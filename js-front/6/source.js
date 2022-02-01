'use strict';

const fetch = require('node-fetch');

const API_KEY = require('./key.json');

const fetchUrl = 'https://api.weather.yandex.ru/v2/forecast?geoid=';

function shortenCondition(condition) {
    switch (condition) {
        case 'clear':
            return 's';
        case 'partly-cloud':
            return 's';
        case 'partly-cloudy':
            return 's';
        case 'cloudy':
            return 'c';
        case 'overcast':
            return 'c';
        default:
            return 'f';
    }
}

const getWeather = geoid => {
    return fetch(fetchUrl + geoid + '&hours=false&limit=7', {
            headers: { 'X-Yandex-API-Key': API_KEY.key }
        })
        .then(response => response.json())
        .then(ans =>
            ans['forecasts'].map(forecast => forecast['parts']['day_short']['condition'])
            .map(condition => shortenCondition(condition))
        )
};

/**
 * @typedef {object} TripItem Город, который является частью маршрута.
 * @property {number} geoid Идентификатор города
 * @property {number} day Порядковое число дня маршрута
 */

class TripBuilder {
    constructor(geoids) {
        this.ids = geoids;
        this.desiredPath = [];
        this.maxx = 100;
    }

    /**
     * Метод, добавляющий условие наличия в маршруте
     * указанного количества солнечных дней
     * Согласно API Яндекс.Погоды, к солнечным дням
     * можно приравнять следующие значения `condition`:
     * * `clear`;
     * * `partly-cloudy`.
     * @param {number} daysCount количество дней
     * @returns {object} Объект планировщика маршрута
     */
    sunny(daysCount) {
        for (let i = 0; i < daysCount; i++) {
            this.desiredPath.push('s');
        }
        return this;
    }

    /**
     * Метод, добавляющий условие наличия в маршруте
     * указанного количества пасмурных дней
     * Согласно API Яндекс.Погоды, к солнечным дням
     * можно приравнять следующие значения `condition`:
     * * `cloudy`;
     * * `overcast`.
     * @param {number} daysCount количество дней
     * @returns {object} Объект планировщика маршрута
     */
    cloudy(daysCount) {
        for (let i = 0; i < daysCount; i++) {
            this.desiredPath.push('c');
        }
        return this;
    }

    /**
     * Метод, добавляющий условие максимального количества дней.
     * @param {number} daysCount количество дней
     * @returns {object} Объект планировщика маршрута
     */
    max(daysCount) {
        this.maxx = daysCount
        return this;
    }

    dfs(cur, visited, ind, count) {
        if (ind === this.desiredPath.length) {
            return [...visited, cur];
        }

        for (const nextInd in cur.next) {
            const next = cur.next[nextInd]
            if (next.id === cur.id) {
                if (count < this.maxx) {
                    let res = this.dfs(next, cur.id === -1 ? [...visited] : [...visited, cur], ind + 1, count + 1)
                    if (res !== []) {
                        return res
                    }
                }
            } else {
                let ok = true
                for (const vId in visited) {
                    const v = visited[vId]
                    if (v.id === next.id) {
                        // do not go to visited els
                        ok = false
                        break
                    }
                }
                if (ok) {
                    let res = this.dfs(next, cur.id === -1 ? [...visited] : [...visited, cur], ind + 1, 1)
                    if (res !== []) {
                        return res
                    }
                }
            }
        }
        return []
    }


    buildTreeFromTable(table) {
        let nodes = new Map()

        for (let y = 0; y < table.length; y++) {
            for (let x = 0; x < table[y].length; x++) {
                table[y][x] = table[y][x] === this.desiredPath[x] ? 1 : 0
                nodes[y * table[y].length + x] = new Node(this.ids[y], [])
            }
        }

        for (let y = 0; y < table.length; y++) {
            for (let x = 0; x < table[y].length - 1; x++) {
                for (let ny = 0; ny < table.length; ny++) {
                    const nx = x + 1
                    if (table[y][x] === 1 && table[ny][nx] === 1) {
                        nodes[y * table[y].length + x].next = [...nodes[y * table[y].length + x].next, nodes[ny * table[ny].length + nx]]
                    }
                }
            }
        }

        let res = []

        for (let y = 0; y < table.length; y++) {
            if (table[y][0] === 1) {
                res = [...res, nodes[y * table[y].length]]
            }
        }

        return new Node(-1, res)
    }

    /**
     * Метод, возвращающий Promise с планируемым маршрутом.
     * @returns {Promise<TripItem[]>} Список городов маршрута
     */
    build() {
        return Promise.all(this.ids.map(id => getWeather(id))).then(table => {
            // console.info(table)
            const tree = this.buildTreeFromTable(table)
            const preRes = this.dfs(tree, [], 0, 0)
            const res = []
            for (let i = 0; i < preRes.length; i++) {
                res.push({ geoid: preRes[i].id, day: i + 1 })
            }

            if (res.length > 0) {
                return res;
            }
            throw new Error('Не могу построить маршрут!');
        });
    }
}

class Node {
    constructor(id, next) {
        this.id = id;
        this.next = next ? next : [];
    }
}


/**
 * Фабрика для получения планировщика маршрута.
 * Принимает на вход список идентификаторов городов, а
 * возвращает планировщик маршрута по данным городам.
 *
 * @param {number[]} geoids Список идентификаторов городов
 * @returns {TripBuilder} Объект планировщика маршрута
 * @see https://yandex.ru/dev/xml/doc/dg/reference/regions-docpage/
 */
function

planTrip(geoids) {
    return new TripBuilder(geoids);
}

module
    .exports = {
        planTrip
    };