#ifndef GAME_H
#define GAME_H

//#include <Gmae>

class Game
{

public:
    Game();
    int state; //游戏状态，1为正在进行，0为未进行
    bool player; //下棋方
    void clear();  //清理棋盘
    bool isWin(int x,int y);//判断是否输赢
    bool isDraw();  //判断是否和棋
    //bool isJinShou_0(int x,int y); //对某点判断是否禁手
    bool isBalanceBreaker(int x,int y); //判断是否禁手
    void startgame();  //开始游戏
    void updateMap(int x, int y); //更新棋盘
    void move(int x,int  y); //下棋
    int board[21][21];  //数组记录棋盘棋子，空格0，白子-1，黑子1
    int white,black;
};

#endif // GAME_H
