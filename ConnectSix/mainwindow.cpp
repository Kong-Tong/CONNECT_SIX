#include "mainwindow.h"
#include"mainpage.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPen>
#include<QPaintEvent>
#include<QLabel>
#include<QBitmap>
#include<QPixmap>
#include<QPushButton>
#include<qmath.h>
#include<QBrush>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<QMenuBar>
#include<QMenu>
#include<QIcon>

#define BACKGROUND  ":/file/Image/background.jpg"  //背景图片路径

const int BoardSize=21;  //棋盘线条数
const int distance=40;  //棋盘距离边缘的距离
const int square_length=40;  //棋盘格子大小
const int MouseRange=30; //鼠标的有效点击距离
const int flag_length=11; //落子标记边长
const int r=17; //棋子半径

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(2*distance+(BoardSize-1)*square_length+400,2*distance+(BoardSize-1)*square_length);
    this->setWindowIcon(QPixmap(":/file/Image/logo.png")); //设置应用图标
    ui->pushButton->setText("开始");
    ui->pushButton->setFont(QFont("宋体",10,700));
    ui->pushButton->setGeometry(1000,200,200,60); //设置按钮位置和尺寸

    ui->pushButton->setFlat(true);  //设置按钮透明
    ui->pushButton_2->close();
    ui->pushButton_3->close();


    back=new QPushButton(this);
    back->setParent(this);
    back->setGeometry(900,50,80,50);
    back->setText("返回界面");
    back->setFont(QFont("宋体",8,300));
    back->setFlat(true);
    on_jinshou=true;  //默认开启禁手
    QMenuBar *menubar=menuBar();  //设置菜单栏
    QMenu *menu_1=menubar->addMenu("六子棋"); //设置菜单
    QAction *action_0=menu_1->addAction("游戏介绍");
    QString str_0=  "本游戏根据五子棋改编而来，规则与五子棋类似，详情见“规则介绍”。"
                    "本游戏与流传于中国民间的传统六子棋不同，玩法规则也区别于吴毅成教授发明的连六棋。"
                    "本游戏设计初衷为提升自我能力。如有误解，敬请谅解。";
    connect(action_0,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"游戏介绍",str_0);
            }
            );
    QAction *action_1=menu_1->addAction("规则介绍");
    QString str=          "规则:\n"
                           "1.对峙双方谁的六个棋子先连在一条线即为胜者。\n"
                           "2.当有四个子连成一条直线时，就应采取防守，堵住四子的一端，否则就会输掉比赛。\n"
                           "3.应当避免在比赛内出现四四禁手、五五禁手等情况，否则就会不小心输掉比赛。\n"
                           "4.关于禁手:\n指对局中禁止先行一方（黑方）使用的战术，具体包括黑方一子落下时同时形成双四、双五或长连等三种棋形。白方无禁手。黑方禁手的位置称为禁手点。";

    connect(action_1,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"游戏规则",str);
            }
            );   //弹出游戏规则内容
    QAction *action_2=menu_1->addAction("退出游戏");
    connect(action_2,&QAction::triggered,this,&QMainWindow::close);  //关闭程序
    QMenu *Ban=menubar->addMenu("选项");
    QAction *on=Ban->addAction("开启禁手");
    QAction *off=Ban->addAction("关闭禁手");
    connect(on,&QAction::triggered,
            [=]()
            {
               on_jinshou=true;
            }
    );
    connect(off,&QAction::triggered,
            [=]()
            {
               on_jinshou=false;
            }
    );
    QMenu *menu_2=menubar->addMenu("了解更多");
    QAction *action_3=menu_2->addAction("版本");
    connect(action_3,&QAction::triggered,
            [=]()
            {
               QMessageBox::about(this,"版本介绍","版本号：1.0");
            }
            );
    QAction *action_4=menu_2->addAction("作者");
    QString str2="学号：920106970105\n";
    connect(action_4,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"关于作者",str2);
            });

    initgame();  //默认初始化
    this->hide();
    page.show();
    connect(back,&QPushButton::clicked,this,&MainWindow::topage);   //连接信号和槽
    void (mainpage::*myfun)()=&mainpage::mysignal;
    connect(&page,myfun,this,&MainWindow::myslot);

}

