#ifndef CNAMASDK_IMAGE_BEAUTY_H
#define CNAMASDK_IMAGE_BEAUTY_H

#ifdef _WIN32
#ifdef NAMA_BUILD_SHARED_LIB
#define FUNAMA_API __declspec(dllexport)
#else
#define FUNAMA_API
#endif
#else
#define FUNAMA_API __attribute__((visibility("default")))
#endif
#ifdef __cplusplus
extern "C" {
#endif
typedef enum FuImageBeautyStatus {
  FU_IMAGE_BEAUTY_STATUS_UNKNOWN = -1,
  FU_IMAGE_BEAUTY_STATUS_OK = 0,
  FU_IMAGE_BEAUTY_STATUS_NO_CONTEXT,
  FU_IMAGE_BEAUTY_STATUS_GL_NOTSUPPORT,
  FU_IMAGE_BEAUTY_STATUS_CONTROLLER_NOTFOUND,
  FU_IMAGE_BEAUTY_STATUS_NO_FACE_DETECT,
  FU_IMAGE_BEAUTY_STATUS_LAYERS_ERROR,
  FU_IMAGE_BEAUTY_STATUS_INVALID_ARGUMENT,
  FU_IMAGE_BEAUTY_STATUS_UNINITIALIZED,
  FU_IMAGE_BEAUTY_STATUS_NULLPTR,
  FU_IMAGE_BEAUTY_STATUS_BITMAP_INFO,
  FU_IMAGE_BEAUTY_STATUS_BITMAP_8888,
  FU_IMAGE_BEAUTY_STATUS_BITMAP_LOCK,
  FU_IMAGE_BEAUTY_STATUS_CACHE_DIR_EMPTY,
} FuImageBeautyStatus;

typedef struct FuImageView {
  int format;  // one of FU_FORMAT_***
  int tex_id;  // unused
  int width;
  int height;
  void* data0;
  int stride0;
  void* data1;
  int stride1;
  void* data2;
  int stride2;
} FuImageView;

typedef enum FuImageBeautyProcessMode {
  FU_IMAGE_BEAUTY_MODE_UNKNOWN = 0,
  FU_IMAGE_BEAUTY_MODE_FACE_BEAUTY = 1,
  FU_IMAGE_BEAUTY_MODE_FACE_WARP = 1 << 1,
  FU_IMAGE_BEAUTY_MODE_BODY_SLIM = 1 << 2,
  FU_IMAGE_BEAUTY_MODE_AUTO = 1 << 3,
  FU_IMAGE_BEAUTY_MODE_AUTO_WITHOUT_ACEN_AVER = 1 << 19,
  FU_IMAGE_BEAUTY_MODE_UPLOAD = 1 << 4,
  FU_IMAGE_BEAUTY_MODE_FACE_BEAUTY_PREPROCESS = 1 << 5,
  FU_IMAGE_BEAUTY_MODE_BLUR = 1 << 6,
  FU_IMAGE_BEAUTY_MODE_ACENCANCEL= 1 << 7,
  FU_IMAGE_BEAUTY_MODE_AVER= 1 << 8,
  FU_IMAGE_BEAUTY_MODE_WRINKLE= 1 << 9,
  FU_IMAGE_BEAUTY_MODE_WHITEBLACK= 1 << 10,
  FU_IMAGE_BEAUTY_MODE_WARMCOLD= 1 << 11,
  FU_IMAGE_BEAUTY_MODE_RED= 1 << 12,
  FU_IMAGE_BEAUTY_MODE_LIGHTEYE= 1 << 13,
  FU_IMAGE_BEAUTY_MODE_SHARPENBROWN= 1 << 14,
  FU_IMAGE_BEAUTY_MODE_THREED= 1 << 15,
  FU_IMAGE_BEAUTY_MODE_JILI= 1 << 16,
  FU_IMAGE_BEAUTY_MODE_DARKCIRCLE= 1 << 17,
  FU_IMAGE_BEAUTY_MODE_DECREEPATTERN= 1 << 18,
} FuImageBeautyProcessMode;

typedef enum FuImageUndoRedoMode {
  FU_IMAGE_UNDOREDO_MODE_GAP_GREATER_THAN_ZERO = 0,
  FU_IMAGE_UNDOREDO_MODE_GAP_EQUAL_TO_ZERO = 1,
} FuImageUndoRedoMode;

typedef struct FuImageBeautyPrecessParam {
  // gpu or cpu pipeline
  int is_gpu_mode;
  int is_new_image;
  float scale_ratio;
  FuImageBeautyProcessMode process_mode;
} FuImageBeautyProcessParam;

/**
 \brief image beauty preprocess.
 \param input, define input image, refer to FuImageView.
 \param p_items points to the list of items
 \param n_items is the number of items
 \param param, define preprocess mode, cpu/gpu, preview scale ratio, eth.
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus
fuImageBeautyPreProcess(const FuImageView* input, const int* p_items,
                        int n_items, const FuImageBeautyProcessParam* param);

/**
 \brief image beauty preprocess.
 \param input, define input image, refer to FuImageView.
 \param scale, texture scale ratio, eth.
  \param result_texture, texture uploaded.
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautyCreateTexture(
    const FuImageView* input, float scale, int* result_texture);

/**
 \brief image beauty preview.
 \param result_texid, output texture id, for gl preview
 \param p_items points to the list of items
 \param n_items is the number of items
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautyPreview(unsigned int* result_texid,
                                                    const int* p_items,
                                                    int n_items);

/**
 \brief image beauty get final buffer result, support maxinum resolution 8k.
 \param output, final output buffer
 \param p_items points to the list of items
 \param n_items is the number of items
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautyGetResult(FuImageView* output,
                                                      const int* p_items,
                                                      int n_items,
                                                      bool clear_mem = false);

/**
 \brief image beauty get final buffer result and save rgba or yuv raw buffer to
 path, support maxinum resolution 12k.
 \param output, final output buffer
 \param p_items points to the list of items
 \param n_items is the number of items
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautySaveResultToPath(
    FuImageView* output, const char* path, const int* p_items, int n_items,
    bool clear_mem = false);

/**
 \brief tool func convert RGBA buffer to Nv21 buffer
 \
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus
fuImageBeautyConvertRGBA2NV21(FuImageView* input, FuImageView* output);

/**
 \brief set cache dir, path should be writeable
 \param p_items points to the list of items
 \param n_items is the number of items
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautySetCacheDir(const char* dir);

/**
 \brief save cache to sdcard, used when going into background.
 \param p_items points to the list of items
 \param n_items is the number of items
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautySaveCache(const int* p_items,
                                                      int n_items);

/**
 \brief load cache from sdcard, used when going into foreground.
 \param p_items points to the list of items
 \param n_items is the number of items
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus fuImageBeautyLoadCache(const int* p_items,
                                                      int n_items);
/**
 \brief get last result texture.
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus
fuImageBeautyGetLastResultTexture(int* result_texture);

/**
 \brief get origin texture.
 \return status, refer to FuImageBeautyStatus.
*/
FUNAMA_API FuImageBeautyStatus
fuImageBeautyGetOriginTexture(int* result_texture);

FUNAMA_API int fuImageBeautyGetParam(const int* p_items, int n_items,
                                     const char* name, char* buf, int buf_sz);

FUNAMA_API FuImageBeautyStatus fuImageBeautySetParam(const int* p_items,
                                                     int n_items,
                                                     const char* name,
                                                     const char* value);

FUNAMA_API FuImageBeautyStatus fuImageBeautySetAttributePath(char* buf);

FUNAMA_API FuImageBeautyStatus fuImageBeautySetFaceBeautyPath(char* buf);

FUNAMA_API FuImageBeautyStatus fuImageBeautySetUndoRedoMode(
    const int* p_items, int n_items, FuImageUndoRedoMode mode);

FUNAMA_API FuImageBeautyStatus fuImageBeautyCreateTextureCoverPreview(
    const FuImageView* input, float scale, int* result_texture);

FUNAMA_API void
fuImageBeautyPreProcessForImageInfo(const FuImageView* input, float scale);

FUNAMA_API FuImageBeautyStatus fuImageBeautyClearMemory(const int* p_items,
                                                      int n_items);

FUNAMA_API int fuImageBeautyGetInfo(int face_id, const char* name, void* pret,
                                    int num);

FUNAMA_API void fuProcessorChangeModel(int type);
#ifdef __cplusplus
}
#endif
#endif