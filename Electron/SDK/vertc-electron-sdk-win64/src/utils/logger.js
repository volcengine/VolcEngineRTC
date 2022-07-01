"use strict"

var Events = {};

const LOG_LEVEL_NONE = 0;
const LOG_LEVEL_FATAL = 1;
const LOG_LEVEL_ERROR = 2;
const LOG_LEVEL_WARNING = 3;
const LOG_LEVEL_INFO = 4;
const LOG_LEVEL_DEBUG = 5;

function Logger(context) {
    if (context) {
        this.context_ = context;
        Events = this.context_.Events;
        this.eventbus_ = this.context_.eventbus;
    }

    this.logToBrowserConsole_ = true;
    this.showLogTimestamp_ = true;
    this.showCalleeName_ = true;
    this.startTime_ = new Date().getTime();
}

/**
 * Prepends a timestamp in milliseconds to each log message.
 * @param {boolean} value Set to true if you want to see a timestamp in each log message.
 * @default false
 * @memberof module:Logger
 * @instance
 */
Logger.prototype.setLogTimestampVisible = function (value) {
    this.showLogTimestamp_ = value;
};

/**
 * Prepends the callee object name, and media type if available, to each log message.
 * @param {boolean} value Set to true if you want to see the callee object name and media type in each log message.
 * @default false
 * @memberof module:Logger
 * @instance
 */
Logger.prototype.setCalleeNameVisible = function (value) {
    this.showCalleeName_ = value;
};


/**
 * Toggles logging to the browser's javascript console.  If you set to false you will still receive a log event with the same message.
 * @param {boolean} value Set to false if you want to turn off logging to the browser's console.
 * @default true
 * @memberof module:Logger
 * @instance
 */
Logger.prototype.setLogToBrowserConsole = function (value) {
    this.logToBrowserConsole_ = value;
};

/**
 * Use this method to get the state of this.logToBrowserConsole_.
 * @returns {boolean} The current value of this.logToBrowserConsole_
 * @memberof module:Logger
 * @instance
 */
Logger.prototype.getLogToBrowserConsole = function () {
    return this.logToBrowserConsole_;
};

Logger.prototype.fatal = function (...params) {
    this.doLog(LOG_LEVEL_FATAL, ...params);
}

Logger.prototype.error = function (...params) {
    this.doLog(LOG_LEVEL_ERROR, ...params);
}

Logger.prototype.warn = function (...params) {
    this.doLog(LOG_LEVEL_WARNING, ...params);
}

Logger.prototype.info = function (...params) {
    this.doLog(LOG_LEVEL_INFO, ...params);
}

Logger.prototype.debug = function (...params) {
    this.doLog(LOG_LEVEL_DEBUG, ...params);
}

Logger.prototype.log = function (...params) {
    this.doLog(LOG_LEVEL_DEBUG, ...params);
}

Logger.prototype.getTime = function () {
    let logTime = new Date();
    message += '[' + ('0' + (logTime.getMonth() + 1)).slice(-2) + '-' +
        ('0' + logTime.getDate()).slice(-2) + ' ' +
        ('0' + logTime.getHours()).slice(-2) + ':' +
        ('0' + logTime.getMinutes()).slice(-2) + ':' +
        ('0' + logTime.getSeconds()).slice(-2) + '.' +
        ('0' + logTime.getMilliseconds()).slice(-3) + ']';
    return logTime;
};

/**
 * This method will allow you send log messages to either the browser's console and/or dispatch an event to capture at the media player level.
 * @param {...*} arguments The message you want to log. The Arguments object is supported for this method so you can send in comma separated logging items.
 * @memberof module:Logger
 * @instance
 */
Logger.prototype.doLog = function (level, ...params) {
    let message = '';
    let logTime = null;

    if (this.showLogTimestamp_) {
        // old from dashjs
        //logTime = new Date().getTime();
        //message += '[' + (logTime - this.startTime_) + ']';
        // new by oldmtn
        logTime = new Date();
        message += '[' + ('0' + (logTime.getMonth() + 1)).slice(-2) + '-' +
            ('0' + logTime.getDate()).slice(-2) + ' ' +
            ('0' + logTime.getHours()).slice(-2) + ':' +
            ('0' + logTime.getMinutes()).slice(-2) + ':' +
            ('0' + logTime.getSeconds()).slice(-2) + '.' +
            ('0' + logTime.getMilliseconds()).slice(-3) + ']';
    }

    // if (this.showCalleeName_ && this && this.getClassName) {
    //   message += '[' + this.getClassName() + ']';
    //   if (this.getType) {
    //     message += '[' + this.getType() + ']';
    //   }
    // }

    // if (message.length > 0) {
    //     message += ' ';
    // }

    // Array.apply(null, params).forEach(function (item) {
    //     message += item + ' ';
    // });

    switch (level) {
        case LOG_LEVEL_NONE:
        case LOG_LEVEL_FATAL:
        case LOG_LEVEL_ERROR:
        case LOG_LEVEL_WARNING: {
            console.warn(message, ...params);
        } break;
        case LOG_LEVEL_INFO:
        case LOG_LEVEL_DEBUG: {
            console.log(message, ...params);
        } break;
        default:
            break;
    }

    if (this.eventbus_) {
        this.eventbus_.trigger(Events.LOG, {
            message: message
        });
    }
}


var logger = new Logger();

module.exports = { logger };

