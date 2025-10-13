#ifndef _LENS_ALGORITHM_ENGINE_H_
#define _LENS_ALGORITHM_ENGINE_H_

#ifndef LENS_EXPORT
#ifdef _WIN32
    #define LENS_EXPORT __declspec(dllexport)
#elif __APPLE__
    #define LENS_EXPORT
#elif __ANDROID__
    #define LENS_EXPORT __attribute__ ((visibility("default")))
#elif __linux__
    #define LENS_EXPORT __attribute__ ((visibility("default")))
#endif
#endif

#include "lens/include/LensConfigType.h"
#include <vector>
#include <memory>
#include <functional>

namespace LENS {
namespace FRAMEWORK {

// custom operator node
typedef std::function<bool(LensAlgorithmType algType,void* in_buffer,void* out_buffer)> piplineCustomOpCallBack;
typedef std::function<bool(LensAlgorithmType algType,void* out_buffer)> piplineInterruptCallBack;
typedef void (*lens_generic_proc)();
typedef lens_generic_proc (*lens_get_proc_func)(const char*);
typedef void (*lens_log_fallback)(int, const char*, const char*);

// asynchronous callback interface
class LENS_EXPORT ILensAsyncOutputListener {
public:
    virtual ~ILensAsyncOutputListener() {}

    virtual void OnStreamData(std::vector<void*>* out_buffers,void* attr) const = 0;
    virtual void OnStreamData(void* out_buffer,void* attr) const = 0;

    virtual void OnTextureData(std::vector<int>* out_textures,void* attr) const = 0;
    virtual void OnTextureData(int* out_texture,void* attr) const = 0;

    virtual void OnEvent(LensCode error_code, const char* error_msg = nullptr) const = 0;
};

//oem manufacturer capability encapsulation interface
class LENS_EXPORT IVendorAlgorithmInterface {
public:
    virtual ~IVendorAlgorithmInterface() {}
    virtual int AntiShake(unsigned char *src_data, double *affine_matrix) = 0;
 };

class LENS_EXPORT ICvAcceleratedOperatorInterface {
public:
    virtual ~ICvAcceleratedOperatorInterface() {}
	//virtual int findHomography(point2f *src, point2f *dst, int method, double ransacReprojThreshold) = 0;
};

//image quality algorithm encapsulation interface
class LENS_EXPORT ILensFlowGraphInterface {
public:
    virtual ~ILensFlowGraphInterface() {}

    virtual LensCode Init(LensBackendType backend_type,void* param) = 0;
    virtual LensCode UnInit() = 0;

    virtual LensCode SetAsyncOutputListener(std::shared_ptr<ILensAsyncOutputListener> listener) = 0;
    virtual LensCode SetPiplineCallBack(const piplineCustomOpCallBack& before, const piplineInterruptCallBack& end) = 0;

    virtual LensCode ExecuteStream(std::vector<void*> &in_buffers,void* param) = 0;
    virtual LensCode ExecuteStream(void* in_buffer,void* param) = 0;

    virtual LensCode ExecuteTexture(std::vector<int> &in_textures,void* param) = 0;
    virtual LensCode ExecuteTexture(int in_texture,void* param) = 0;

    virtual LensCode GetStreamOutput(std::vector<void*>* out_buffers,void* attr) = 0;
    virtual LensCode GetStreamOutput(void* out_buffer,void* attr) = 0;

    virtual LensCode GetTextureOutput(std::vector<int>* out_textures,void* attr) = 0;
    virtual LensCode GetTextureOutput(int *out_texture,void* attr) = 0;

    virtual LensCode SetInputProperty(void* attr) = 0;
    virtual LensCode GetOutputProperty(void* attr) = 0;
};

class LENS_EXPORT IOneKeyGraphInterface {
public:
    virtual ~IOneKeyGraphInterface() {}
    virtual LensCode Init(OneKeySceneStrategyConfig &config) = 0;
    virtual LensCode Process(OneKeySceneInput *input) = 0;
    virtual LensCode GetOutput(OneKeySceneOutput* output) = 0;
    virtual LensCode DeInit() = 0;
};

//lens engine interface
class LENS_EXPORT ILensEngineInterface {
public:
    virtual ~ILensEngineInterface() {}
    virtual void SetLogCallback(std::function<void(int,const char*,const char*)> log_callback) = 0;
    virtual int SetLicenseInfo(const char *lic_file, const char *appid) = 0;

    virtual ILensFlowGraphInterface *CreateFlowGraphAlgorithm(LensAlgorithmType algorithm_type) = 0;
    virtual void ReleaseFlowGraphAlgorithm(ILensFlowGraphInterface *instance) = 0;

    virtual IOneKeyGraphInterface *CreateOneKeyGraphAlgorithm(OneKeySceneStrategyMode mode) = 0;
    virtual void ReleaseOneKeyGraphAlgorithm(IOneKeyGraphInterface *instance) = 0;

    virtual ICvAcceleratedOperatorInterface *CreateCvOperator() = 0;
    virtual void ReleaseCvOperator(ICvAcceleratedOperatorInterface *instance) = 0;

    virtual IVendorAlgorithmInterface *CreateVendorAlgorithm() = 0;
    virtual void ReleaseVendorAlgorithm(IVendorAlgorithmInterface *instance) = 0;
};

class LENS_EXPORT CVLensEngineFactory {
public:
    static ILensEngineInterface *CreateLensEngine(const char* path, int* error_code);
    static ILensEngineInterface *CreateLensEngine(const char* licenseBuffer, const unsigned long length, int* error_code);
    static void ReleaseLensEngine(ILensEngineInterface* instance);
};

class LENS_EXPORT LensUtils {
public:
    static void SetLogCallback(lens_log_fallback logCallback);  // set lens log callback
    static void LoadEGLLibrary(const char* path);       // load egl library with library path
    static void UnLoadEGLLibrary();                     // unload after LoadEGLLibrary
    static void LoadGLESLibrary(const char* path);      // load gles library with library path
    static void UnLoadGLESLibrary();                    // unload after LoadGLESLibrary
    static void LoadEGL(lens_get_proc_func loadProc);   // load egl library with proc_func
    static void LoadGLES(lens_get_proc_func loadProc);  // load gles library with proc_func
};

} /* namespace FRAMEWORK */
} /* namespace LENS */

#endif //_LENS_ALGORITHM_ENGINE_H_
