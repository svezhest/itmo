const { count } = require("console");
const { KeyObject } = require("crypto");

function getEmitter() {
    return {
        /**
         * Подписаться на событие
         * @param {String} event
         * @param {Object} context
         * @param {Function} handler
         */
        on: function(event, context, handler) {
            if (!this[event]) {
                this[event] = [];
            }
            this[event].push({ context, handler });

            return this;
        },

        /**
         * Отписаться от события
         * @param {String} event
         * @param {Object} context
         */
        off: function(event, context) {
            Object.keys(this).forEach(key => {
                if (key === event || key.indexOf(event + ".") === 0) {
                    this[key] = this[key].filter(event => !(event.context === context));
                }
            });
            return this;
        },

        /**
         * Уведомить о событии
         * @param {String} event
         */
        emit: function(event) {
            if (this[event]) {
                this[event].forEach(event => event.handler.apply(event.context));
            }

            if (event.indexOf('.') !== -1) {
                this.emit(event.substring(0, event.lastIndexOf('.')));
            }

            return this;
        },

        /**
         * Подписаться на событие с ограничением по количеству полученных уведомлений
         * @star
         * @param {String} event
         * @param {Object} context
         * @param {Function} handler
         * @param {Number} times – сколько раз получить уведомление
         */
        several: function(event, context, handler, times) {
            if (times <= 0) {
                times = Infinity
            }
            let h = {
                counter: times,

                apply: function(context) {
                    if (this.counter > 0) {
                        handler.apply(context);
                        this.counter--;
                    }
                }
            }
            this.on(event, context, h)
            return this
        },

        /**
         * Подписаться на событие с ограничением по частоте получения уведомлений
         * @star
         * @param {String} event
         * @param {Object} context
         * @param {Function} handler
         * @param {Number} frequency – как часто уведомлять
         */
        through: function(event, context, handler, frequency) {
            if (frequency <= 0) {
                frequency = 1
            }
            let h = {
                counter: 0,
                frequency: frequency,
                apply: function(context) {
                    if (this.counter % this.frequency === 0) {
                        handler.apply(context);
                    }
                    this.counter++;
                }
            }
            this.on(event, context, h)
            return this
        }
    };
}


module.exports = {
    getEmitter
};