#ifndef RENDERRGB_H
#define RENDERRGB_H

#include <QWidget>

class RenderRGB : public QWidget
{
    Q_OBJECT
public:
    explicit RenderRGB(QWidget *parent = nullptr);
    void setImage(const QImage &img);

private:
    void paintEvent(QPaintEvent *);

signals:

private:
    QImage m_img;

};

#endif // RENDERRGB_H
