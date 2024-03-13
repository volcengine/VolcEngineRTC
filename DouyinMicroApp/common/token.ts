import { Token } from '../constant';

/**
 * 获取 token
 * @param roomId 
 * @param userId 
 */
export async function fetchToken(roomId: string, userId: string) {
  return {
    token: Token,
    userId: userId,
    roomId: roomId,
  };
}
