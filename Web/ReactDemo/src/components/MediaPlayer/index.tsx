import React from 'react';

export interface VideoPlayerProps {
  userId: string;
  //   setRemoteVideoPlayer: any;
}

const MediaPlayer: React.FC<VideoPlayerProps> = ({ userId }) => {
  //   const dom = useRef<any>();
  //   useLayoutEffect(() => {
  //     if (setRemoteVideoPlayer && dom) {
  //       setRemoteVideoPlayer(userId, `remoteStream_${userId}`);
  //     }
  //   }, [setRemoteVideoPlayer, userId]);

  return (
    <div
      style={{ width: '100%', height: '100%', position: 'relative', background: '#000' }}
      className="remoteStream"
      id={`remoteStream_${userId}`}
      //   ref={dom}
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