void MainWindow::myslot()
{
    this->show();  //游戏界面显示
    page.hide();   //子窗口隐藏
}
void MainWindow::topage()  //返回主界面
{

    this->hide();
    page.show();
}
MainWindow::~MainWindow()
{
    delete ui;
    if(game)   //撤销游戏指针
    {
        delete game;
        game = nullptr;
    }

}
void MainWindow::paintEvent(QPaintEvent *)
{
    if(ui->pushButton->underMouse())
    {
        ui->pushButton->setFlat(false);
    }
    else
    {
        ui->pushButton->setFlat(true);
    }

    if(back->underMouse())
    {
        back->setFlat(false);
    }
    else
    {
        back->setFlat(true);
    }
    QPainter painter(this); //画家
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(BACKGROUND));
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen; //画笔
    pen.setWidth(2);  //画笔的线条宽度
    pen.setColor(Qt::black);
    painter.setPen(pen);  //将画笔交给画家
    for(int i=0;i<BoardSize;i++)
    {
        painter.drawLine(distance,distance+i*square_length,distance+(BoardSize-1)*square_length,distance+i*square_length);  //画横线
        painter.drawLine(distance+i*square_length,distance,distance+i*square_length,distance+(BoardSize-1)*square_length);//画竖线

    }
    QBrush brush; //笔刷
    brush.setStyle(Qt::SolidPattern);
    if(clickPosX>=0&&clickPosX<BoardSize&&clickPosY>=0&&clickPosY<BoardSize&&game->state==1&&game->board[clickPosX][clickPosY]==0)  //范围内有效，绘制鼠标将要落子的标记点
    {
        if(game->player)
        {
            brush.setColor(Qt::black);
            painter.setBrush(brush);
            painter.drawRect(distance + square_length * clickPosX - flag_length / 2, distance + square_length * clickPosY  - flag_length / 2, flag_length, flag_length);
        }
        else if(game->player==false)
        {
            brush.setColor(Qt::white);
            painter.setBrush(brush);
            painter.drawRect(distance + square_length * clickPosX - flag_length / 2, distance + square_length * clickPosY  - flag_length / 2, flag_length, flag_length);
        }

    }

    for(int i=0;i<BoardSize;i++)
    {
        for(int j=0;j<BoardSize;j++)
        {

            if(game->board[i][j]==1&&game->state==1)
           {
              brush.setColor(Qt::black);
              painter.setBrush(brush);
              painter.drawEllipse(QPoint(distance + square_length * i ,distance + square_length * j),r,r);
           }
            else if(game->board[i][j]==-1&&game->state==1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(distance + square_length * i ,distance + square_length * j),r,r);
            }
        }
    }
    update();

}

void MainWindow::initgame()   //初始化
{

        game=new Game;

}
void MainWindow::init()
{
    if(game)
    {
        delete game;
    }
    game=new Game;

    game->state=1;

    clickPosX=-1;
    clickPosY=-1;

    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    int x=event->x();
    int y=event->y();

    //保证鼠标在有效范围内,且棋盘边缘不落子
    if (x >= distance-MouseRange  &&
        x <= distance+(BoardSize-1)*square_length+MouseRange  &&
        y >= distance-MouseRange  &&
        y <= distance+(BoardSize-1)*square_length+MouseRange&&game->state==1)
    {

        int row=(x)/square_length;
        int col=(y)/square_length;

        int leftTopPosX = distance + square_length * row;
        int leftTopPosY = distance + square_length * col;
        //周围一共四个点，根据两点距离选最近的
        clickPosX = -1;
        clickPosY = -1;
        int len = 0;

        //确定一个允许范围内的点
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < MouseRange)
        {
            clickPosX = row;
            clickPosY = col;
        }
        len = sqrt((x - leftTopPosX - square_length) * (x - leftTopPosX - square_length) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < MouseRange)
        {
            clickPosX = row+1;
            clickPosY = col;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - square_length) * (y - leftTopPosY - square_length));
        if (len < MouseRange)
        {
            clickPosX = row;
            clickPosY = col+1;
        }
        len = sqrt((x - leftTopPosX - square_length) * (x - leftTopPosX - square_length) + (y - leftTopPosY - square_length) * (y - leftTopPosY - square_length));
        if (len < MouseRange)
        {
            clickPosX = row + 1;
            clickPosY = col + 1;
        }

    }
        update();
}
// 存坐标后更新

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
      if (clickPosX != -1 && clickPosY != -1&&game->state==1)
      {
              play();
      }

      update();
}

void MainWindow::play()
{

    if (clickPosX != -1 && clickPosY != -1 && game->board[clickPosX][clickPosY] == 0)
    {
        game->move(clickPosX,clickPosY);

        isEnd();
        update();
    }
}

void MainWindow::isEnd()
{
    if(clickPosX>=0&&clickPosX<BoardSize&&clickPosY>=0&&clickPosY<BoardSize&&game->board[clickPosX][clickPosY]!=0) //判断游戏输赢
    {
        if(game->board[clickPosX][clickPosY]==1&&on_jinshou&&game->isBalanceBreaker(clickPosX,clickPosY)&&game->state==1)  //判断黑棋落子是否禁手
        {

            QMessageBox::StandardButton standar=QMessageBox::information(this,"游戏结束","禁手 白方胜\n 点击Ok返回主界面",QMessageBox::Ok);
            if(standar==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("开始");

            }
        }
        else if(game->isWin(clickPosX,clickPosY)==true&&game->state==1)  //弹出提示框
        {

            QString string;
            if(game->board[clickPosX][clickPosY]==1)
            {
                string="黑棋胜";
            }
            else
            {
                string="白棋胜";
            }
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this," 游戏结束 ",string+"\n"+" 点击 Ok 返回主界面",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("开始");

            }
        }
        else if(game->isDraw()&&game->state==1)
        {

            game->state=0;
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this,"游戏结束","和棋\n 点击Ok返回主界面",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("开始");

            }
        }
    }
}


void MainWindow::on_pushButton_clicked()
{

     ui->centralWidget->setMouseTracking(true);
     setMouseTracking(true);//激活整个窗体的鼠标追踪
     ui->pushButton->setMouseTracking(true);//激活按钮的鼠标追踪功能

     init();
     ui->pushButton->setText("游戏进行中");

     //qDebug()<<"开始";
     update();
}



