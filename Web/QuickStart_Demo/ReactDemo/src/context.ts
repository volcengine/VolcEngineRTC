import React from 'react';
export const Context = React.createContext({} as {
  roomId: string;
  userId: string;
  joinFailReason: string;
  hasJoin: boolean;
  setUserId: React.Dispatch<React.SetStateAction<string>>;
  setRoomId: React.Dispatch<React.SetStateAction<string>>;
  setJoin: React.Dispatch<React.SetStateAction<boolean>>;
  setJoinFailReason: React.Dispatch<React.SetStateAction<string>>;
});
