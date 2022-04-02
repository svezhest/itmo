#include <iostream>
#include <fstream>

struct Params {
    bool c = false, d = false, u = false;
};

std::pair<Params, int> parse_params(int start, int argc, char **argv) {
    enum Ops {c, d, u};
    Params p;
    std::string optinons[3] = {"--count", "--repeated", "--unique"};
    int i;
    for (i = start; i < argc; ++i) {
        if (argv[i][0] == '-') {
            int j = 1;
            if (argv[i][j] == '-') {
                if (optinons[c].compare(argv[i]) == 0) {
                    p.c = true;
                } else if (optinons[d].compare(argv[i]) == 0) {
                    p.d = true;
                } else if (optinons[u].compare(argv[i]) == 0) {
                    p.u = true;
                } else {
                    return {p, i};
                }
            } else {
                while (argv[i][j] != '\0') {
                    switch (argv[i][j]) {
                        case 'u':
                            p.u = true;
                            break;
                        case 'd':
                            p.d = true;
                            break;
                        case 'c':
                            p.c = true;
                            break;
                        default:
                            return {p, i};
                    }
                    ++j;
                }
            }
        } else {
            break;
        }

    }
    return {p, i};
}

class Filter {
    Params params;

public:
    Filter(const Params &p) : params(p) {};

    void filtrate(std::istream &input) {
        std::string prev;
        std::string line = "";
        bool eof = false;
        if (!std::getline(input, line)) {
            eof = true;
        }
        while (!eof) {
            int counter = 0;
            prev = std::move(line);
            do {
                ++counter;
                if (!std::getline(input, line)) {
                    eof = true;
                    break;
                }
            } while (line == prev);
            if ((counter == 1 && !params.d) || (counter != 1 && !params.u)) {
                if (params.c) {
                    std::cout << "      " << counter << ' ';
                }
                std::cout << prev << '\n';
            }
        }
    }

};

int main(int argc, char **argv) {
    auto[p, ind] = parse_params(1, argc, argv);
    const char *input_name = nullptr;
    if (ind != argc) {
        input_name = argv[ind];
    }
    Filter filter(p);

    if (input_name != nullptr) {
        std::ifstream f(input_name);
        filter.filtrate(f);
    } else {
        filter.filtrate(std::cin);
    }
    return 0;
}
