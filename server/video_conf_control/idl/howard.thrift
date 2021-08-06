include "base.thrift"
namespace go howard

struct CleanVideoRequest {
    1: required string Vid    #Vid
    2: required string IdentityInfo   #身份认证信息,服务正式上线之前会已sdk的形式提供
    3: optional map<string,string> CallbackArgs #如果需要回调联系@gaohonglei注册回调,将该参数回调时原样返回
    4: optional string QTag   #rocketmq 消息tag

    255: optional base.Base Base
}

struct CleanVideoResponse {
    255: base.BaseResp BaseResp
}

service HowardService {
    //CleanVideo: 物理删除vid下的所有内容，不做备份,封面图/抽帧图/转码视频/原片等，包括cdn缓存/oss/tos等
    //整个清理操作是异步执行,如果业务需要执行结果，可以联系注册回调，会将清理结果回调给业务方
    //清理任务如果超过1h默认处理失败，会将处理结果回调给业务方
    CleanVideoResponse CleanVideo(1: CleanVideoRequest request)
}
