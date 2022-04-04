#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

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

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int Width = 1060;
    int Height = 760;
};
#endif // MAINWINDOW_H
