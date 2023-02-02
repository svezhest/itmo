const dateToUnix = (date) => Math.floor(date.getTime() / 1000)

const hoursToMills = (hours) => hours * 60 * 60 * 1000

function hoursToTimeArray(hours) {
    const start = new Date(new Date().getTime() - hoursToMills(hours))
    const res = [start]
    for (let i = 1; i <= hours; i++) {
        res.push(new Date(start.getTime() + hoursToMills(i)))
    }
    return res.map(dateToUnix)
}

module.exports = hoursToTimeArray
