import React from 'react';
import IconBlock from 'src/components/IconBlock';
import {IVideoProps} from './type';

import videoOnIcon from 'src/assets/images/videoOnIcon.png';
import videoOffIcon from 'src/assets/images/videoOffIcon.png';


const VideoControl: React.FC<IVideoProps> = ({
  changeHooks,
  isVideoOn
}) => {
  return (
    <IconBlock onClick={() => changeHooks && changeHooks()} size={28}>
      <img src={isVideoOn ? videoOnIcon : videoOffIcon} />
    </IconBlock>
  );
};

export default VideoControl;