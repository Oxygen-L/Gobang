#ifndef GOBANGAI_H
#define GOBANGAI_H

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <QPoint>
#include <vector>
#include <cstdio>
#include <iostream>
#include <QVector>
#include <algorithm>
#include <QMap>

#define BLACK 0x1111
#define WHITE 0x2222
#define FIRST 0x3333
#define SECOND 0x4444
#define WALL 0x5555
#define LL long long

QPoint get_pos(int a[][16], int color1, int color2,int diff);
QPoint test_1(int a[][16],int color1,int color2,int diff);
QPoint test_2(int a[][16],int color1,int color2,int diff);

class gobangAI
{
public:

    gobangAI();
    gobangAI(int a[][16], int color1, int color2,int diff); //构造函数
    bool around(int x,int y);                       //判断(x,y)处周围九格中是否有棋子
    bool END(int COL);                              //判断某种颜色的棋子是否连成了五个

    void place(QPoint x, int color);                //将某种颜色的棋子放在棋盘上某点
    void calc_f(int);                               //计算当前棋盘局面的分值
    int calc_value(int color);                      //整个棋盘局面的估值函数
    int calc_five(int *a,int color, bool is_en);    //整个棋盘局面的估值函数

    void tanxin();                                  //一种贪心算法，对应游戏中的普通难度
    int dfs(int depth);                             //贪心算法中使用的搜索函数

    int MINMAX(int depth,int alpha, int beta);      //MINMAX搜索算法


    int map[16][16];
    int my_color,e_color;
    int f_v;
    int dif;
    int kyb=0;
    QPoint aim_pos = QPoint(7,7);
    QPoint cur_place;
};

#endif // GOBANGAI_H
