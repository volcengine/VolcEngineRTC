
#ifndef effectsSDK_effect_pixelformat_cvt_h
#define effectsSDK_effect_pixelformat_cvt_h

#include <stdio.h>
#ifdef __ANDROID__
  #include <GLES2/gl2.h>
  #define GL_GLEXT_PROTOTYPES
  #include <GLES2/gl2ext.h>

  #define EGL_EGLEXT_PROTOTYPES
  #include <EGL/egl.h>
  #include <EGL/eglext.h>
#if !BEF_EFFECT_ANDROID_WITH_JNI
  #include <android/hardware_buffer.h>
#endif
#else
  #include <OpenGLES/ES2/gl.h>
  #include <OpenGLES/ES2/glext.h>
#endif
#include "bef_effect_ai_public_define.h"
#include "bef_effect_ai_log.h"

#define HAL_FIRST_FRAME_CNT 3

enum ConvertType{
  NV21ToRGBA,//android
  NV12ToRGBA,
  I420ToRGBA,//android camera2 format
  //nv12
  BT601ToRGBA,//ios
  BT601FullToRGBA,//ios
  BT709ToRGBA,//ios
  
  RGBAToNV12,
  RGBAToNV21,
  RGBAToI420,
};

class EffectsSDKOpenGLProgram2{
private:
  GLuint _program;
  GLuint _vertShader;
  GLuint _fragShader;
  
public:
  int init(const char* v_shade, const char* f_shade);
  ~EffectsSDKOpenGLProgram2();
  bool compileShader(GLuint *shader, GLenum type, const char* shader_str);
  bool linkProgram();
  void useProgram();

  void addAttribute(GLuint index, const char *attributeName);
  GLuint uniformIndex(const char *uniformName);
};

