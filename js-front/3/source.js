'use strict';
const days = ['ПН', 'ВТ', 'СР', 'ЧТ', 'ПТ', 'СБ', 'ВС'];

function parseDate(date) {
    const [day, time] = date.split(' ');
    return [day, ...parseTime(time)];
}

function parseTime(time) {
    const [hoursAndMinutes, timezone] = time.split('+');
    const [hours, minutes] = hoursAndMinutes.split(':');

    return [hours, minutes, timezone];
}

function timeToMin(time) {
    const parsed = time.map(x => parseInt(x))
    return (parsed[0] - parsed[2]) * 60 + parsed[1]
}

function dateToMin(time) {
    return days.indexOf(time[0]) * 24 * 60 + timeToMin(time.slice(1))
}

function invert(intervals, start, end) {
    let ans = []
    let last = start

    intervals.forEach(([from, to]) => {
        if (last !== from) { ans.push([last, from]) }
        last = to
    })
    ans.push([last, end])
    return ans
}

function merge(intervals) {
    const mergeInterval = (ac, x) => (!ac.length || ac[ac.length - 1][1] < x[0] ?
        ac.push(x) :
        ac[ac.length - 1][1] = Math.max(ac[ac.length - 1][1], x[1]), ac);

    return intervals
        .sort((a, b) => a[0] - b[0])
        .reduce(mergeInterval, []);
}

function intersect(l, r) {
    let res = []
    l.forEach(x => r.forEach(y => {
        let t = [Math.max(x[0], y[0]), Math.min(x[1], y[1])]
        if (t[0] <= t[1]) { res.push(t) }
    }))

    return merge(res)
}

function minToDate(mins) {
    return [days[Math.floor(mins / (24 * 60))], Math.floor(mins % (24 * 60) / 60), mins % 60]
}

const getAppropriateMoment = function(schedule, duration, workingHours) {
    const timezone = parseTime(workingHours.from)[2]
    let ans = intersect(invert(merge([...schedule.Danny, ...schedule.Linus, ...schedule.Rusty].map(event => [event.from, event.to].map(parseDate).map(dateToMin))), dateToMin(parseDate("ПН 00:00+" + timezone)), dateToMin(parseDate("СР 23:59+" + timezone))), merge(days.map(day => [day + " " + workingHours.from, day + " " + workingHours.to].map(parseDate).map(dateToMin)))).filter(x => x[1] - x[0] >= duration)
    return {

        /**
         * Найдено ли время
         * @returns {Boolean}
         */
        exists: function() {
            return ans.length > 0;
        },

        /**
         * Возвращает отформатированную строку с часами для ограбления
         * Например,
         *   "Начинаем в %HH:%MM (%DD)" -> "Начинаем в 14:59 (СР)"
         * @param {String} template
         * @returns {String}
         */
        format: function(template) {
            if (!this.exists()) {
                return '';
            }

            const date = minToDate(ans[0][0] + 60 * timezone).map(x => x.toString().padStart(2, 0))

            return template.replace('%HH', date[1])
                .replace('%MM', date[2])
                .replace('%DD', date[0]);
        },

        /**
         * Попробовать найти часы для ограбления позже [*]
         * @star
         * @returns {Boolean}
         */
        tryLater: function() {
            if (!this.exists) {
                return false
            }
            if (ans[0][1] - ans[0][0] - 30 >= duration) {
                ans[0][0] += 30;

                return true;
            }
            let ind = 1
            while (ind < ans.length) {
                if (ans[0][0] + 30 > ans[ind][0]) {
                    ind++
                } else {
                    break
                }
            }
            if (ind === ans.length) {
                return false
            }
            if (ans[0][0] + 30 <= ans[ind][0]) {
                ans = ans.slice(ind)
                return true
            }


            return false;
        }
    };
};

module.exports = {
    getAppropriateMoment
};