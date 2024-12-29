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
#include <QStackedLayout>
#include <vector>


class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    enum RepeatMode{
        PlaylistRepeat=0,
        VideoRepeat=1,
        Shuffle=2,
    };
    enum FIRSTLAYOUT_LABEL_ELEMENTS{
        PAUSE_BUTTON = 0,
        BACK_BUTTON = 1,
        STOP_BUTTON = 2,
        NEXT_BUTTON = 3,
        FULLSCREEN_BUTTON = 4,
        PLAYLIST_BUTTON = 5,
        REPETITION_BUTTON = 6,
        BVolumeControl = 7,
    };
    enum FOURTHLAYOUT_LABEL_ELEMENTS{
        Open_file = 0,
        Open_folder = 1,
        Open_media = 2,
        Quit = 3,
        Title = 4,
        JUMP_BACKWARD = 5,
        JUMP_FORWARD = 6,
        JUMP_TO_TIME = 7,
        FULL_VOLUME = 8,
        MUTE = 9,
        SET_RADIO = 10,
        ADDSUB = 11,
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
    void slidertovolume(int position);
    void volumetoslider(qreal position);
    void subscraper(std::string subpath);
    //turnning off the tab focusing
    bool focusNextPrevChild(bool next) override{
        if(next){}
        return false;
    }
private:
    bool paused = false;
    bool fullscreened = false;
    bool finished = false;
    QString playertype;
    size_t videoindex=0;
    RepeatMode  rep = PlaylistRepeat ;
    
    QLabel* image;
    QWidget *mainwidget;
    QStackedLayout *stackedlayout;
    QVBoxLayout *mainlayout;
    QHBoxLayout *firstlayout;
    QGridLayout *videolayout;
    QHBoxLayout *thirdlayout;
    QHBoxLayout *fourthlayout;
    QMediaPlayer *player;
    QLabel *sublabel;
    QAudioOutput *audio;
    QVideoWidget *video;
    QSlider *videoslider;
    QSlider *volumeslider;
    QLabel *currenttimer;
    QLabel *totaltimer;
    qreal oldvolume;
    std::chrono::time_point<std::chrono::system_clock> now;
    
    std::vector<QUrl> playlist;
    QList<QString> mcbuttons = {"BPause","BBack","BStop","BNext","BFullscreen","BPlaylist","BRepeating","BVolumeControl"};
    QList<QString> firstlayoutbuttons = {"Media","Playback","Audio","Video","Subtitle","Tools","View","Help"};
    QList<QList <QString> > actionslist = {{"open file","open folder","open media","quit"},{"Title","Jump Backward","Jump Forward","Jump to Time"},{"Full Volume","Mute"},{"Set Radio"},{"add subtitles"}};

public:
    std::vector <float> subtimer;
    std::vector <std::string> sublines;
    bool displayed=false;
    int subcounter=0;

};

#endif
//https://vo-live.cdb.cdn.orange.com/Content/Channel/NationalGeographicHDChannel/HLS/index.m3u8
