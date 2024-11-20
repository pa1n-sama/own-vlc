#include<nlohmann/json.hpp>
#include <iomanip>
#include <iostream>
#include <mainwindow.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <fstream>
#include <QAction>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QLabel>
#include <QKeyEvent>
#include <QFileDialog>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    this->setFocus();

    //elements definition

    player = new QMediaPlayer;
    audio = new QAudioOutput;
    video = new QVideoWidget;
    videoslider = new QSlider(Qt::Horizontal);
    mainwidget = new QWidget;
    mainlayout = new QVBoxLayout;
    firstlayout = new QHBoxLayout;
    videolayout = new QVBoxLayout;
    thirdlayout = new QHBoxLayout;
    fourthlayout = new QHBoxLayout;
    currenttimer = new QLabel("--:--:--");
    totaltimer = new QLabel("--:--:--");
    
    //setting firstlayout toolbuttons with it's actions

    int counter = 0;
    for(int i=0;i<firstlayoutbuttons.size();i++){
        QToolButton *button = new QToolButton;
        button->setPopupMode(QToolButton::InstantPopup);
        button->setText(firstlayoutbuttons[i]);
        button->setObjectName(firstlayoutbuttons[i]);
        connect(button,&QPushButton::clicked,[this,i](){
            firstlayoutclick(i);
        });
        QMenu *menu = new QMenu; 
        while(counter<actionslist.size()){
            QAction *action = new QAction;
            action->setObjectName(actionslist[counter]);
            action->setText(actionslist[counter]);
            connect(action,&QAction::triggered,[this,counter](){
                firstlayoutclick(counter);
            });
            // connect these actions later
            menu->addAction(action);
            counter++;
        }
        button->setMenu(menu);
        firstlayout->addWidget(button);
    }

    //setting fourthlayout pushbuttons

    for(int j=0;j<mcbuttons.size();j++){
        QPushButton *button = new QPushButton;
        button->setObjectName(mcbuttons[j]);
        QPixmap pix("cache/icons/"+mcbuttons[j]+".png");
        button->setIcon(pix);
        button->setIconSize(QSize(16,16));
        connect(button,&QPushButton::clicked,[this,j](){
            fourthlayoutclick(j);
        });
        fourthlayout->addWidget(button);
    }

    //connecting the slider and media with there logic

    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::setsliderposition);
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::setsliderrange);
    connect(videoslider,&QSlider::sliderMoved,this,&MainWindow::mediaposition);

    //setting videowidget parametres

    video->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    video->setMinimumSize(854,480);
    video->setMaximumSize(1920,1080);
    
    //adding widgets to there layouts and the layous to the central widget
    videolayout->addWidget(video);
    thirdlayout->addWidget(currenttimer);
    thirdlayout->addWidget(videoslider);
    thirdlayout->addWidget(totaltimer);
    mainlayout->addLayout(firstlayout);
    mainlayout->addLayout(videolayout);
    mainlayout->addLayout(thirdlayout);
    mainlayout->addLayout(fourthlayout);
    mainwidget->setLayout(mainlayout);
    setCentralWidget(mainwidget);

    //showing a blackscreen
    mediaplayer("blackscreen");
}

void MainWindow::mediaplayer(QString url){

    //if there is no video to play a black image will play (blackscreen)
    
    if(videoindex>playlist.size()||url=="blackscreen") {
        player->setSource(QUrl("blackscreen"));
        currenttimer->setText("--:--:--");
        totaltimer ->setText("--:--:--");}
    
    //if pass "play a list" as an argunent a video from the playlist will play

    else if(url=="play a list"){
        player->setSource(QUrl(playlist[videoindex]));
        }
    
    //if we pass a url, a video with the url will play and the playlist will be cleared

    else{
        player->setSource(QUrl(url));}

    //mediaplayer setup (sound and video widget)

    player->setVideoOutput(video);
    player->setAudioOutput(audio);
    audio->setVolume(false);
    video->show();
    player->play();

}

