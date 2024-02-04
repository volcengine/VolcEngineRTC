const host = 'https://rtc.bytedance.com'
const baseUrl = '/vertc_demo';

function resolveUri(pathname: string) {
  return `${host}${baseUrl}${pathname}`
}

export type RequestResponse<T> = {
  statusCode: number;
  errMsg?: string;
  data: T;
}

export type ApiResponse<T> = {
  code: number;
  message: string;
  message_type: string;
  request_id: string;
  response: T;
}

export function get<T = any>(
  pathname: string,
  options: {
    header?: Record<string, string>;
    dataType?: string;
    responseType?: string;
  } = {}
) {
  const url = resolveUri(pathname);
  return new Promise((resolve, reject) => {
    tt.request({
      url,
      header: {
        'content-type': 'application/json',
        ...(options.header || {}),
      },
      method: 'GET',
      dataType: options.dataType || 'json',
      responseType: options.responseType || 'text',
      success(res) {
        const { statusCode, data, errMsg } = res;
        if (statusCode >= 400) {
          console.log(`网络请求失败`, url, errMsg);
          tt.showToast({ title: '网络失败', icon: 'fail' });
          reject(res);
          return;
        }

        const { code, message, response } = data as unknown as ApiResponse<T>;
        if (code !== 200) {
          console.log(`服务端错误`, url, message);
          tt.showToast({ title: '服务错误:' + message, icon: 'fail' });
          reject(data);
          return;
        }

        resolve(response);
      },
      fail(err) {
        reject(err);
      },
    });
  });
}

export function post<T = any>(
  pathname: string,
  data: any,
  options: {
    header?: Record<string, string>;
    dataType?: string;
    responseType?: string;
  } = {}
) {
  const url = resolveUri(pathname);
  return new Promise<T>((resolve, reject) => {
    tt.request({
      url,
      data,
      header: {
        'content-type': 'application/json',
        ...(options.header || {}),
      },
      method: 'POST',
      dataType: options.dataType || 'json',
      responseType: options.responseType || 'text',
      success(res) {
        const { statusCode, data, errMsg } = res;
        if (statusCode >= 400) {
          console.log(`网络请求失败`, url, errMsg);
          tt.showToast({ title: '网络失败', icon: 'fail' });
          reject(res);
          return;
        }

        const { code, message, response } = data as unknown as ApiResponse<T>;
        if (code !== 200) {
          console.log(`服务端错误`, url, message);
          tt.showToast({ title: '服务错误:' + message, icon: 'fail' });
          reject(data);
          return;
        }

        resolve(response);
      },
      fail(err) {
        reject(err);
      },
    });
  });
}
