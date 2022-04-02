#include "calc.h"

#include <cctype> // for std::isspace
#include <cmath> // various math functions
#include <iostream> // for error reporting via std::cerr

namespace {

    const std::size_t max_decimal_digits = 10;

    enum class Op {
        ERR, SET, ADD, SUB, MUL, DIV, REM, NEG, POW, SQRT, FOLD_ADD, FOLD_SUB, FOLD_MUL, FOLD_DIV, FOLD_REM, FOLD_POW
    };

    enum class Arity {
        err, unary, binary, folded
    };

    Arity arity(const Op op) {
        switch (op) {
            case Op::ERR:
                return Arity::err;
            case Op::NEG:
                [[fallthrough]];
            case Op::SQRT:
                return Arity::unary;
            case Op::SET:
                [[fallthrough]];
            case Op::ADD:
                [[fallthrough]];
            case Op::SUB:
                [[fallthrough]];
            case Op::MUL:
                [[fallthrough]];
            case Op::DIV:
                [[fallthrough]];
            case Op::REM:
                [[fallthrough]];
            case Op::POW:
                return Arity::binary;
            case Op::FOLD_ADD:
                [[fallthrough]];
            case Op::FOLD_SUB:
                [[fallthrough]];
            case Op::FOLD_MUL:
                [[fallthrough]];
            case Op::FOLD_DIV:
                [[fallthrough]];
            case Op::FOLD_REM:
                [[fallthrough]];
            case Op::FOLD_POW:
                return Arity::folded;
        }
        return Arity::err;
    }

    Op parse_op(const std::string &line, std::size_t &i) {
        const auto rollback = [&i, &line](const std::size_t n) {
            i -= n;
            std::cerr << "Unknown operation " << line << std::endl;
            return Op::ERR;
        };
        switch (line[i++]) {
            case '0':
                [[fallthrough]];
            case '1':
                [[fallthrough]];
            case '2':
                [[fallthrough]];
            case '3':
                [[fallthrough]];
            case '4':
                [[fallthrough]];
            case '5':
                [[fallthrough]];
            case '6':
                [[fallthrough]];
            case '7':
                [[fallthrough]];
            case '8':
                [[fallthrough]];
            case '9':
                --i;
                return Op::SET;
            case '+':
                return Op::ADD;
            case '-':
                return Op::SUB;
            case '*':
                return Op::MUL;
            case '/':
                return Op::DIV;
            case '%':
                return Op::REM;
            case '_':
                return Op::NEG;
            case '^':
                return Op::POW;
            case 'S':
                switch (line[i++]) {
                    case 'Q':
                        switch (line[i++]) {
                            case 'R':
                                switch (line[i++]) {
                                    case 'T':
                                        return Op::SQRT;
                                    default:
                                        return rollback(4);
                                }
                            default:
                                return rollback(3);
                        }
                    default:
                        return rollback(2);
                }
            case '(':
                switch (line[i++]) {
                    case '+':
                        switch (line[i++]) {
                            case ')':
                                return Op::FOLD_ADD;
                            default:
                                return rollback(3);
                        }
                    case '-':
                        switch (line[i++]) {
                            case ')':
                                return Op::FOLD_SUB;
                            default:
                                return rollback(3);
                        }
                    case '*':
                        switch (line[i++]) {
                            case ')':
                                return Op::FOLD_MUL;
                            default:
                                return rollback(3);
                        }
                    case '/':
                        switch (line[i++]) {
                            case ')':
                                return Op::FOLD_DIV;
                            default:
                                return rollback(3);
                        }
                    case '%':
                        switch (line[i++]) {
                            case ')':
                                return Op::FOLD_REM;
                            default:
                                return rollback(3);
                        }
                    case '^':
                        switch (line[i++]) {
                            case ')':
                                return Op::FOLD_POW;
                            default:
                                return rollback(3);
                        }
                    default:
                        return rollback(2);
                }
            default:
                return rollback(1);
        }
    }

    std::size_t skip_ws(const std::string &line, std::size_t &i) {
        while (i < line.size() && std::isspace(line[i])) {
            ++i;
        }
        return i;
    }

