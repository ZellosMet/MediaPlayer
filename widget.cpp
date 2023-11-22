#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //test push github

    //                      Button style

    ui->btnOpen->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->btnPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->btnPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->btnPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->btnStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->btnNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->btnMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui->lComposition->setFrameStyle(QFrame::Box);

    //                      Player init

    m_player = new QMediaPlayer(this);
    m_player->setVolume(70);
    ui->lVolume->setText(QString("Volume:").append(QString::number(m_player->volume())));
    ui->lDuration->setText("00:00");
    ui->hsVolume->setValue(m_player->volume());
    mute = false;
    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::positionChanged);
}

Widget::~Widget()
{
    delete this->m_player;
    delete ui;
}


void Widget::on_btnOpen_clicked()
{
   QString file = QFileDialog::getOpenFileName(
                                                this,                                                     //родительское окно
                                                tr("Open file"),                                          //заголовок окна диалога
                                                "C:\\Users\\Zello\\OneDrive\\Рабочий стол\\Музыка",       //рабочий каталог
                                                tr("Audio files (*.mp3 *.flac)")                          //выбор форматов файла
                                              );
   QString name_song = file.split('/').back();
   ui->lComposition -> setText(name_song);
   m_player->setMedia(QUrl::fromLocalFile(file));
}


void Widget::on_hsVolume_valueChanged(int value)
{
    m_player->setVolume(value);
    ui->lVolume->setText((QString("Volume: ").append(QString::number(m_player->volume()))));
}


void Widget::on_btnPlay_clicked()
{
    m_player->play();
    ui->lDuration->setText(QString(QTime::fromMSecsSinceStartOfDay(m_player->duration()).toString("mm:ss")));
}

void Widget::positionChanged(qint64 position)
{
    ui->hsProgress->setMaximum(m_player->duration());
    ui->hsProgress->setValue(position);
    ui->lProgress->setText(QString(QTime::fromMSecsSinceStartOfDay(position).toString("mm:ss")));
}

void Widget::on_hsProgress_sliderMoved(int position)
{
    m_player->setPosition(position);
}

void Widget::on_btnPause_clicked()
{
    m_player->pause();
}

void Widget::on_btnStop_clicked()
{
    m_player->stop();
}


void Widget::on_btnMute_clicked()
{
    if(!mute)
    {
        mute = !mute;
        ui->btnMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        m_player->setMuted(mute);
    }
    else
    {
        mute = !mute;
        ui->btnMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        m_player->setMuted(mute);
    }
}

