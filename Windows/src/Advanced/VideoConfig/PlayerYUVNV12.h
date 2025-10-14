/******************************************************************************
 * @文件名     playimage.h
 * @功能       使用OpenGL实现YUV图像的绘制，可通过USE_WINDOW宏切换使用QOpenGLWindow还是QOpenGLWidget
 *
 * @开发者     mhf
 * @邮箱       1603291350@qq.com
 * @时间       2022/10/14
 * @备注
 *****************************************************************************/
#ifndef PlayerYUVNV12_H
#define PlayerYUVNV12_H

#include <QWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <qopenglshaderprogram.h>
#include <QOpenGLTexture>
#include <qopenglpixeltransferoptions.h>

enum VPixelFormat{
    kVPixelFormat_Unknow = -1,
    kVPixelFormat_YUV420 = 1,
    kVPixelFormat_NV12 = 2,
    kVPixelFormat_RGB = 3
};

typedef struct  {
    int format = kVPixelFormat_Unknow;
    int width;
    int height;
    int linesize[3];
    uint8_t* data[3];
public:
    void clean() {
        for (int i = 0; i < 3; i++) {
            if (data[i]) {
                delete[]data[i];
                data[i] = nullptr;
            }
            linesize[i] = 0;
        }
        width = 0;
        height = 0;
        format = kVPixelFormat_Unknow;
    }
}VFrame;

#define USE_WINDOW 0    // 1:使用QOpenGLWindow显示, 0：使用QOpenGLWidget显示

#if USE_WINDOW
#include <QOpenGLWindow>
class PlayerYUVNV12 : public QOpenGLWindow, public  QOpenGLFunctions_3_3_Core
#else
#include <QOpenGLWidget>
class PlayerYUVNV12 : public QOpenGLWidget, public  QOpenGLFunctions_3_3_Core
#endif
{
    Q_OBJECT
public:
#if USE_WINDOW
    explicit PlayerYUVNV12(UpdateBehavior updateBehavior = NoPartialUpdate, QWindow *parent = nullptr);
#else
    explicit PlayerYUVNV12(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
#endif
     ~PlayerYUVNV12() override;

    void repaint(VFrame* frame);             // 设置需要绘制的图像帧


protected:
    void initializeGL() override;               // 初始化gl
    void resizeGL(int w, int h) override;       // 窗口尺寸变化
    void paintGL() override;                    // 刷新显示

private:
    // YUV420图像数据更新
    void repaintTexYUV420P(VFrame* frame);
    void initTexYUV420P(VFrame* frame);
    void freeTexYUV420P();
    // NV12图像数据更新
    void repaintTexNV12(VFrame* frame);
    void initTexNV12(VFrame* frame);
    void freeTexNV12();

    // RGBA 图像数据更新
    void repaintTexRGBA(VFrame *frame);
    void initTexRGBA(VFrame *frame);
    void freeTexRGBA();

private:
    QOpenGLShaderProgram* m_program = nullptr;
    QOpenGLTexture* m_texY = nullptr;
    QOpenGLTexture* m_texU = nullptr;
    QOpenGLTexture* m_texV = nullptr;
    QOpenGLTexture* m_texUV = nullptr;
    QOpenGLTexture* m_texRGBA = nullptr;
    QOpenGLPixelTransferOptions m_options;

    GLuint VBO = 0;       // 顶点缓冲对象,负责将数据从内存放到缓存，一个VBO可以用于多个VAO
    GLuint VAO = 0;       // 顶点数组对象,任何随后的顶点属性调用都会储存在这个VAO中，一个VAO可以有多个VBO
    GLuint EBO = 0;       // 元素缓冲对象,它存储 OpenGL 用来决定要绘制哪些顶点的索引
    QSize  m_size;
    QSizeF  m_zoomSize;
    QPointF m_pos;
    int m_format = -1;         // 像素格式
};

#endif // PlayerYUVNV12_H
