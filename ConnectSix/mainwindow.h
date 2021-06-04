#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QWidget>
#include"game.h"
#include<QMouseEvent>
#include<QEvent>
#include"mainpage.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Game *game; //游戏指针

    void paintEvent(QPaintEvent *); //绘图
    void mouseReleaseEvent(QMouseEvent *ev);  //鼠标点击
    void mouseMoveEvent(QMouseEvent *ev);

    int clickPosX, clickPosY; //鼠标将点击位置
    void initgame(); //初始化游戏
    bool on_jinshou;
    void init();//初始化
    QPushButton pushButton; //开始

    void isEnd();  //判断游戏是否结束



private slots:
    void play();  //人下棋

    void on_pushButton_clicked();


    void myslot();


public slots:
    void topage();
private:
    Ui::MainWindow *ui;
    mainpage page;
    QPushButton  *back;
};

#endif // MAINWINDOW_H
