/**
 * @brief get query string
 * @param {string} name
 * @returns {string | null}
 */
export const getQueryString = (name: string): string | null  => {
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