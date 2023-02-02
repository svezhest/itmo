const hoursToTimeArray = require("../src/utils/timeEncoder")

describe('timeEncoder works correctly', function () {
    test('timeEncoder returns an array of numbers', () => {
        const res = hoursToTimeArray(5)
        expect(res.hasOwnProperty('length')).toBe(true)
        expect(res.length).toEqual(6)
        res.forEach(n => expect(typeof n).toEqual('number'))
    })

    test('timeEncoder works exactly right', () => {
        jest.useFakeTimers().setSystemTime(new Date('2000-01-01T15:00:00.000Z'));
        const res = hoursToTimeArray(5)
        expect(new Date(res[0] * 1000)).toEqual(new Date('2000-01-01T10:00:00.000Z'))
        expect(new Date(res[1] * 1000)).toEqual(new Date('2000-01-01T11:00:00.000Z'))
        expect(new Date(res[2] * 1000)).toEqual(new Date('2000-01-01T12:00:00.000Z'))
        expect(new Date(res[3] * 1000)).toEqual(new Date('2000-01-01T13:00:00.000Z'))
        expect(new Date(res[4] * 1000)).toEqual(new Date('2000-01-01T14:00:00.000Z'))
        expect(new Date(res[5] * 1000)).toEqual(new Date('2000-01-01T15:00:00.000Z'))
    })
});
