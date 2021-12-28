import React from 'react';
import { IMicProps,  } from './type';
import IconBlock from 'src/components/IconBlock';

import micOnIcon from 'src/assets/images/micOnIcon.png';
import micOffIcon from 'src/assets/images/micOffIcon.png';


const MicroPhone: React.FC<IMicProps> = ({ changeHooks, isMicOn }) => {
  return (
    <IconBlock onClick={() => changeHooks && changeHooks()} size={20}>
      <img src={isMicOn ? micOnIcon : micOffIcon} />
    </IconBlock>
  );
};

export default MicroPhone;