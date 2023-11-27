#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>
#include <QItemSelectionModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void SavePlaylist(QString filename);
    void LoadPlaylist(QString filename);
    void Load_CUE_Playlist(QString filename);

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
    void on_btnPBM_clicked();
    void on_btnClear_clicked();
    void on_btnRemove_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer* m_player;
    QMediaPlaylist* m_playlist;
    QStandardItemModel* m_playlist_model;
    bool muted;
    bool PBM_loop;
    QString PLAYLIST = "C:\\Qt\\Learning\\MediaPlayer\\playlist.m3u";
};
#endif // WIDGET_H
