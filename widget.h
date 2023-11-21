#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnOpen_clicked();
    void on_hsVolume_valueChanged(int value);
    void on_btnPlay_clicked();
    void positionChanged(qint64 position);
    void on_hsProgress_sliderMoved(int position);
    void on_btnPause_clicked();
    void on_btnStop_clicked();
    void on_btnMute_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer* m_player;
    bool mute;
};
#endif // WIDGET_H
