#ifndef GOBANGAI_H
#define GOBANGAI_H

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <QPoint>

#define BLACK 0x1111
#define WHITE 0x2222
#define FIRST 0x3333
#define SECOND 0x4444


class gobangAI
{
public:
    gobangAI();
    gobangAI(int a[][15], int color1, int color2);

    QPoint calc_point();

private:
    int map[15][15];
    int my_color,e_color;
};

#endif // GOBANGAI_H
