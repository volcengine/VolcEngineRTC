#pragma once
#include "bef_effect_ai_public_define.h"
#include <iostream>
#include <map>

namespace EffectsSDK {

typedef struct RequestInfo{
    std::string url;
    std::map<std::string, std::string> requestHead;
    const char* bodydata;
    int bodySize;
    void* userdata;

} RequestInfo;

typedef struct ResponseInfo{
    int status_code;
    std::map<std::string, std::string> responseHead;
    char* bodydata;
    int bodySize;
    void* userdata;
} ResponseInfo;

class HttpRequestProvider
{
public:
    virtual ~HttpRequestProvider() {}
    virtual bool getRequest(const RequestInfo* request, ResponseInfo& response) = 0;
    virtual bool postRequest(const RequestInfo* request, ResponseInfo& response) = 0;
};

typedef struct ErrorInfo {
    int errorCode;
    std::string errorMsg;
} ErrorInfo;

typedef void (*licenseCallback)(const char* retmsg, int retSize, ErrorInfo error, void* userdata);


/*
params: <mode:license模式，必需， OFFLINE/ONLINE/ACCOUNT 对应 离线/在线/账号>
        <licensePath:自定义license路径，不用可不传>
        <url:请求的url， 离线模式不需要>
        <key:  仅用于在线请求的key，其他模式可不传>
        <secret：仅用于在线请求的secret, 其他模式可不传>
        <ticket：仅用于账号模式的票据值，其他模式可不传>
        <deviceId: 仅用于账号模式的设备id值，其他模式可不传>
*/

class LicenseProvider
{
public:
    virtual ~LicenseProvider() {}

    static LicenseProvider* GetInstanceWithParam(const std::map<std::string, std::string>& params, HttpRequestProvider* provider = NULL);
    /*
     getLicenseWithParams 支持带参数去获取license，也可以提前通过setParam传入参数，这里传空，会去使用提前设置好的参数
     三种模式：
          1.离线模式, 可以不依赖其他参数，licensePath是可选项，固定为同步操作
          2.在线模式, url,key和secret为必需项，licensePath为可选项,其他不需要，本地不存在的话，才会去发起请求，否则直接返回本地license文件
          3.账号模式, url,ticket和deviceId为必需项，其他不需要
     params: 用来获取license的参数，这里设置的参数只用来请求，不对原本的参数进行替换
     isAsyn: 是否为异步请求，对离线模式无效
     callback: 返回结果的回调函数
     */
    virtual int getLicenseWithParams(const std::map<std::string, std::string>& params, bool isAsyn, licenseCallback callback, void* userdata = NULL) = 0;
    
    /*
     updateLicenseWithParams 支持带参数去更新本地的license文件，也可以提前通过setParam传入参数，这里传空，会去使用提前设置好的参数
     仅支持在线模式，url,key和secret为必需项，licensePath为可选项，每次都会去更新本地的license
     params: 用来获取license的参数，这里设置的参数只用来请求，不对原本的参数进行替换
     isAsyn: 是否为异步请求
     callback: 返回结果的回调函数
     */
    virtual int updateLicenseWithParams(const std::map<std::string, std::string>& params, bool isAsyn, licenseCallback callback, void* userdata = NULL) = 0;
    
    /*
     registerHttpProvider 为用户提供网络注入
     provider: 用户实现的HttpRequestProvider对象，用户注册之后，网络请求部分会使用用户的实现
     */
    virtual void registerHttpProvider(HttpRequestProvider* provider) = 0;
    
    /*
     setParam 设置参数
     name:  参数名
     value: 参数值
     */
    virtual void setParam(const std::string& name, const std::string& value) = 0;
    
    virtual std::string getParam(const std::string& name) = 0;
    
    virtual void clearParams() = 0;
    
};

}

BEF_SDK_API EffectsSDK::LicenseProvider* bef_effect_ai_get_license_wrapper_instance();
