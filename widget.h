#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>

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
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 duration);
    void on_hsProgress_sliderMoved(int position);
    void on_btnPause_clicked();
    void on_btnStop_clicked();
    void on_btnMute_clicked();
    void on_btnPrev_clicked();
    void on_btnNext_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer* m_player;
    QMediaPlaylist* m_playlist;
    QStandardItemModel* m_playlist_model;
    bool muted;
};
#endif // WIDGET_H
