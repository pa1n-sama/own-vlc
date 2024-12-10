#ifndef URLWINDOW_H
#define URLWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QString>

class UrlWindow : public QDialog {
    Q_OBJECT

public:
    explicit UrlWindow(QWidget *parent = nullptr);

public:
    QString url="";
private:
    QTextEdit *urlentry;
    QVBoxLayout *mainlayout;
    QHBoxLayout *firstlayout;
    QHBoxLayout *secondlayout;
    QLabel *urllabel;
    QPushButton *donebutton;
    QPushButton * cancelbutton;
};

#endif
