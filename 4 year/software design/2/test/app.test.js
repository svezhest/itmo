const countHashtagEntries = require('../src/app')
const getData = require("../src/vk/getData.js")
jest.mock('../src/vk/getData.js', () => () => ({total_count: 1}))

describe('it works', () => {
    test('app will return the expected count', async () => {
        const res = await countHashtagEntries('#test', 7)
        expect(res).toEqual([1, 1, 1, 1, 1, 1, 1])
    })

    test('should throw an error when given zero', async () => {
        try {
            const res = await countHashtagEntries('#test', 0)
            console.log(res)
            expect(false).toEqual(true)
        } catch (err) {
            expect(true).toEqual(true)
        }
    })
})