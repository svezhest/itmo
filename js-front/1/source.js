'use strict';

/**
 * Складывает два целых числа
 * @param {Number} a Первое целое
 * @param {Number} b Второе целое
 * @throws {TypeError} Когда в аргументы переданы не числа
 * @returns {Number} Сумма аргументов
 */
function abProblem(a, b) {
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw TypeError('...');
    }
    return a + b;
}

/**
 * Определяет век по году
 * @param {Number} year Год, целое положительное число
 * @throws {TypeError} Когда в качестве года передано не число
 * @throws {RangeError} Когда год – отрицательное значение
 * @returns {Number} Век, полученный из года
 */
function centuryByYearProblem(year) {
    if (typeof year !== 'number') {
        throw TypeError('...');
    }
    if (year < 0) {
        throw RangeError('...');
    }
    return year === 0 ? 0 : Math.floor(1 + (year - 1) / 100);
}

/**
 * Переводит цвет из формата HEX в формат RGB
 * @param {String} hexColor Цвет в формате HEX, например, '#FFFFFF'
 * @throws {TypeError} Когда цвет передан не строкой
 * @throws {RangeError} Когда значения цвета выходят за пределы допустимых
 * @returns {String} Цвет в формате RGB, например, '(255, 255, 255)'
 */
function colorsProblem(hexColor) {
    if (typeof hexColor !== 'string') {
        throw TypeError('...');
    }
    if (hexColor.match(/^#[\da-fA-F]+$/) === null) {
        throw RangeError('...');
    }
    // #ababab assuming '#' at front
    let res = parseInt(hexColor.substr(1), 16);
    if (res < 0 || res > 16777215) {
        throw RangeError('...');
    }
    return '(' + Math.floor(res / 65536) + ', ' + Math.floor(res / 256) % 256 + ', ' + res % 256 + ')';
}

/**
 * Находит n-ое число Фибоначчи
 * @param {Number} n Положение числа в ряде Фибоначчи
 * @throws {TypeError} Когда в качестве положения в ряде передано не число
 * @throws {RangeError} Когда положение в ряде не является целым положительным числом
 * @returns {Number} Число Фибоначчи, находящееся на n-ой позиции
 */
function fibonacciProblem(n) {
    if (typeof n !== 'number') {
        throw TypeError('...');
    }
    if (n <= 0 || !Number.isInteger(n)) {
        throw RangeError('...');
    }
    let a = 1;
    let b = 1;
    for (let i = 1; i < n; i++) {
        let t = a + b;
        a = b;
        b = t;
    }
    return a;
}

/**
 * Транспонирует матрицу
 * @param {(Any[])[]} matrix Матрица размерности MxN
 * @throws {TypeError} Когда в функцию передаётся не двумерный массив
 * @returns {(Any[])[]} Транспонированная матрица размера NxM
 */
function matrixProblem(matrix) {
    if (Array.isArray(matrix) && matrix.length === 0) {
        return matrix;
    }
    if (!Array.isArray(matrix) || !Array.isArray(matrix[0])) {
        throw TypeError('...');
    }
    let rows = matrix.length;
    let cols = matrix[0].length;
    let res = [];
    for (let i = 0; i < cols; i++) {
        res[i] = Array(rows);
        for (let j = 0; j < rows; j++) {
            res[i][j] = matrix[j][i];
        }
    }
    return res;
}

/**
 * Переводит число в другую систему счисления
 * @param {Number} n Число для перевода в другую систему счисления
 * @param {Number} targetNs Система счисления, в которую нужно перевести (Число от 2 до 36)
 * @throws {TypeError} Когда переданы аргументы некорректного типа
 * @throws {RangeError} Когда система счисления выходит за пределы значений [2, 36]
 * @returns {String} Число n в системе счисления targetNs
 */
function numberSystemProblem(n, targetNs) {
    if (typeof(n) !== "number" || typeof(targetNs) !== "number") {
        throw TypeError('...');
    }
    if (targetNs < 2 || targetNs > 36 || targetNs !== Math.floor(targetNs)) {
        throw RangeError('...');
    }
    return n.toString(targetNs);
}

/**
 * Проверяет соответствие телефонного номера формату
 * @param {String} phoneNumber Номер телефона в формате '8–800–xxx–xx–xx'
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Boolean} Если соответствует формату, то true, а иначе false
 */
function phoneProblem(phoneNumber) {
    if (typeof(phoneNumber) !== "string") {
        throw TypeError('...');
    }
    return /^8-800-\d\d\d-\d\d-\d\d$/.exec(phoneNumber) !== null;
}

/**
 * Определяет количество улыбающихся смайликов в строке
 * @param {String} text Строка в которой производится поиск
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Number} Количество улыбающихся смайликов в строке
 */
function smilesProblem(text) {
    if (typeof(text) !== "string") {
        throw TypeError('...');
    }
    let m = text.match(/:-\)|\(-:/g);
    if (m !== null) {
        return m.length;
    }
    return 0;
}

/**
 * Определяет победителя в игре "Крестики-нолики"
 * Тестами гарантируются корректные аргументы.
 * @param {(('x' | 'o')[])[]} field Игровое поле 3x3 завершённой игры
 * @returns {'x' | 'o' | 'draw'} Результат игры
 */
function ticTacToeProblem(field) {
    let xWon = ttHasWon(field, 'x');
    let oWon = ttHasWon(field, 'o');
    if (xWon === oWon) {
        return 'draw';
    }
    if (xWon) {
        return 'x';
    }
    if (oWon) {
        return 'o';
    }
}

function ttHasWon(field, sign) {
    for (let i = 0; i < 3; i++) {
        let ok = true
        for (let j = 0; j < 3; j++) {
            if (field[i][j] !== sign) {
                ok = false;
            }
        }
        if (ok) {
            return true;
        }
    }
    for (let i = 0; i < 3; i++) {
        let ok = true
        for (let j = 0; j < 3; j++) {
            if (field[j][i] !== sign) {
                ok = false;
            }
        }
        if (ok) {
            return true;
        }
    }
    if (field[0][0] === sign && field[1][1] === sign && field[2][2] === sign) {
        return true;
    }
    if (field[2][0] === sign && field[1][1] === sign && field[0][2] === sign) {
        return true;
    }
    return false;
}

module.exports = {
    abProblem,
    centuryByYearProblem,
    colorsProblem,
    fibonacciProblem,
    matrixProblem,
    numberSystemProblem,
    phoneProblem,
    smilesProblem,
    ticTacToeProblem
};