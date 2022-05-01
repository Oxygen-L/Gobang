#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setMouseTracking(true);
    memset(map,0,sizeof(map));
    ui->setupUi(this);
    this->setWindowTitle("五子棋");
    this->setFixedSize(Width,Height);
    this->setWindowIcon(QIcon(":/imgs/icon.png"));
    ui->start->setEnabled(false);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    PaintChessboard(painter);
    PaintCurChessman(painter);
    PaintLastChessman(painter);
    PaintWinCase(painter);
}

void MainWindow::PaintChessboard(QPainter &paint){
    paint.drawPixmap(0,0,Width,Height,QPixmap(":/imgs/chessboard.png"));
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            if(map[i][j] == BLACK){
                paint.drawPixmap(j*50+10,i*50+10,41,41,QPixmap(":/imgs/black.png"));
            }else if(map[i][j] == WHITE){
                paint.drawPixmap(j*50+10,i*50+10,41,41,QPixmap(":/imgs/white.png"));
            }
        }
    }
}

void MainWindow::PaintLastChessman(QPainter &paint)
{
    if(last_chessman_pos != QPoint(-1,-1) && START==true){
        paint.drawPixmap(last_chessman_pos.y()*50+20,last_chessman_pos.x()*50+20,21,21,QPixmap(":/imgs/last_chessman.png"));
    }
}

void MainWindow::PaintCurChessman(QPainter &paint)
{
    if(cur_chessman_pos != QPoint(-1,-1) && START==true && map[cur_chessman_pos.x()][cur_chessman_pos.y()]==0 && my_turn==true){
        paint.drawPixmap(cur_chessman_pos.y()*50+8,cur_chessman_pos.x()*50+8,43,43,QPixmap(":/imgs/cur_chessman.png"));
    }
}

void MainWindow::PaintWinCase(QPainter &paint)
{
    if(robot_win||i_win){
        for(int i=0;i<5;++i){
            paint.drawPixmap(win_case[i].y()*50+20,win_case[i].x()*50+20,21,21,QPixmap(":/imgs/win_chessman.png"));
        }
    }
}

void MainWindow::init()
{
    memset(map,0,sizeof(map));
    for(int i=0;i<=15;++i){
        map[i][15] = map[15][i] = WALL;
    }
    last_chessman_pos = QPoint(-1,-1);
    cur_chessman_pos = QPoint(-1,-1);
}

int MainWindow::check(int COL)
{
    int sum_chessman=0;
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            //和棋判断
            if(map[i][j]!=0) ++sum_chessman;

            //横向判断
            if(j+4<15&&map[i][j]==COL&&map[i][j+1]==COL&&map[i][j+2]==COL&&map[i][j+3]==COL&&map[i][j+4]==COL){
                win_case[0] = QPoint(i,j);
                win_case[1] = QPoint(i,j+1);
                win_case[2] = QPoint(i,j+2);
                win_case[3] = QPoint(i,j+3);
                win_case[4] = QPoint(i,j+4);
                return 1;
            }

            //纵向判断
            if(i+4<15&&map[i][j]==COL&&map[i+1][j]==COL&&map[i+2][j]==COL&&map[i+3][j]==COL&&map[i+4][j]==COL){
                win_case[0] = QPoint(i,j);
                win_case[1] = QPoint(i+1,j);
                win_case[2] = QPoint(i+2,j);
                win_case[3] = QPoint(i+3,j);
                win_case[4] = QPoint(i+4,j);
                return 1;
            }

            //左斜判断
            if(i-4>=0&&j+4<15&&map[i][j]==COL&&map[i-1][j+1]==COL&&map[i-2][j+2]==COL&&map[i-3][j+3]==COL&&map[i-4][j+4]==COL){
                win_case[0] = QPoint(i,j);
                win_case[1] = QPoint(i-1,j+1);
                win_case[2] = QPoint(i-2,j+2);
                win_case[3] = QPoint(i-3,j+3);
                win_case[4] = QPoint(i-4,j+4);
                return 1;
            }

            //右斜判断
            if(i+4<15&&j+4<15&&map[i][j]==COL&&map[i+1][j+1]==COL&&map[i+2][j+2]==COL&&map[i+3][j+3]==COL&&map[i+4][j+4]==COL){
                win_case[0] = QPoint(i,j);
                win_case[1] = QPoint(i+1,j+1);
                win_case[2] = QPoint(i+2,j+2);
                win_case[3] = QPoint(i+3,j+3);
                win_case[4] = QPoint(i+4,j+4);
                return 1;
            }
        }
    }
    if(sum_chessman == 15*15){
        draw = 1;
        return 1;
    }
    return 0;
}

void MainWindow::robot_place()
{
//    last_chessman_pos = test_1(map,robot_color,my_color,difficulty);
    if(difficulty == 1){
        last_chessman_pos = test_2(map,robot_color,my_color,difficulty);
    }else if(difficulty > 1){
        last_chessman_pos = get_pos(map,robot_color,my_color,difficulty);
    }
    place_chessman(last_chessman_pos,robot_color);
    my_turn = !my_turn;
}

