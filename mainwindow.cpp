#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋");
    this->setFixedSize(Width,Height);
    this->setWindowIcon(QIcon(":/imgs/icon.png"));


}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    PaintChessboard(painter);

}

void MainWindow::PaintChessboard(QPainter &paint){
    paint.drawPixmap(0,0,Width,Height,QPixmap(":/imgs/chessboard.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

