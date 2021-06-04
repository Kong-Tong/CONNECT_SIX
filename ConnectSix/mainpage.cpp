#include "mainpage.h"
#include<QPainter>
#include<QIcon>
#include<QPaintEvent>
#include<QSound>

#define BACK ":/file/Image/background1.jpg"

mainpage::mainpage(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("六子棋");
    this->setWindowIcon(QIcon(":/file/Image/logo.png"));
    this->setFixedSize(800,600);
    button=new QPushButton(this);
    button->move(QPoint(350,350));
    button->setFlat(true);
    button->setFixedSize(100,70);
    button->setFont(QFont("宋体",20,700));
    button->setText("进入");
    connect(button,&QPushButton::clicked,this,&mainpage::sendslot);  //连接信号

}
void mainpage::paintEvent(QPaintEvent *event)
{
    if(button->underMouse())
    {
        button->setFlat(false);
    }
    else
    {
        button->setFlat(true);
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿,防止图像走样
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(BACK));

}
void mainpage::sendslot()
{
    emit mysignal();   //发出信号，等待主窗口接收
}

