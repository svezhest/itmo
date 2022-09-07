"use strict";

const cnst = value => () => value;

const variables = ['x', 'y', 'z'];

const variable = sym => {
    const index = variables.indexOf(sym);
    return (...args) => args[index]
};

const op = (action) => (...args) => (...vars) => action(...(args.map(f => f(...vars))));

const add = op((a, b) => a + b);

const subtract = op((a, b) => a - b);

const multiply = op((a, b) => a * b);

const divide = op((a, b) => a / b);

const negate = op(a => -a);

const avg5 = op((...args) => args.reduce((res, current) => res + current, 0) / args.length);

const med3 = op((...args) => args.sort((a, b) => a - b)[Math.ceil(args.length / 2) - 1]);


const pi = cnst(Math.PI);
const e = cnst(Math.E);

function parse(expr) {

    // :NOTE: Арность
    const ops = {
        '+': [add, 2],
        '-': [subtract, 2],
        '*': [multiply, 2],
        '/': [divide, 2],
        'negate': [negate, 1],
        'avg5': [avg5, 5],
        'med3': [med3, 3]
    };

    const cnsts = {
        'pi': pi,
        'e': e
    };

    let stack = [];
    for (token of expr.trim().split(/\s+/)) {
        if (token in ops) {
            // :NOTE: Array.?
            let args = [];
            for (let j = 0; j < ops[token][1]; j++) {
                args.push(stack.pop());
            }
            args.reverse();
            stack.push(ops[token][0](...args));
        } else if (variables.indexOf(token) !== -1) {
            stack.push(variable(token));
        } else if (token in cnsts) {
            stack.push(cnsts[token]);
        } else if (0 <= token[0] && token[0] <= 9 || (token[0] === '-' && token.length !== 1)) {
            stack.push(cnst(parseInt(token)));
        } else {
            throw new Error('Cannot parse symbol' + token);
        }
    }
    return stack.pop();
}