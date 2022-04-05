#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>
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

    void paintEvent(QPaintEvent*);
    void PaintChessboard(QPainter&);
    void PaintLastChessman(QPainter&);
    void PaintCurChessman(QPainter&);
    void PaintWinCase(QPainter&);

    void init();

    int check(int);
    void robot_place();
    void place_chessman(QPoint, int);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_black_chessman_clicked();

    void on_white_chessman_clicked();

    void on_first_clicked();

    void on_second_clicked();

private:
    Ui::MainWindow *ui;
    int Width = 1060;
    int Height = 760;

    int map[15][15];

    int BoW=0, FoS=0;

    int my_color, robot_color;

    bool START = false;
    bool my_turn = false;

    bool robot_win = false, i_win = false, draw = false;

    QPoint last_chessman_pos = QPoint(-1,-1);
    QPoint cur_chessman_pos = QPoint(-1,-1);
    QPoint win_case[5];
};
#endif // MAINWINDOW_H
