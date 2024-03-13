#ifndef PIXTEXTWIDGET_H
#define PIXTEXTWIDGET_H

#include <QWidget>

namespace Ui {
class PixTextWidget;
}

class PixTextWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PixTextWidget(QWidget *parent = nullptr);
    ~PixTextWidget();

public:
    void setText(const QString &txt);
    void setTextVisuable(bool visual = true);
    void setPixUrl(const QString &url);
    void setUnClicked();

    const QString getText();
    const QString getPixmapUrl();

private:
    void mousePressEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;

signals:
    void clicked();


private:
    Ui::PixTextWidget *ui;
    QString m_text;
    QString m_pixUrl;
    bool m_txtVisible;
    bool m_pressed;
};

#endif // PIXTEXTWIDGET_H
