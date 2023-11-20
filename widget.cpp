#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //                      Button style

    ui->btnOpen->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->btnPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->btnPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->btnPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->btnStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->btnNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    //                      Player init

    m_player = new QMediaPlayer(this);
    m_player->setVolume(70);
    ui->lVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
    ui->hsVolume->setValue(m_player->volume());
}

Widget::~Widget()
{
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
   ui->lComposition -> setText(file);
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
}

