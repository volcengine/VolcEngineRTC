function getUrlArgs() {
  var args = {};
  var query = window.location.search.substring(1);
  var pairs = query.split('&');
  for (var i = 0; i < pairs.length; i++) {
    var pos = pairs[i].indexOf('=');
    if (pos == -1) continue;
    var name = pairs[i].substring(0, pos);
    var value = pairs[i].substring(pos + 1);
    value = decodeURIComponent(value);
    args[name] = value;
  }
  return args;
}

function setSessionInfo(params) {
  Object.keys(params).forEach((key) => {
    sessionStorage.setItem(key, params[key]);
  });
}

function removeLoginInfo() {
  const variable = ['roomId', 'uid', 'scene'];
  variable.forEach((v) => sessionStorage.removeItem(v));
}

function checkLoginInfo() {
  const { roomId, userId } = getUrlArgs();
  roomId && setSessionInfo({ roomId });
  userId && setSessionInfo({ uid: userId });

  const _roomId = roomId || sessionStorage.getItem('roomId');
  const _uid = userId || sessionStorage.getItem('uid');
  const scene = sessionStorage.getItem('scene');

  let hasLogin = true;
  if (!_roomId || !_uid) {
    hasLogin = false;
  } else if (
    !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(_roomId) ||
    !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(_uid)
  ) {
    hasLogin = false;
  }
  return { hasLogin, _roomId, _uid, scene };
}

window.checkLoginInfo = checkLoginInfo;
window.getUrlArgs = getUrlArgs;
window.setSessionInfo = setSessionInfo;
window.removeLoginInfo = removeLoginInfo;