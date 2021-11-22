import MicoPhoneControlModule from './microPhone';
import VideoControlModule from './videoControl';

type modulesOptions = {
  [key: string]: React.FC<any>;
};

const controlModules: modulesOptions = {
  MicoPhoneControlModule,
  VideoControlModule,
};

export default controlModules;