    double parse_arg(const std::string &line, std::size_t &i) {
        double res = 0;
        std::size_t count = 0;
        bool good = true;
        bool integer = true;
        double fraction = 1;
        while (good && i < line.size() && count < max_decimal_digits) {
            switch (line[i]) {
                case '0':
                    [[fallthrough]];
                case '1':
                    [[fallthrough]];
                case '2':
                    [[fallthrough]];
                case '3':
                    [[fallthrough]];
                case '4':
                    [[fallthrough]];
                case '5':
                    [[fallthrough]];
                case '6':
                    [[fallthrough]];
                case '7':
                    [[fallthrough]];
                case '8':
                    [[fallthrough]];
                case '9':
                    if (integer) {
                        res *= 10;
                        res += line[i] - '0';
                    } else {
                        fraction /= 10;
                        res += (line[i] - '0') * fraction;
                    }
                    ++i;
                    ++count;
                    break;
                case '.':
                    integer = false;
                    ++i;
                    break;
                default:
                    good = false;
                    break;
            }
        }
        return res;
    }

    double unary(const double current, const Op op) {
        switch (op) {
            case Op::NEG:
                return -current;
            case Op::SQRT:
                if (current > 0) {
                    return std::sqrt(current);
                } else {
                    std::cerr << "Bad argument for SQRT: " << current << std::endl;
                    [[fallthrough]];
                }
            default:
                return current;
        }
    }

    double binary(const Op op, const double left, const double right) {
        switch (op) {
            case Op::SET:
                return right;
            case Op::ADD:
                return left + right;
            case Op::SUB:
                return left - right;
            case Op::MUL:
                return left * right;
            case Op::DIV:
                if (right != 0) {
                    return left / right;
                } else {
                    std::cerr << "Bad right argument for division: " << right << std::endl;
                    return left;
                }
            case Op::REM:
                if (right != 0) {
                    return std::remainder(left, right);
                } else {
                    std::cerr << "Bad right argument for remainder: " << right << std::endl;
                    return left;
                }
            case Op::POW:
                return std::pow(left, right);
            default:
                return left;
        }
    }
}

Op unfold(const Op op) {
    switch (op) {
        case Op::FOLD_ADD:
            return Op::ADD;
        case Op::FOLD_SUB:
            return Op::SUB;
        case Op::FOLD_MUL:
            return Op::MUL;
        case Op::FOLD_DIV:
            return Op::DIV;
        case Op::FOLD_REM:
            return Op::REM;
        case Op::FOLD_POW:
            return Op::POW;
        default:
            return Op::ERR;
    }
}

double folded(const Op op, double first, std::size_t &i, const std::string &line) {
    while (true) {
        std::size_t j = i;
        skip_ws(line, i);
        if (i == j) {
            if (i != line.size()) {
                std::cerr << "No space symbols found, line remaining: " << line.substr(i)
                          << "\n";
            }
            break;
        }
        j = i;
        double t = parse_arg(line, i);
        if (i == j) {
            if (i != line.size()) {
                std::cerr << "Cannot parse argument, line remaining: " << line.substr(i) << "\n";
            }
            break;
        }
        if (unfold(op) == Op::REM) {
            if (t != 0) {
                first = std::fmod(first, t);
            } else {
                std::cerr << "Bad right argument for remainder: " << t << std::endl;
                first = t;
            }
        } else {


        }
    }
    return first;
}


double process_line(const double current, const std::string &line) {
    std::size_t i = 0;
    const auto op = parse_op(line, i);
    switch (arity(op)) {
        case Arity::folded: {
            return folded(op, current, i, line);
        }
        case Arity::binary: {
            skip_ws(line, i);
            double arg = 0;
            arg = parse_arg(line, i);
            if (i < line.size()) {
                std::cerr << "Argument isn't fully parsed, suffix left: '" << line.substr(i) << "'" << std::endl;
            }
            return binary(op, current, arg);
        }
        case Arity::unary:
            return unary(current, op);
        default:
            break;
    }
    return current;
}
