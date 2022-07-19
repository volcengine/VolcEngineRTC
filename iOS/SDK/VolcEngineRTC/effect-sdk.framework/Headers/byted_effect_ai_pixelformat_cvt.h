// Copyright (C) 2019 Beijing Bytedance Network Technology Co., Ltd.
#ifndef byted_effect_pixelformat_cvt_h
#define byted_effect_pixelformat_cvt_h

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
  I420ToRGBA,//android camera2 format
  //nv12
  BT601ToRGBA,//ios
  BT601FullToRGBA,//ios
  BT709ToRGBA,//ios
  
  RGBAToNV12,
  RGBAToNV21,
  RGBAToI420,
};

class BytedOpenGLProgram2{
private:
  GLuint _program;
  GLuint _vertShader;
  GLuint _fragShader;
  
public:
  int init(const char* v_shade, const char* f_shade);
  ~BytedOpenGLProgram2();
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
#else
  GLuint cvtYUVBufToTexture(int width, int height, unsigned char* pixelBuffer, bef_ai_camera_position is_front, bef_ai_rotate_type orientation);
#endif
  //NOT convert, make sure input is a rgba buffer
    GLuint BufToTexture(int width, int height, bef_ai_pixel_format format, unsigned char* pixelBuffer);

  int cvtNV12ToRGBA_CPU(int width, int height, unsigned char* buffer_nv21, unsigned char** buffer_rgba);

  int cvtRGBA2YUV(int width, int height, unsigned char* buf, unsigned char**buf_yuv);
  //for test only
  int cvtNV12ToNV21(int width, int height, unsigned char* buffer_nv12, unsigned char** buffer_nv21);
  int cvtNV12ToI420(int width, int height, unsigned char* buffer_nv12, unsigned char** buffer_i420);
  int cvtRGBAToYUV_CPU(int width, int height, unsigned char* buffer_rgba, unsigned char** buffer_yuv);
#if BEF_EFFECT_ANDROID_WITH_JNI
  int cvtTexture2YUVBuf(int width, int height, GLuint RGBATexture, unsigned char**buf_yuv);
#else
  int cvtTexture2YUVBuf(int width, int height, GLuint RGBATexture, unsigned char**buf_yuv, int firstFrameCnt, int previewMode, bef_ai_camera_position is_front, bef_ai_rotate_type orientation);
#endif
private:
  BytedOpenGLProgram2 _program;
  const GLfloat convert601torgba[9] = { 1.164, 1.164, 1.164, 0.0, -0.213, 2.112, 1.793, -0.533, 0.0};
  const GLfloat convert601fulltorgba[9] = { 1.0, 1.0, 1.0, 0.0, -0.343, 1.765, 1.4, -0.711, 0.0};
  const GLfloat convert709torgba[9] = { 1.164, 1.164, 1.164, 0.0, -0.213, 2.112, 1.793, -0.533, 0.0};
  const GLfloat convertrgba[9] = {0.299, -0.1678, 0.5, 0.587, -0.3313, -0.4187, 0.114, 0.5, -0.0813};
  const GLfloat rotate_model270[16] = {0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat rotate_model90[16] = {0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat flip_modelY[16] = {-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat flip_modelX[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat unit_matrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  int status;
  int buf_inited;
#if !BEF_EFFECT_ANDROID_WITH_JNI
  bool hardware_buffer_inited = false;
  AHardwareBuffer* hardWareBuf = nullptr;
  unsigned char *hardwareBuffer_writePtr = nullptr;
  EGLImageKHR imageEGL;
  int hardware_buffer_stride = 0;
  void init_hardware_buffer(int width, int height);
#endif
  int init_buf(int width, int height);

  const char* vertex_shader = "\n\
  attribute vec4 position;\n \
  attribute vec2 textureCoord; \n \
  varying lowp vec2 m_textureCoord; \n \
  uniform mat4 transform_rotate_model;  \n \
  uniform mat4 transform_flip_model;  \n \
  void main() \n \
  { \n \
  m_textureCoord = textureCoord; \n \
  gl_Position =  transform_flip_model * transform_rotate_model * position; \n \
  } \n \
  \n";
  const char* fragment_shader_601fullToRGBA = "\n \
  varying lowp vec2 m_textureCoord; \n \
  precision mediump float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV; \n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  mediump vec3 yuv; \n \
  lowp vec3 rgb; \n \
  // Subtract constants to map the video range start at 0 \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r);// - (16.0/255.0)); \n \
  yuv.yz = (texture2D(SamplerUV, m_textureCoord).ra - vec2(0.5, 0.5)); \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";
  
  const char* fragment_shader_601ToRGBA = "\n \
  varying lowp vec2 m_textureCoord; \n \
  precision mediump float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV; \n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  mediump vec3 yuv; \n \
  lowp vec3 rgb; \n \
  // Subtract constants to map the video range start at 0 \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r - (16.0/255.0)); \n \
  yuv.yz = (texture2D(SamplerUV, m_textureCoord).ra - vec2(0.5, 0.5)); \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";

  const char* fragment_shader_NV21ToRGBA = "\n \
  varying lowp vec2 m_textureCoord; \n \
  precision mediump float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV;\n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  mediump vec3 yuv; \n \
  lowp vec3 rgb; \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r); \n \
  yuv.yz = (texture2D(SamplerUV, m_textureCoord).ar - vec2(0.5, 0.5)); \n \
  rgb = colorConversionMatrix * yuv; \n \
  gl_FragColor = vec4(rgb,1); \n \
  } \n \
  \n ";

  const char* fragment_shader_I420ToRGBA = "\n \
  varying lowp vec2 m_textureCoord; \n \
  precision mediump float; \n \
  uniform sampler2D SamplerY;\n \
  uniform sampler2D SamplerUV; \n \
  uniform sampler2D SamplerU; \n \
  uniform sampler2D SamplerV; \n \
  uniform mat3 colorConversionMatrix; \n \
  void main()\n \
  { \n \
  mediump vec3 yuv; \n \
  lowp vec3 rgb; \n \
  yuv.x = (texture2D(SamplerY, m_textureCoord).r); \n \
  yuv.y = (texture2D(SamplerU, m_textureCoord).r) - 0.5; \n \
  yuv.z = (texture2D(SamplerV, m_textureCoord).r) - 0.5; \n \
  //yuv.yz = (texture2D(SamplerUV, m_textureCoord).ar - vec2(0.5, 0.5)); \n \
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
  GLuint frameBuffer;
  GLuint output_texture;
  GLint fboOld;
  
  GLint positionAttribute, textureCoordAttribute;
  
  GLint SamplerY, SamplerUV, colorConversionMatrixUniform, rotateMatrixUniform, flipMatrixUniform;

  GLint SamplerU, SamplerV;
  
  GLint SamplerRGBA;

  const GLfloat *_preferredConversion;
  
  GLuint luminanceTexture, chrominanceTexture;
  
  GLuint UTexture, VTexture;
  
  GLuint RGBATexture;
  
  ConvertType convert_type;
};
#endif /* PixelFormatConvertor2_h */