void MainWindow::place_chessman(QPoint p, int color)
{
    map[p.x()][p.y()] = color;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.setX(pos.x()-5);
    pos.setY(pos.y()-5);
    if(pos.x()>0&&pos.y()>0&&pos.x()<750&&pos.y()<750){
        cur_chessman_pos.setX(pos.y()/50);
        cur_chessman_pos.setY(pos.x()/50);
    }else{
        cur_chessman_pos = QPoint(-1,-1);
    }
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.setX(pos.x()-5);
    pos.setY(pos.y()-5);
    if(event->button() == Qt::LeftButton && pos.x()>0&&pos.y()>0&&pos.x()<750&&pos.y()<750 && my_turn==true){
        QPoint tmp;
        tmp.setX(pos.y()/50);
        tmp.setY(pos.x()/50);
        if(map[tmp.x()][tmp.y()] != 0){
            return;
        }
        last_chessman_pos = tmp;
        place_chessman(last_chessman_pos,my_color);
        if(check(my_color)){
            i_win = true;
            QMessageBox::information(this, "游戏结束", "恭喜你，你赢了！");
            this->close();
        }
        my_turn = !my_turn;
        robot_place();
        if(check(robot_color)&&(!i_win)){
            robot_win = true;
            QMessageBox::information(this, "游戏结束", "你输了！");
            this->close();
        }
        if(draw){
            QMessageBox::information(this, "游戏结束", "平局！");
            this->close();
        }
    }
    update();
}

void MainWindow::out_chessboard()
{
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            printf("%-4x ",map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    START = true;
    init();
    ui->start->setText("重玩");
    if(FoS == FIRST){
        my_turn = true;
    }else{
        my_turn = false;
        robot_place();
    }
    update();
}

void MainWindow::on_black_chessman_clicked()
{
    BoW = BLACK;
    my_color = BLACK;
    robot_color = WHITE;
    if(BoW!=0 && FoS!=0 && difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_white_chessman_clicked()
{
    BoW = WHITE;
    my_color = WHITE;
    robot_color = BLACK;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_first_clicked()
{
    FoS = FIRST;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_second_clicked()
{
    FoS = SECOND;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_diff1_clicked()
{
    difficulty = 1;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_diff2_clicked()
{
    difficulty = 2;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_diff3_clicked()
{
    difficulty = 3;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_diff4_clicked()
{
    difficulty = 4;
    if(BoW!=0 && FoS!=0&& difficulty!=0){
        ui->start->setEnabled(true);
    }
}

void MainWindow::on_export_chess_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "导出棋局", "chess", "*.txt");
    QFile file(filename);
    QString s = "";
    s += "# 棋局位于 {} 内 ！！！\n"
         "# ‘#’字符为注释！！！\n"
         "# 0：空\n"
         "# 1：黑棋\n"
         "# 2：白棋\n";
    s += ((BoW == BLACK)?"1.BLACK\n":"1.WHITE\n");
    s += ((FoS == FIRST)?"2.defensive\n":"2.offensive\n");
    if(difficulty == 1){
        s += "3.difficulty 1\n";
    }else if(difficulty == 2){
        s += "3.difficulty 2\n";
    }else if(difficulty == 3){
        s += "3.difficulty 3\n";
    }else if(difficulty == 4){
        s += "3.difficulty 4\n";
    }

    s+="\n{\n";
    for(int i=0;i<15;++i){
        s += "   ";
        for(int j=0;j<15;++j){
            s += (map[i][j]==BLACK?"2":(map[i][j]==WHITE?"1":"0"));
            s += ", ";
        }
        s+="\n";
    }
    s+="}\n";
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(s.toUtf8());
    file.close();
}

void MainWindow::on_import_chess_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "导入棋局", ".", "*.txt");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    while(!file.atEnd()){
        QString line = file.readLine();
        if(line[0] == '#') continue;
        if(line[0] == '1'){
            line.remove('1');line.remove('.');line.remove('\n');
            if(line == "BLACK"){
                ui->black_chessman->setChecked(1);
                BoW = BLACK;
                my_color = BLACK;
                robot_color = WHITE;
            }else{
                ui->white_chessman->setChecked(1);
                BoW = WHITE;
                my_color = WHITE;
                robot_color = BLACK;
            }
        }
        if(line[0] == '2'){
            line.remove('2');line.remove('.');line.remove('\n');
            if(line == "defensive"){
                ui->first->setChecked(1);
                FoS = FIRST;
            }else{
                ui->second->setChecked(1);
                FoS = SECOND;
            }
        }
        if(line[0] == '3'){
            difficulty = line[13].digitValue();
            if(difficulty == 1){
                ui->diff1->setChecked(1);
            }else if(difficulty == 2){
                ui->diff2->setChecked(1);
            }else if(difficulty == 3){
                ui->diff3->setChecked(1);
            }else if(difficulty == 4){
                ui->diff4->setChecked(1);
            }
        }
        if(line[0] == '{'){
            for(int i=0;i<15;++i){
                line = file.readLine();
                line.remove(' ');
                line.remove(',');
                for(int j=0;j<15;++j){
                    map[i][j] = (line[j].digitValue()==0?0:(line[j].digitValue()==1?BLACK:WHITE));
                }
            }
            break;
        }
    }
    file.close();
    last_chessman_pos = QPoint(-1,-1);
    cur_chessman_pos = QPoint(-1,-1);
    START = true;
    ui->start->setText("重玩");
    my_turn = true;
    update();
}
