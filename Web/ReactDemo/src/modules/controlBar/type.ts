
import {RTCClient} from '../../app-interfaces';


export interface ICommonProps {
    changeHooks?: <T>(arg?: T) => void;
    RClient?: Nullable<RTCClient>;
}

interface IModuleConf{
    moduleName: string;
    moduleProps: {
        [key: string]: any
    };
    visible?: boolean;
}

export interface IControlBarProps {
    systemConf?: Array<IModuleConf>;
    moduleConf?: Array<IModuleConf>;
    RClient?: any;
}