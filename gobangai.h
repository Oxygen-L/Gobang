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
    gobangAI(int a[][16], int color1, int color2,int diff);
    bool around(int x,int y);
    bool END(int COL);

    QPoint cur_place;

    int dfs(int depth);
    int MINMAX(int depth,int alpha, int beta);
    void tanxin();

    void place(QPoint x, int color);
    void calc_f(int);
    int calc_value(int color);
    int calc_five(int *a,int color, bool is_en);
    int map[16][16];
    int my_color,e_color;
    int f_v;
    int dif;

    int kyb=0;
    QPoint aim_pos = QPoint(7,7);
};

#endif // GOBANGAI_H
