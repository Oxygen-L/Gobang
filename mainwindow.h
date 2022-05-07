#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "gobangai.h"

#define CRA(X, Y, Width, Height) (event->x() >= (X) && event->x() <= (X) + (Width) &&  event->y() >= (Y) && event->y() <= (Y) + (Height))

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);      //绘图函数
    void PaintChessboard(QPainter&);    //绘制棋盘以及棋子
    void PaintLastChessman(QPainter&);  //绘制上个棋子的位置
    void PaintCurChessman(QPainter&);   //绘制当前鼠标所在棋盘中的位置
    void PaintWinCase(QPainter&);       //绘制胜者五子

    void init();                        //初始化函数

    int check(int);                     //判断棋局是否结束（胜，负，平）
    void robot_place();                 //机器下棋
    void place_chessman(QPoint, int);   //将某棋子下在某点处

    void mouseMoveEvent(QMouseEvent *); //鼠标移动事件
    void mousePressEvent(QMouseEvent *);//鼠标点击事件

    void out_chessboard();

    ~MainWindow();

private slots:
    void on_start_clicked();            //游戏开始

    void on_black_chessman_clicked();   //选择黑色棋子

    void on_white_chessman_clicked();   //选择白色棋子

    void on_first_clicked();            //选择先手

    void on_second_clicked();           //选择后手

    void on_diff1_clicked();            //选择游戏难度为“简单”

    void on_diff2_clicked();            //选择游戏难度为“普通”

    void on_diff3_clicked();            //选择游戏难度为“困难”

    void on_diff4_clicked();            //选择游戏难度为“地狱”

    void on_export_chess_triggered();   //导出棋局

    void on_import_chess_triggered();   //导入棋局

private:
    Ui::MainWindow *ui;
    int Width = 1060;
    int Height = 760;

    int map[16][16];

    int BoW=0, FoS=0;

    int difficulty=0;

    int my_color, robot_color;

    bool START = false;
    bool my_turn = false;

    bool robot_win = false, i_win = false, draw = false;

    QPoint last_chessman_pos = QPoint(-1,-1);
    QPoint cur_chessman_pos = QPoint(-1,-1);
    QPoint win_case[5];
};
#endif // MAINWINDOW_H