class PixelFormatConvertor2{
public:
  PixelFormatConvertor2(ConvertType type);
  ~PixelFormatConvertor2();
  int init(ConvertType type);
  int setupProgram(const char* v_shade, const char* f_shade);
  int cvtTextureToBuf(int width, int height, GLuint texture, bef_ai_pixel_format format, unsigned char**pixelBuffer);
  
#if BEF_EFFECT_ANDROID_WITH_JNI
  GLuint cvtYUVBufToTexture(int width, int height, unsigned char * buf);
  int cvtTexture2YUVBuf(int width, int height, GLuint RGBATexture, unsigned char**buf_yuv);
#else
  GLuint cvtYUVBufToTexture(int width, int height, unsigned char* pixelBuffer, bef_ai_camera_position is_front, bef_ai_rotate_type orientation);
  void updateYuvData(int width, int height, uint8_t *yuv_buf);
  void adapt_out_yuv_format(int width, int height, unsigned char** buf_yuv, AHardwareBuffer_Planes outPlanes);
  void adapt_in_yuv_format(int width, int height, uint8_t* buf_yuv, uint8_t* nv21_buf);
  void init_hardware_buffer(int width, int height, unsigned int usage_outside);
  void copyNv21DataPadding(uint8_t*src_y, uint8_t*src_v, uint8_t*dst_y, uint8_t*dst_v, int width, int height, int src_stride, int dst_stride);
  int cvtTexture2YUVBuf(int width, int height, GLuint RGBATexture, unsigned char**buf_yuv, bef_ai_process_type previewMode, bef_ai_camera_position is_front, bef_ai_rotate_type orientation);
#endif
  //NOT convert, make sure input is a rgba buffer
    GLuint BufToTexture(int width, int height, bef_ai_pixel_format format, unsigned char* pixelBuffer);
private:
  EffectsSDKOpenGLProgram2 _program;
  const GLfloat convert601torgba[9] = { 1.164, 1.164, 1.164, 0.0, -0.391, 2.018, 1.596, -0.813, 0.0};
  const GLfloat convert601fulltorgba[9] = { 1.0, 1.0, 1.0, 0.0, -0.343, 1.765, 1.4, -0.711, 0.0};
  const GLfloat convert709torgba[9] = { 1.164, 1.164, 1.164, 0.0, -0.213, 2.112, 1.793, -0.533, 0.0};
  const GLfloat convertrgba[9] = {0.299, -0.1678, 0.5, 0.587, -0.3313, -0.4187, 0.114, 0.5, -0.0813};
  const GLfloat rotate_model270[16] = {0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat rotate_model90[16] = {0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat flip_modelY[16] = {-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat flip_modelX[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat unit_matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  int buf_inited;
  int init_buf(int width, int height);

#if !BEF_EFFECT_ANDROID_WITH_JNI
  bool hardware_buffer_inited = false;
  AHardwareBuffer* hardWareBuf = nullptr;
  int hardware_buffer_stride = 0;
  int preview_gl_finifh = 1;
  EGLImageKHR imageEGL;
  GLuint OEStextureId = 0;
  unsigned int yuv_y_size = 0;
  unsigned int half_yuv_y_size = 0;
  unsigned int quarter_yuv_y_size = 0;
  uint8_t *dst_i420_u = nullptr;
  uint8_t *dst_i420_v = nullptr;
  uint8_t *nv21_buf   = nullptr;
#endif

  const char* vertex_shader = "\n\
  attribute vec4 position;\n \
  attribute vec2 textureCoord; \n \
  varying highp vec2 m_textureCoord; \n \
  uniform mat4 transform_rotate_model;  \n \
  uniform mat4 transform_flip_model;  \n \
  void main() \n \
  { \n \
  m_textureCoord = textureCoord; \n \
  gl_Position =  transform_flip_model * transform_rotate_model * position; \n \
  } \n \
  \n";
  const char* fragment_shader_601NV21ToRGBA = "\n \
  varying highp vec2 m_textureCoord; \n \
  precision highp float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV;\n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  highp vec3 yuv; \n \
  highp vec3 rgb; \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r) - (16.0/255.0); \n \
  yuv.yz = (texture2D(SamplerUV, m_textureCoord).ar - vec2(0.5, 0.5)); \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";
  const char* fragment_shader_NV21ToRGBA = "\n \
  varying highp vec2 m_textureCoord; \n \
  precision highp float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV;\n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  highp vec3 yuv; \n \
  highp vec3 rgb; \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r); \n \
  yuv.yz = (texture2D(SamplerUV, m_textureCoord).ar - vec2(0.5, 0.5)); \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";

  const char* fragment_shader_NV12ToRGBA = "\n \
  varying highp vec2 m_textureCoord; \n \
  precision highp float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV;\n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  highp vec3 yuv; \n \
  highp vec3 rgb; \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r); \n \
  yuv.yz = (texture2D(SamplerUV, m_textureCoord).ra - vec2(0.5, 0.5)); \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";

  const char* fragment_shader_I420ToRGBA = "\n \
  varying highp vec2 m_textureCoord; \n \
  precision highp float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV; \n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  highp vec3 yuv; \n \
  highp vec3 rgb; \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r); \n \
  yuv.y = (texture2D(SamplerU, m_textureCoord).r) - 0.5; \n \
  yuv.z = (texture2D(SamplerV, m_textureCoord).r) - 0.5; \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";

 const char* fragment_shader_RGBAToYUV = "\n \
  varying lowp vec2 m_textureCoord; \n \
  precision mediump float; \n \
  uniform sampler2D SamplerRGBA; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  mediump vec3 rgb; \n \
  mediump vec3 yuv; \n \
  rgb = (texture2D(SamplerRGBA, m_textureCoord).rgb); \n\
  yuv = colorConversionMatrix * rgb+vec3(0, 0.5, 0.5); \n \
  gl_FragColor = vec4(yuv,1); \n \
  } \n \
  \n ";

const char* vertex_shader_OutYUV = 
  "#version 300 es \n \
  layout (location = 0) in vec3 position; \n \
  layout (location = 1) in vec2 aTexCoords; \n \
  out vec2 TexCoords; \n \
  uniform mat4 transform_rotate_model; \n \
  uniform mat4 transform_flip_model; \n \
  void main() \n \
  { \n \
    TexCoords = aTexCoords; \n \
    gl_Position = transform_flip_model * transform_rotate_model * vec4(position.x, position.y, position.z, 1.0); \n \
  } \n \
  \n ";

const char* fragment_shader_OutYUV =
  "#version 300 es \n \
  #extension GL_OES_EGL_image_external_essl3 : require \n \
  #extension GL_EXT_YUV_target : require \n \
  precision highp float; \n \
  in vec2 TexCoords; \n \
  layout (yuv) out vec3 outColor; \n \
  uniform int rgbToyuvType; \n \
  uniform sampler2D SamplerRGBA; \n \
  void main() \n \
  { \n \
    vec4 color = texture(SamplerRGBA, TexCoords); \n \
    vec3 colorRgb = color.rgb; \n \
    outColor = rgb_2_yuv(colorRgb, itu_601_full_range); \n \
  } \n \
  \n ";

  GLuint frameBuffer;
  GLuint output_texture;
  GLint fboOld;
  
  GLint positionAttribute, textureCoordAttribute;
  
  GLint SamplerY, SamplerUV, colorConversionMatrixUniform, rotateMatrixUniform, flipMatrixUniform;

  GLint SamplerU, SamplerV;
  
  GLint SamplerRGBA;

  const GLfloat *_preferredConversion;
  
  GLuint luminanceTexture = 0;
  GLuint chrominanceTexture = 0;
  
  GLuint UTexture = 0;
  GLuint VTexture = 0;
  GLuint RGBATexture = 0;
  
  ConvertType convert_type;
};
#endif /* PixelFormatConvertor2_h */
