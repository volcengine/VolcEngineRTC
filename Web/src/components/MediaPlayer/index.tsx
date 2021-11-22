import React, {useState, useEffect} from 'react';
import {v4 as uuid} from 'uuid';
import { Stream } from '../../app-interfaces';

export interface VideoPlayerProps {
  stream: Stream | undefined;
  userId: string;
}

const MediaPlayer: React.FC<VideoPlayerProps> = ({stream, userId}) => {

  const [id] = useState<string>(uuid());

  useEffect(() => {
    if (stream) {
      stream.play(id, {
        fit: 'cover',
      });
    }
  }, [id, stream]);

  return (
    <div style={{width: '100%', height: '100%', position: 'relative'}} id={id}>
      <span
        style={{
          color: '#fff',
          position: 'absolute',
          bottom: 0,
          right: 0,
          zIndex: 1000,
        }}
      >
        {userId}
      </span>
    </div>
  );
};

export default MediaPlayer;