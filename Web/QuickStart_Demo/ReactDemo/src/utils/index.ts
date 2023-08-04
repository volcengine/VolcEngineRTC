/**
 * @brief get query string
 * @param {string} name
 * @returns {string | null}
 */
export const getQueryString = (name: string): string | null => {
  const reg = new RegExp('(^|&)' + name + '=([^&]*)(&|$)', 'i');
  const reg_rewrite = new RegExp('(^|/)' + name + '/([^/]*)(/|$)', 'i');
  const r = window.location.search.substr(1).match(reg);
  const q = window.location.pathname.substr(1).match(reg_rewrite);
  if (r != null) {
    return unescape(r[2]);
  } else if (q != null) {
    return unescape(q[2]);
  } else {
    return null;
  }
};

export function removeLoginInfo() {
  const variable = ['roomId', 'uid'];
  variable.forEach((v) => sessionStorage.removeItem(v));
}

export function setSessionInfo(params: { [key: string]: any }) {
  Object.keys(params).forEach((key) => {
    sessionStorage.setItem(key, params[key]);
  });
}

export function getSessionInfo() {
  const roomId = sessionStorage.getItem('roomId');
  const uid = sessionStorage.getItem('uid');
  return {
    roomId,
    uid,
  };
}

export function getUrlArgs() {
  const args = {} as { [key: string]: string };
  const query = window.location.search.substring(1);
  const pairs = query.split('&');
  for (let i = 0; i < pairs.length; i++) {
    const pos = pairs[i].indexOf('=');
    if (pos == -1) continue;
    const name = pairs[i].substring(0, pos);
    let value = pairs[i].substring(pos + 1);
    value = decodeURIComponent(value);
    args[name] = value;
  }
  return args;
}

export function checkLoginInfo() {
  const { roomId } = getUrlArgs();
  roomId && setSessionInfo({ roomId });

  const _roomId = roomId;
  const _uid = sessionStorage.getItem('uid');

  let hasLogin = true;
  if (!_roomId || !_uid) {
    hasLogin = false;
  } else if (
    !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(_roomId) ||
    !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(_uid)
  ) {
    hasLogin = false;
  }

  return hasLogin;
}
