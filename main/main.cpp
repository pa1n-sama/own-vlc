#include "mainwindow.h"
#include <QApplication>
#include <QFile>


int main(int argc,char* argv[]){
    QApplication a(argc, argv);
    QFile file("/home/pain/.config/VFW/cache/styles/style.css");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString script = file.readAll();
        a.setStyleSheet(script);
        file.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}