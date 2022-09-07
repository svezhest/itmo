'use strict';

/**
 * Итератор по друзьям
 * @constructor
 * @param {Object[]} friends
 * @param {Filter} filter
 */
function Iterator(friends, filter = Filter()) {
    if (!(filter instanceof Filter)) {
        throw new TypeError();
    }

    this.guests = limitGuests(friends).filter(filter.predicate);
}

Iterator.prototype = {
    index: 0,
    done: function() {
        return this.index >= this.guests.length;
    },
    next: function() {
        if (this.done()) {
            return null;
        } else {
            return this.guests[this.index++]
        }
    }
};

/**
 * Итератор по друзям с ограничением по кругу
 * @extends Iterator
 * @constructor
 * @param {Object[]} friends
 * @param {Filter} filter
 * @param {Number} maxLevel – максимальный круг друзей
 */
function LimitedIterator(friends, filter = Filter(), maxLevel = Infinity) {
    if (!(filter instanceof Filter)) {
        throw new TypeError();
    }

    this.guests = limitGuests(friends, maxLevel).filter(filter.predicate);
}

Object.setPrototypeOf(LimitedIterator.prototype, Iterator.prototype);

/**
 * Фильтр друзей
 * @constructor
 */
function Filter() {
    this.predicate = () => true;
}

function limitGuests(friends, maxLevel = Infinity) {
    const friendByName = new Map();
    friends.forEach(friend => {
        friendByName.set(friend.name, friend);
    });

    let addedFriends = new Set();
    let guests = [];
    let currentFriends = friends
        .filter(f => f.best)
        .sort((a, b) => a.name.localeCompare(b.name));

    let friendLevel = 0;
    while (friendLevel < maxLevel && currentFriends.length > 0) {
        friendLevel++;
        let nextFriends = [];
        currentFriends.forEach(friend => {
            addedFriends.add(friend.name);
            guests.push(friend);
        });
        currentFriends.forEach(friend => {
            nextFriends = nextFriends.concat(friend.friends);
        });
        currentFriends = nextFriends.filter(nextFriend => !addedFriends.has(nextFriend));
        currentFriends = currentFriends.filter((nextFriend, index, self) => index === self.indexOf(nextFriend));
        currentFriends = currentFriends.sort();
        currentFriends = currentFriends.map(nextFriend => friendByName.get(nextFriend));
    }

    return guests;
}

/**
 * Фильтр друзей
 * @extends Filter
 * @constructor
 */
function MaleFilter() {
    this.predicate = friend => friend.gender === 'male';
}

Object.setPrototypeOf(MaleFilter.prototype, Filter.prototype);

/**
 * Фильтр друзей-девушек
 * @extends Filter
 * @constructor
 */
function FemaleFilter() {
    this.predicate = friend => friend.gender === 'female';
}

Object.setPrototypeOf(FemaleFilter.prototype, Filter.prototype);


exports.Iterator = Iterator;
exports.LimitedIterator = LimitedIterator;

exports.Filter = Filter;
exports.MaleFilter = MaleFilter;
exports.FemaleFilter = FemaleFilter;