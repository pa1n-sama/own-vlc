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
    MainWindow(QWidget *parent=nullptr);
    void firstlayoutclick(int buttonindex);
    void fourthlayoutclick(int buttonindex);
    void setsliderrange(qint64 position);
    void setsliderposition(qint64 position);
    void mediaposition(int position);
    void keyPressEvent(QKeyEvent *event)override;
    void mediaplayer(QString url="image.png");
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    ~MainWindow();
private:
    QString playertype;
    bool finished = false;
    QLabel* image;
    int  rep = 0 ;
    size_t videoindex=0;
    QList<QString> firstlayoutbuttons = {"Media","Playback","Audio","Video","Subtitle","Tools","View","Help"};
    QList<QString> actionslist = {"open file","open folder"};
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
    QList<QString> mcbuttons = {"BPause","BBack","BStop","BNext","BFullscreen","BPlaylist","BRepeating"};
    QLabel *currenttimer;
    QLabel *totaltimer;
    bool paused = false;
    bool fullscreened = false;
    std::vector<QUrl> playlist;

};

#endif