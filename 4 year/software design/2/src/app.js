const getData = require("./vk/getData.js")
const hoursToTimeArray = require("./utils/timeEncoder.js")

async function countHashtagEntries(hashtag, hours) {
    if (hours <= 0) {
        throw `parameter 'hours' should be a positive integer number`
    }
    let [timeStart, ...timeArray] = hoursToTimeArray(hours)
    const res = timeArray.map(async (timeEnd) => {
        const data = await getData(hashtag, timeStart, timeEnd)
        timeStart = timeEnd
        if (data && data.hasOwnProperty('total_count')) {
            return data.total_count
        } else {
            return 0
        }
    })
    return await Promise.all(res)
}

module.exports = countHashtagEntries

const showResult = (hashtag, hours) => countHashtagEntries(hashtag, hours).then(res => console.log(hashtag, ' -> ', res))

// showResult('#tiktok', 5)
// showResult('#abc', 14)
