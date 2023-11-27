#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>
#include <QTime>
#include <QMediaContent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //test push github
    this->setWindowFlags(Qt::Dialog  | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint | Qt::WindowSystemMenuHint | Qt::MSWindowsFixedSizeDialogHint);

    //                      Button style

    ui->btnOpen->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->btnPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->btnPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->btnPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->btnStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->btnNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->btnMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->btnPBM->setIcon(QIcon(":/new_icons/ICO/loop.ico"));
    ui->btnClear->setIcon(QIcon(":/new_icons/ICO/trash.ico"));
    ui->btnRemove->setIcon(QIcon(":/new_icons/ICO/file-delete.ico"));
    ui->lComposition->setFrameStyle(QFrame::Box);

    //                      Player init

    m_player = new QMediaPlayer(this);
    m_player->setVolume(50);
    ui->lVolume->setText(QString("Volume:").append(QString::number(m_player->volume())));
    ui->lDuration->setText("00:00");
    ui->hsVolume->setValue(m_player->volume());
    ui->tvPlayList->setSelectionBehavior(QAbstractItemView::SelectRows);
    muted = false;
    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::on_positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::on_durationChanged);

    //                      PlayList init

    m_playlist_model = new QStandardItemModel(this);
    ui->tvPlayList->setModel(m_playlist_model);
    m_playlist_model->setHorizontalHeaderLabels(QStringList() << "Audio track" << "File path");
    ui->tvPlayList->hideColumn(1);
    ui->tvPlayList->horizontalHeader()->setStretchLastSection(true);
    ui->tvPlayList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    LoadPlaylist();

    connect(ui->tvPlayList, &QTableView::doubleClicked,
        [this](const QModelIndex& index)
        {
            m_playlist->setCurrentIndex(index.row());
            m_player->play();
        }
    );
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged,
        [this](int index)
        {
          ui->lComposition->setText(m_playlist_model->data(m_playlist_model->index(index, 0)).toString());
          this->setWindowTitle("Winamp - " + ui->lComposition->text());
          ui->tvPlayList->selectRow(index);
        }
    );
    PBM_loop = true;
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

Widget::~Widget()
{
    SavePlaylist();
    delete m_player;
    delete m_playlist;
    delete m_playlist_model;
    delete ui;
}

void Widget::on_btnOpen_clicked()
{
//  QString file = QFileDialog::getOpenFileName(
//                                                this,                                                     //родительское окно
//                                                tr("Open file"),                                          //заголовок окна диалога
//                                                "C:\\Users\\Zello\\OneDrive\\Рабочий стол\\Музыка",       //рабочий каталог
//                                                tr("Audio files (*.mp3 *.flac)")                          //выбор форматов файла
//                                              );
//   QString name_song = file.split('/').last();
//   this->setWindowTitle(QString("Winamp - ").append(file.split('/').last()));
//   ui->lComposition -> setText(name_song);
//   m_player->setMedia(QUrl::fromLocalFile(file));

    QStringList files = QFileDialog::getOpenFileNames(this, "Open files", "", "Audio files (*.mp3)");
    for(QString filesPath: files)
    {
        QList<QStandardItem*> items;
        items.append(new QStandardItem(QDir(filesPath).dirName()));
        items.append(new QStandardItem(filesPath));
        m_playlist_model->appendRow(items);
        m_playlist->addMedia(QUrl(filesPath));
    }
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

void Widget::on_positionChanged(qint64 position)
{
    ui->hsProgress->setMaximum(m_player->duration());
    ui->hsProgress->setValue(position);
    ui->lProgress->setText(QString(QTime::fromMSecsSinceStartOfDay(position).toString("mm:ss")));
}

void Widget::on_durationChanged(qint64 duration)
{
    ui->hsProgress->setMaximum(duration);
    ui->lDuration->setText(QString(QTime::fromMSecsSinceStartOfDay(duration).toString("mm:ss")));
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
    muted = !muted;
    m_player->setMuted(muted);
    ui->btnMute->setIcon(style()->standardIcon(muted?QStyle::SP_MediaVolumeMuted:QStyle::SP_MediaVolume));
}

void Widget::on_btnPrev_clicked()
{
    m_playlist->previous();
}

void Widget::on_btnNext_clicked()
{
    m_playlist->next();
}

void Widget::on_btnPBM_clicked()
{
    PBM_loop = !PBM_loop;
    ui->btnPBM->setIcon(PBM_loop?QIcon(":/new_icons/ICO/loop.ico"):QIcon(":/new_icons/ICO/random.ico"));
    m_playlist->setPlaybackMode(PBM_loop?QMediaPlaylist::Loop:QMediaPlaylist::Random);
}

void Widget::on_btnClear_clicked()
{
    m_player->stop();
    m_playlist->clear();
    m_playlist_model->clear();
    ui->lComposition->setText("Composition");
    m_playlist_model->setHorizontalHeaderLabels(QStringList() << "Audio track" << "File path");
    ui->tvPlayList->hideColumn(1);
    ui->tvPlayList->horizontalHeader()->setStretchLastSection(true);
    ui->tvPlayList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Widget::SavePlaylist()
{
    QString path_directory = QString(QDir::currentPath()).append("//playlist.m3u");
    m_playlist->save(QUrl::fromLocalFile(path_directory), "m3u");
}

void Widget::LoadPlaylist()
{
    QString path_directory = QString(QDir::currentPath()).append("//playlist.m3u");
    m_playlist->load(QUrl::fromLocalFile(path_directory), "m3u");
    for(int i = 0; i < m_playlist->mediaCount(); i++)
    {
        QMediaContent content = m_playlist->media(i);
        QString file = content.canonicalUrl().url();
        QList<QStandardItem*> items;
        items.append(new QStandardItem(QDir(file).dirName()));
        items.append(new QStandardItem(file));
        m_playlist_model->appendRow(items);
    }
}

void Widget::on_btnRemove_clicked()
{
    QItemSelectionModel* selection = ui->tvPlayList->selectionModel();
    QModelIndexList rows = selection->selectedRows();
    for(QModelIndexList::iterator it = rows.begin(); it != rows.end(); ++it)
    {
        if(m_playlist->removeMedia(it->row()))
        m_playlist_model->removeRow(it->row());
    }
}