//firstlayout buttons logic
void MainWindow::firstlayoutclick(int buttonindex){
    QString url;
    switch(buttonindex){
        //if the user choose to open a file
        case 0:
            url = QFileDialog::getOpenFileName(this,tr("Select Video File"),"/home/pain/Downloads",tr("Mp4 files (*.mp4)"));
            if(!url.isEmpty()){
                mediaplayer(url);
                playertype = "vid";
            }
            playlist.clear(); //clearing the playlist
            break;
        //if the user choose to open a directory (playlist)
        case 1:
            url = QFileDialog::getExistingDirectory(this,tr("Setect Playlist Directory","/home/pain/Downloads", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
            if(!url.isEmpty()){
                
                playlist.clear(); //clearing the playlist
                //saving all the urls in a list
                for(auto i : std::filesystem::directory_iterator(url.toStdString())){
                    playlist.push_back(QUrl(QString::fromStdString(i.path())));
                }
                playertype = "playlist";
                mediaplayer("play a list");
            }
            break;
    }
}

//fourthlayout buttons logic
void MainWindow::fourthlayoutclick(int buttonindex){
    switch(buttonindex){

        //if the pause button is clicked
        case 0:
            {QPushButton *searchbutton = this->findChild<QPushButton *>("BPause");
            if(paused){
                searchbutton->setIcon(QPixmap("cache/icons/BPause.png"));
                player->play();
            }else{
                searchbutton->setIcon(QPixmap("cache/icons/BPlay.png"));
                player->pause();
            }
            paused=!paused;
            break;}
        
        //if the prevous video button is clicked
        case 1:
            {if(playertype=="playlist" && videoindex>0){
            videoindex--;
            mediaplayer("play a list");}
            break;}
            

        //if the stop button is clicked
        case 2:
            {player->setSource(QUrl("blackscreen"));
            currenttimer->setText("--:--:--");
            totaltimer ->setText("--:--:--");
            playlist.clear();
            playertype="video";
            break;}
        
        //if the next video button is clicked
        case 3:
            {if(playertype=="playlist"){
            //we set the player to the end of the video so it trigger the logic in the lines (326,...354)
            player->setPosition(player->duration());}
            break;}
        //if fullscreen button is clicked
        case 4:
            {if(fullscreened){
                currenttimer->show();
                totaltimer->show();
                videoslider->show();
            }else{
                currenttimer->hide();
                totaltimer->hide();
                videoslider->hide();
            }

            for(int i=0;i<firstlayoutbuttons.size();i++){
                QToolButton *searchtoolbutton = this->findChild<QToolButton *>(firstlayoutbuttons[i]);
                if(searchtoolbutton){
                    if(fullscreened){
                        searchtoolbutton->show();
                    }else{
                        searchtoolbutton->hide();

                    }
                }
            }
            for(int i=0;i<mcbuttons.size();i++){
                QPushButton *seachpushbutton = this->findChild<QPushButton *>(mcbuttons[i]);
                if(seachpushbutton){
                    if(fullscreened){
                        seachpushbutton->show();
                    }else{
                    seachpushbutton->hide();
                    }
                }
            }
            fullscreened=!fullscreened;
            break;}
        
        //if reloading behavior is clicked 
        case 6:
            QPushButton * sb = this->findChild<QPushButton*>("BRepeating");
            if(rep==0){
                //repeat playlist
                sb->setIcon(QPixmap("cache/icons/BRepeatingone.png"));
                rep=1;
            }else if (rep==1){
                //repeating one video
                sb->setIcon(QPixmap("cache/icons/BSuffle.png"));
                rep=2;
            }else if (rep==2){
                //shuffle
                sb->setIcon(QPixmap("cache/icons/BRepeating.png"));
                rep=0;
            }
    }
}

//keyboard event catching function
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()  == Qt::Key_Escape){
       fullscreened = true;
       fourthlayoutclick(4);
    }else if(event->key()  == Qt::Key_F){
       fourthlayoutclick(4);
    }else if(event->key()==Qt::Key_Space){
       fourthlayoutclick(0);
    }else if(event->key()==Qt::Key_Right){
        player->setPosition(player->position()+5000);
    }else if(event->key()==Qt::Key_Left){
        player->setPosition(player->position()-5000);
    }else if(event->key()==Qt::Key_Up){
        audio->setVolume(audio->volume()+0.1);
    }else if(event->key()==Qt::Key_Down){
        audio->setVolume(audio->volume()-0.1);
    }
}


// slider and player relationship

//setting the player position basing on the slider position
void MainWindow::mediaposition(int position){
    player->setPosition(position);
}

//setting the range of the slider basing on the player
void MainWindow::setsliderrange(qint64 position){
    videoslider->setRange(0,position);
}

//setting the app elements in there relation with the player
void MainWindow::setsliderposition(qint64 position){
    videoslider->setValue(position);

    //if the video is still playing (position != video duration) 
    if(position!=player->duration()){

        //setting the current timer basing on the player position
        int hour = player->position()/(1000*60*60);
        int min = (player->position()/1000-hour*60*60)/60;
        int second = player->position()/1000-min*60;
        std::ostringstream osshour, ossmin, osssecond;
        osshour<<std::setfill('0')<<std::setw(2)<<hour;
        ossmin<<std::setfill('0')<<std::setw(2)<<min;
        osssecond<<std::setfill('0')<<std::setw(2)<<second;
        currenttimer->setText(QString::fromStdString(osshour.str())+":"+
            QString::fromStdString(ossmin.str())+":"+
            QString::fromStdString(osssecond.str()));
        
        //setting the total timer basing on the player duration
        int thour = player->duration()/(1000*60*60);
        int tmin = (player->duration()/1000-thour*60*60)/60;
        int tsecond = player->duration()/1000-tmin*60;
        std::ostringstream tosshour, tossmin, tosssecond;
        tosshour<<std::setfill('0')<<std::setw(2)<<thour;
        tossmin<<std::setfill('0')<<std::setw(2)<<tmin;
        tosssecond<<std::setfill('0')<<std::setw(2)<<tsecond;
        totaltimer->setText(QString::fromStdString(tosshour.str())+":"+
            QString::fromStdString(tossmin.str())+":"+
            QString::fromStdString(tosssecond.str()));

    }
    //if the video is finished
    else if (position==player->duration()){
        //if the reloading button is in the "reload full playlist" mode
        if(rep==0){
            if(videoindex==playlist.size()-1){
                videoindex = 0;
            }else{
                videoindex++;
            }
            mediaplayer("play a list");
        }

        //if the reloading button is in the "reload one video" mode
        else if (rep==1){
            player->setPosition(0);
            player->stop();
            player->play();
        }

        //if the reloading button is in the "random video" mode
        else{
            videoindex = rand()%playlist.size();
            mediaplayer("play a list");
        }
        videoslider->setValue(0);
    }

}


MainWindow::~MainWindow(){

}
