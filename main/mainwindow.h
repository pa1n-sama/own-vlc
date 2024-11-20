#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QSlider>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QUrl>




class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    enum RepeatMode{
        PlaylistRepeat=0,
        VideoRepeat=1,
        Shuffle=2,
    };

    MainWindow(QWidget *parent=nullptr);
    void firstlayoutclick(int buttonindex);
    void fourthlayoutclick(int buttonindex);
    void setsliderrange(qint64 position);
    void setsliderposition(qint64 position);
    void mediaposition(int position);
    void keyPressEvent(QKeyEvent *event)override;
    void mediaplayer(QString url="blackscreen");
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    bool paused = false;
    bool fullscreened = false;
    bool finished = false;
    QString playertype;
    size_t videoindex=0;
    RepeatMode  rep = PlaylistRepeat ;
    
    QLabel* image;
    QWidget *mainwidget;
    QVBoxLayout *mainlayout;
    QHBoxLayout *firstlayout;
    QVBoxLayout *videolayout;
    QHBoxLayout *thirdlayout;
    QHBoxLayout *fourthlayout;
    QMediaPlayer *player;
    QAudioOutput *audio;
    QVideoWidget *video;
    QSlider *videoslider;
    QLabel *currenttimer;
    QLabel *totaltimer;

    std::vector<QUrl> playlist;
    QList<QString> mcbuttons = {"BPause","BBack","BStop","BNext","BFullscreen","BPlaylist","BRepeating"};
    QList<QString> firstlayoutbuttons = {"Media","Playback","Audio","Video","Subtitle","Tools","View","Help"};
    QList<QString> actionslist = {"open file","open folder"};

};

#endif
