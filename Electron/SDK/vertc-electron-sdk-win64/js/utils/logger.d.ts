export var logger: Logger;
declare function Logger(context: any): void;
declare class Logger {
    constructor(context: any);
    context_: any;
    eventbus_: any;
    logToBrowserConsole_: boolean;
    showLogTimestamp_: boolean;
    showCalleeName_: boolean;
    startTime_: number;
    setLogTimestampVisible(value: boolean): void;
    setCalleeNameVisible(value: boolean): void;
    setLogToBrowserConsole(value: boolean): void;
    getLogToBrowserConsole(): boolean;
    fatal(...params: any[]): void;
    error(...params: any[]): void;
    warn(...params: any[]): void;
    info(...params: any[]): void;
    debug(...params: any[]): void;
    log(...params: any[]): void;
    getTime(): Date;
    doLog(level: any, ...params: any[]): void;
}
export {};
