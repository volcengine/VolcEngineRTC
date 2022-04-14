import React, { useLayoutEffect, useRef } from 'react';

export interface VideoPlayerProps {
  userId: string;
  setRemoteVideoPlayer: any;
  stream: any;
}

const MediaPlayer: React.FC<VideoPlayerProps> = ({
  userId,
  setRemoteVideoPlayer,
  stream,
}) => {
  const dom = useRef<any>();
  useLayoutEffect(() => {
    if (setRemoteVideoPlayer && dom) {
      setRemoteVideoPlayer(userId, `remoteStream_${userId}`, stream);
    }
  }, [setRemoteVideoPlayer, stream, userId]);

  return (
    <div
      style={{width: '100%', height: '100%', position: 'relative'}}
      className='remoteStream'
      id={`remoteStream_${userId}`}
      ref={dom}
    >
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