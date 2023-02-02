const {access_key, version} = require("../../config.json")
const request = require("request-promise")

async function getData(hashtag, startTime, endTime) {
    const url = `https://api.vk.com/method/newsfeed.search?`
        + `access_token=${access_key}&v=${version}&q=${encodeURIComponent(hashtag)}`
        + `&start_time=${startTime}&end_time=${endTime}`
    const res = await request(url)
    return JSON.parse(res).response
}

module.exports = getData
