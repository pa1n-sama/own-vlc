#ifndef SUBCONFIG
#define SUBCONFIG

#include <iostream>
#include <QDialog>
#include <nlohmann/json.hpp>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QSpinBox>
#include <QColorDialog>
#include <QList>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>

using namespace nlohmann;

class SubConfig:public QDialog{
  Q_OBJECT

public:
  QString HtmlScript;

  QString selected_font;
private:

  QList <QString>labels={"Margin Bottom:","Padding:",
                      "Border Color:","Border Weight:",
                      "Bg Color:","Bg Opacity:",
                      "Font Size:","Font Familly:",
                      "Font Color:","Font Opacity:"
  };
  QVBoxLayout * mainlayout;
  QGridLayout * gridlayout;
  QHBoxLayout * buttonlayout;
  
public:
  SubConfig(QWidget *parent=nullptr){
    loadstylefiles();
    mainlayout = new QVBoxLayout(this);
    gridlayout = new QGridLayout();
    buttonlayout = new QHBoxLayout();
    for(size_t i=0;i<labels.size();i++){
      QLabel *label = new QLabel;
      label->setText(labels[i]);
      gridlayout->addWidget(label,i/2,(i%2)*2);
      if(i==2||i==4||i==8){
        QPushButton *colorpicker = new QPushButton();
        colorpicker->setObjectName(labels[i].replace(" ","").replace(":",""));
        connect(colorpicker,&QPushButton::clicked,[this,colorpicker](){
          QColor color = QColorDialog::getColor(Qt::white,this,"Pick your color");
          if(color.isValid()){
            colorpicker->setStyleSheet("background-color:"+color.name()+";");
          }
        });
        gridlayout->addWidget(colorpicker,i/2,(i%2)*2+1);
      
      }else if(i==7){
        QToolButton *button = new QToolButton;
        button->setText("Font");
        QList <QString> fonts= {"JetBrains","monospace"};
        QMenu *font_familly = new QMenu();
        for(int i=0;i<fonts.size();i++){
          QAction * actions = new QAction;
          actions->setText(fonts[i]);
          font_familly->addAction(actions);
          button->setMenu(font_familly);
          connect(actions,&QAction::triggered,[this,i,fonts](){
            selected_font = fonts[i];
          });
        }
        gridlayout->addWidget(button,i/2,(i%2)*2+1);
      }else{
        QSpinBox* number_picker = new QSpinBox();
        number_picker->setObjectName(labels[i]);

        number_picker->setRange(0,101);
        gridlayout->addWidget(number_picker,i/2,(i%2)*2+1);
      }
    }

    QPushButton *done = new QPushButton(this);
    done->setText("done");
    QPushButton *cancel = new QPushButton(this);
    cancel->setText("cancel");
    connect(done,&QPushButton::clicked,[this](){
      saveconfig();
      QDialog::accept();
    });
    connect(cancel,&QPushButton::clicked,[this](){
      QDialog::accept();
    });
    buttonlayout->addWidget(done);
    buttonlayout->addWidget(cancel);
    mainlayout->addLayout(gridlayout);
    mainlayout->addLayout(buttonlayout);
    setLayout(mainlayout);
  }

  void loadstylefiles(){
    QFile file("/home/pain/.config/VFW/cache/styles/subconfig.css");
      if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
          QTextStream in(&file);
          QString styleSheet = in.readAll();
          this->setStyleSheet(styleSheet);
      }
  }

  void saveconfig(){
    json file("/home/pain/.config/VFW/cache/styles/subconfig.json");
    file["margin-bottom"] ; file["padding"];
    file["border-color"] ; file["border-weight"];
    file["bg-color"];file["bg-opacity"];
    file["font-size"];file["font-familly"];
    file["font-color"];file["font-opacity"];
  }
};

#endif