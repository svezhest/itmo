"use strict";

const unresolvedArity = 0;

function Const(value) {
    this.value = value;
}

Const.prototype.evaluate = function () {
    return this.value;
};

Const.prototype.postfix = Const.prototype.prefix = Const.prototype.toString = function () {
    return this.value.toString();
};

Const.prototype.diff = function () {
    return Consts.Zero;
};

const Consts = {
    E: new Const(Math.E),
    Zero: new Const(0),
    One: new Const(1),
    Two: new Const(2)
};

const VARIABLES = {
    'x': 0,
    'y': 1,
    'z': 2
};

function Variable(name) {
    this.name = name;
    this.index = VARIABLES[name];
    return this;
}

console.log(new Variable('x') === null);

Variable.prototype.evaluate = function (...args) {
    return args[this.index];
};

Variable.prototype.toString = function () {
    return this.name.toString();
};

Variable.prototype.prefix = Variable.prototype.toString;
Variable.prototype.postfix = Variable.prototype.toString;
Variable.prototype.diff = function (arg) {
    return arg === this.name ? Consts.One : Consts.Zero;
};

// :NOTE: Прототипы
class Op {
    constructor(fn, diff, symbol, arity, ...operands) {
        this.operands = operands;
        this.fn = fn;
        this.diff = diff(...operands);
        this.symbol = symbol;
        this.getArity = () => arity;
    }

    evaluate(...args) {
        return this.fn(...this.operands.map(operand => operand.evaluate(...args)));
    }

    toString() {
        return this.operands.map(operand => operand.toString()).join(' ') + " " + this.symbol;
    }

    prefix() {
        return '(' + this.symbol + ' ' + this.operands.map(operand => operand.prefix()).join(' ') + ')';
    }

    postfix() {
        return '(' + this.operands.map(operand => operand.postfix()).join(' ') + ' ' + this.symbol + ')';
    }
}

const operation = (fn, difFn, sym) => function (...args) {
    return new Op(fn, difFn, sym, fn.length, ...args)
};

const diffSum = (fn) => (...args) => (arg) => args.reduce((res, current) => new Add(res,
    fn(current).diff(arg)), Consts.Zero);

const Add = operation((a, b) => a + b,
    diffSum((current) => current), '+');

const Subtract = operation((a, b) => a - b,
    (a, b) => (arg) => new Subtract(a.diff(arg), b.diff(arg)), '-');

const Multiply = operation((a, b) => a * b,
    (a, b) => (arg) => new Add(new Multiply(a.diff(arg), b), new Multiply(a, b.diff(arg))),
    '*');

const Divide = operation((a, b) => a / b,
    (a, b) => (arg) => new Divide(new Subtract(new Multiply(a.diff(arg), b),
        new Multiply(a, b.diff(arg))), new Power(b, Consts.Two)),
    '/');

const Negate = operation((x) => -x,
    (x) => (arg) => new Negate(x.diff(arg)), 'negate');

const Log = operation((a, b) => Math.log(Math.abs(b)) / Math.log(Math.abs(a)),
    (a, b) => (arg) => {
        let expr = (x, y) => new Divide(new Multiply(new Ln(x), y.diff(arg)), y);
        return new Divide(new Subtract(
            expr(a, b),
            expr(b, a)),
            new Power(new Ln(a), Consts.Two))
    },
    "log");

const Power = operation((a, b) => Math.pow(a, b),
    (a, b) => (arg) => new Multiply(new Power(a, b), new Multiply(b, new Ln(a)).diff(arg)),
    'pow');

const Sumexp = operation((...args) => args.reduce((res, current) => res + Math.exp(current), 0),
     diffSum((current) => new Power(Consts.E, current)),
    'sumexp');

const Softmax = operation((...args) => Math.exp(args[0]) / args.reduce((res, current) => res + Math.exp(current), 0),
    (...args) => (arg) => new Divide(new Power(Consts.E, args[0]), new Sumexp(...args)).diff(arg),
    'softmax');

function Ln(x) {
    return new Log(Consts.E, x);
}

const isDigit = (c) => '0' <= c && c <= '9';

