type CallbackStyleOptions<D = any, E = any> = {
  success(data: D): void;
  fail(e: E): void;
}

type InferData<T> = T extends CallbackStyleOptions<infer Data> ? Data : unknown;

type CallbackStyleFn<Params> = (options: Params) => void;
type PromiseStyleFn<Params> = (options: Params) => Promise<InferData<Params>>;

export function promisify<Params>(fn: CallbackStyleFn<Params>): PromiseStyleFn<Params> {
  return function wrapper(this: any, params: Params) {
    return new Promise((resolve, reject) => {
      fn.call(this, {
        ...params,
        success(data: any) {
          resolve(data);
        },
        fail(e: any) {
          console.error('error:', e);
          reject(e);
        },
      })
    });
  }
}
