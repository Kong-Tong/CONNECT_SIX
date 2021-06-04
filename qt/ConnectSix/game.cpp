#include "game.h"
#include"mainwindow.h"
#include <utility>
#include <stdlib.h>
#include <time.h>
#include<QDebug>
#include<QApplication>
#include<iostream>
#include<vector>
#include<QTimer>

using namespace std;

const int board_size=21;  //棋盘尺寸

Game::Game()
{
   black=1;
   white=-1;
   state=0;
}

void Game::startgame()
{
    clear();
    player=true;
}

void Game::clear()
{
    for(int i=0;i<board_size;i++)
    {
        for(int j=0;j<board_size;j++)
        {
            board[i][j]=0;  //数组初始化置0
        }
    }
}
void Game::updateMap(int x,int y)
{
    if(player)  //根据下棋方填充数组
    {
        board[x][y]=1;
        player=false;
    }
    else
    {
         board[x][y]=-1;
         player=true;
    }
    //qDebug()<<player;
}
void Game::move(int x, int y)
{
    updateMap(x,y);
}

bool Game::isWin(int X,int Y)  //判断游戏输赢
{

    for (int i = 0; i < 6; i++)
    {
         if (Y - i >= 0 &&
            Y - i + 5 < board_size &&
            board[X][Y - i] == board[X][Y - i + 1] &&
            board[X][Y - i] == board[X][Y - i + 2] &&
            board[X][Y - i] == board[X][Y - i + 3] &&
            board[X][Y - i] == board[X][Y - i + 4]&&
            board[X][Y-i]==board[X][Y-i+5])  //竖直方向
         {
           return true;
         }
         else if (X - i >= 0 &&
             X - i + 5 < board_size &&
             board[X - i][Y] == board[X - i + 1][Y] &&
             board[X - i][Y] == board[X - i + 2][Y] &&
             board[X - i][Y] == board[X - i + 3][Y] &&
             board[X - i][Y] == board[X - i + 4][Y]&&
             board[X - i][Y] == board[X - i + 5][Y])  //水平方向
         {
             return true;
         }
         else if(X+i<board_size&&X+i-5>=0&&Y-i>=0&&Y-i+5<board_size&&
                 board[X+i][Y-i]==board[X+i-1][Y-i+1]&&
                 board[X+i][Y-i]==board[X+i-2][Y-i+2]&&
                 board[X+i][Y-i]==board[X+i-3][Y-i+3]&&
                 board[X+i][Y-i]==board[X+i-4][Y-i+4]&&
                 board[X+i][Y-i]==board[X+i-5][Y-i+5])  //斜向左下
         {
             return true;
         }
         else if (X - i >= 0 &&
                  X - i + 5 < board_size &&
                  Y - i >= 0 &&
                  Y - i + 5 < board_size &&
                  board[X - i][Y - i] == board[X - i + 1][Y - i + 1] &&
                  board[X - i][Y - i] == board[X - i + 2][Y - i + 2] &&
                  board[X - i][Y - i] == board[X - i + 3][Y - i + 3] &&
                  board[X - i][Y - i] == board[X - i + 4][Y - i + 4]&&
                  board[X - i][Y - i] == board[X - i + 5][Y - i + 5]) //斜向右下
              {
                  return true;
              }

    }
    return false;
}
bool Game::isDraw()
{
    //棋盘全部占满棋子则和棋，有空位则不是和棋
    for(int i=0;i<board_size;i++)
    {
        for(int j=0;j<board_size;j++)
        {
            if(board[i][j]==0)
            {
                return false;
            }
        }
    }
    return true;
}

bool Game::isBalanceBreaker(int x, int y)
{
    int num=0,k=0;
    k=0;
    //向上
    for(int i=0;i<6;i++)
    {
        if(y+i<board_size)
        {
            if(board[x][y+i]==1)
            {
                k++;
            }
            else if(board[x][y+i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    k=0;
    if(num>=2)
    {
        return true;
    }
    //向下
    for(int i=0;i<6;i++)
    {
        if(y-i>=0)
        {
            if(board[x][y-i]==1)
            {
                k++;
            }
            else if(board[x][y-i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向左
    for(int i=0;i<6;i++)
    {
        if(x-i>=0)
        {
            if(board[x-i][y]==1)
            {
                k++;
            }
            else if(board[x-i][y]==white)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向右
    for(int i=0;i<6;i++)
    {
        if(x+i<board_size)
        {
            if(board[x+i][y]==1)
            {
                k++;
            }
            else if(board[x+i][y]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向左上
    for(int i=0;i<6;i++)
    {
        if(x-i>=0&&y-i>=0)
        {
            if(board[x-i][y-i]==1)
            {
                k++;
            }
            else if(board[x-i][y-i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向左下
    for(int i=0;i<6;i++)
    {
        if(x-i>=0&&y+i<board_size)
        {
            if(board[x-i][y+i]==1)
            {
                k++;
            }
            else if(board[x-i][y+i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向右上
    for(int i=0;i<6;i++)
    {
        if(x+i<board_size&&y-i>=0)
        {
            if(board[x+i][y-i]==1)
            {
                k++;
            }
            else if(board[x+i][y-i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向右下
    for(int i=0;i<6;i++)
    {
        if(x+i<board_size&&y+i<board_size)
        {
            if(board[x+i][y+i]==1)
            {
                k++;
            }
            else if(board[x+i][y+i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    return false;


}
