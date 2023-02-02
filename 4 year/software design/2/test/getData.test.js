const getData = require('../src/vk/getData')
const nock = require('nock')
const {access_key, version} = require("../config.json")

const scope = nock('https://api.vk.com')
    .get(`/method/newsfeed.search?access_token=${access_key}&v=${version}&q=hashtag&start_time=10&end_time=20`)
    .reply(200, {
        "response": {
            "total_count": 3
        }
    })

describe('getData does get data', () => {
    test('getData does send correct get and reads it properly', async () => {
        const res = await getData('hashtag', 10, 20)
        expect(res.hasOwnProperty('total_count'))
        expect(res.total_count).toEqual(3)
    })
})