const ops = {
    '+': Add,
    '-': Subtract,
    '*': Multiply,
    '/': Divide,
    'negate': Negate,
    'log': Log,
    'pow': Power,
    'sumexp': Sumexp,
    'softmax': Softmax
};

function parse(expr) {
    let stack = [];
    expr.trim().split(/\s+/).forEach(token => {
        if (token in ops) {
            let args = [];
            for (let j = 0; j < new ops[token]().getArity(); j++) {
                args.push(stack.pop());
            }
            args.reverse();
            stack.push(new ops[token](...args));
        } else if (token in VARIABLES) {
            stack.push(new Variable(token));
        } else if (isDigit(token[0]) || token[0] === '-' && token.length !== 1) {
            stack.push(new Const(parseInt(token)));
        } else {
            throw new Error('Cannot parse symbol ' + token);
        }
    });
    return stack.pop();
}

const MODIFIERS = {
    'postfix': 'a',
    'prefix': 'b'
};

function parseExpression(expr, modifier) {
    let pos = 0;
    let mode = MODIFIERS[modifier];
    expr = expr.trim();

    function Exception(message) {
        this.message = message + ' at position ' + pos + ' at expression ' + expr;
    }

    Exception.prototype.name = "Exception";
    Exception.prototype = Object.create(Error.prototype);
    Exception.prototype.constructor = Exception;

    function isWhiteSpace(c) {
        return /\s/.test(c);
    }

    function isEndOfToken(c) {
        return isWhiteSpace(c) || c === ')' || c === '(';
    }

    function isPartOfNumber(c) {
        return isDigit(c) || c === '-' || c === '.';
    }

    function isOperandBeginning(c) {
        return c in VARIABLES || isPartOfNumber(c) || c === '(';
    }

    function skipUntil(checker) {
        while (!checker(expr[pos]) && pos < expr.length) {
            pos++;
        }
    }

    function parseNumber() {
        let from = pos;
        skipUntil((c) => !isPartOfNumber(c));
        return new Const(parseInt(expr.substr(from, pos - from)));
    }

    function parseOperand() {
        if (expr[pos] in VARIABLES) {
            pos++;
            return new Variable(expr[pos - 1]);
        } else if (isPartOfNumber(expr[pos])) {
            return parseNumber();
        } else if (expr[pos] === '(') {
            pos++;
            return parseInBrackets();
        } else {
            throw new Exception("Cannot parse operand");
        }
    }

    function parseOperationSymbol() {
        let from = pos;
        skipUntil(isEndOfToken);
        let op = expr.substr(from, pos - from);
        if (!op in ops || pos === expr.length) {
            throw new Exception("Cannot parse operation symbol");
        }
        return ops[op];
    }

    function parseOperands() {
        skipUntil((c) => !isWhiteSpace(c));
        let operands = [];
        while (pos < expr.length && isOperandBeginning(expr[pos]) &&
        !(expr[pos] === '-' && pos + 1 < expr.length && !isDigit(expr[pos + 1]))) {
            operands.push(parseOperand());
            skipUntil((c) => !isWhiteSpace(c));
        }
        if (pos === expr.length) {
            throw new Exception("Unexpected ')' symbol");
        }
        return operands;
    }

    function parseInBrackets() {
        skipUntil((c) => !isWhiteSpace(c));
        let op, operands = null;
        if (mode === 'b') {
            op = parseOperationSymbol();
            operands = parseOperands();
        } else {
            operands = parseOperands();
            op = parseOperationSymbol();
        }
        // :NOTE: instanceof
        try {
            (new op);
        } catch (e) {
            throw new Exception("Expected operation");
        }
        let arity = (new op).getArity();
        if (arity !== operands.length && arity !== unresolvedArity) {
            throw new Exception("Extra arguments has been found, or not enough arguments");
        }
        skipUntil((c) => !isWhiteSpace(c));
        if (pos === expr.length || expr[pos] !== ')') {
            throw new Exception("Found unclosed bracket");
        }
        pos++;
        return new op(...operands);
    }

    let result = parseOperand();
    if (pos !== expr.length) {
        throw new Exception("Extra content has been found after expression");
    }
    return result;
}

const parsePrefix = (expr) =>  parseExpression(expr, 'prefix');
const parsePostfix = (expr) => parseExpression(expr, 'postfix');