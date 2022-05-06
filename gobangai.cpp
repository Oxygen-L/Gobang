#include "gobangai.h"

int wi[15][15] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
    {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
    {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

struct Node{
    QPoint poi;
    int val;
};

bool cmp(Node x,Node y){
    return x.val>y.val;
}

gobangAI::gobangAI()
{
    memset(map,0,sizeof(map));
}

gobangAI::gobangAI(int a[][16], int color1, int color2, int diff)
{
    my_color = color1;
    e_color = color2;
    dif = diff;
    for(int i=0;i<=15;++i){
        for(int j=0;j<=15;++j){
            map[i][j] = a[i][j];
        }
    }
}

bool gobangAI::around(int x, int y)
{
    int sum = 0;
//    sum += ((x-2>=0&&y-2>=0)?map[x-2][y-2]:0);
//    sum += ((x-2>=0&&y-1>=0)?map[x-2][y-1]:0);
//    sum += ((x-2>=0&&y>=0)?map[x-2][y]:0);
//    sum += ((x-2>=0&&y+1<15)?map[x-2][y+1]:0);
//    sum += ((x-2>=0&&y+2<15)?map[x-2][y+2]:0);

//    sum += ((x-1>=0&&y-2>=0)?map[x-1][y-2]:0);
    sum += ((x-1>=0&&y-1>=0)?map[x-1][y-1]:0);
    sum += ((x-1>=0&&y>=0)?map[x-1][y]:0);
    sum += ((x-1>=0&&y+1<15)?map[x-1][y+1]:0);
//    sum += ((x-1>=0&&y+2<15)?map[x-1][y+2]:0);

//    sum += ((x>=0&&y-2>=0)?map[x][y-2]:0);
    sum += ((x>=0&&y-1>=0)?map[x][y-1]:0);
    sum += ((x>=0&&y+1<15)?map[x][y+1]:0);
//    sum += ((x>=0&&y+2<15)?map[x][y+2]:0);

//    sum += ((x+1<15&&y-2>=0)?map[x+1][y-2]:0);
    sum += ((x+1<15&&y-1>=0)?map[x+1][y-1]:0);
    sum += ((x+1<15&&y>=0)?map[x+1][y]:0);
    sum += ((x+1<15&&y+1<15)?map[x+1][y+1]:0);
//    sum += ((x+1<15&&y+2<15)?map[x+1][y+2]:0);

//    sum += ((x+2<15&&y-2>=0)?map[x+2][y-2]:0);
//    sum += ((x+2<15&&y-1>=0)?map[x+2][y-1]:0);
//    sum += ((x+2<15&&y>=0)?map[x+2][y]:0);
//    sum += ((x+2<15&&y+1<15)?map[x+2][y+1]:0);
//    sum += ((x+2<15&&y+2<15)?map[x+2][y+2]:0);

    if(sum==0) return 0;

    return 1;
}

bool gobangAI::END(int COL)
{
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            //横向判断
            if(j+4<15&&map[i][j]==COL&&map[i][j+1]==COL&&map[i][j+2]==COL&&map[i][j+3]==COL&&map[i][j+4]==COL){
                return 1;
            }

            //纵向判断
            if(i+4<15&&map[i][j]==COL&&map[i+1][j]==COL&&map[i+2][j]==COL&&map[i+3][j]==COL&&map[i+4][j]==COL){
                return 1;
            }

            //左斜判断
            if(i-4>=0&&j+4<15&&map[i][j]==COL&&map[i-1][j+1]==COL&&map[i-2][j+2]==COL&&map[i-3][j+3]==COL&&map[i-4][j+4]==COL){
                return 1;
            }

            //右斜判断
            if(i+4<15&&j+4<15&&map[i][j]==COL&&map[i+1][j+1]==COL&&map[i+2][j+2]==COL&&map[i+3][j+3]==COL&&map[i+4][j+4]==COL){
                return 1;
            }
        }
    }
    return 0;

}

int gobangAI::MINMAX(int depth, int alpha, int beta)
{
    if(END(my_color)){
        return ((1<<30)-7);
    }
    if(END(e_color)){
        return (-(1<<30)+depth*10);
    }
    if(depth == ((dif==3)?4:5)){
        calc_f((depth%2)==1?my_color:my_color);
        return f_v;
    }
    QVector<Node> vi;
    vi.clear();
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            if(map[i][j]==0&&around(i,j)==1){
                place(QPoint(i,j),(depth%2)==1?my_color:e_color);
                calc_f((depth%2)==1?my_color:e_color);
                Node tmp;
                tmp.poi = QPoint(i,j);
                tmp.val = f_v;
                vi.push_back(tmp);
                place(QPoint(i,j),0);
            }
        }
    }
    std::sort(vi.begin(),vi.end(),cmp);

    if(depth%2==1){
        for(int i=0;i<qMin(vi.size(),(dif==3)?47:25);++i){
            place(vi[i].poi,(depth%2)==1?my_color:e_color);
            int t_val=MINMAX(depth+1,alpha,beta);
            place(vi[i].poi,0);
            if(t_val > alpha){
                alpha = t_val;
                if(depth == 1) aim_pos = vi[i].poi;
            }
            if(alpha>beta){
                return alpha;
            }
        }
        return alpha;
    }else{
        for(int i=0;i<qMin(vi.size(),(dif==3)?47:25);++i){
            place(vi[i].poi,(depth%2)==1?my_color:e_color);
            int t_val=MINMAX(depth+1,alpha,beta);
            place(vi[i].poi,0);
            if(t_val < beta){
                beta = t_val;
                if(depth == 1) aim_pos = vi[i].poi;
            }
            if(alpha>beta){
                return beta;
            }
        }
        return beta;
    }
}

int gobangAI::dfs(int depth)
{
    if(END(my_color)){
        return (1<<30);
    }
    if(END(e_color)){
        return (-(1<<30)+depth*10);
    }
    if(depth == 12){
        calc_f(my_color);
        return f_v;
    }
    QPoint vi;
    int max_val=-(1<<30);
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            if(map[i][j]==0&&around(i,j)==1){
                place(QPoint(i,j),(depth%2==1)?my_color:e_color);
                if(depth%2==1){
                    calc_f(my_color);
                }else{
                    calc_f(e_color);
                }
                if(f_v > max_val){
                    vi = QPoint(i,j);
                    max_val = f_v;
                }
                place(QPoint(i,j),0);
            }
        }
    }

    int t_val;
    place(vi,(depth%2==1)?my_color:e_color);
    t_val = dfs(depth+1);
    place(vi,0);
    return t_val;
}

void gobangAI::tanxin()
{
    QVector<Node> vi;
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            if(map[i][j]==0&&around(i,j)==1){
                place(QPoint(i,j),my_color);
                calc_f(my_color);
                Node tmp;
                tmp.poi = QPoint(i,j);
                tmp.val = f_v;
                vi.push_back(tmp);
                place(QPoint(i,j),0);
            }
        }
    }
    std::sort(vi.begin(),vi.end(),cmp);

    int max_val = -(1<<30);
    for(int i=0;i<qMin(vi.size(),107);++i){
        place(vi[i].poi,my_color);
        int t_val=dfs(2);
        place(vi[i].poi,0);
        if(t_val > max_val){
            max_val = t_val;
            aim_pos = vi[i].poi;
        }
    }
}

void gobangAI::place(QPoint x, int color)
{
    cur_place = x;
    map[x.x()][x.y()] = color;
}

void gobangAI::calc_f(int color1)
{
    f_v = calc_value(color1) + wi[cur_place.x()][cur_place.y()];
}

int gobangAI::calc_value(int color)
{
    int res=0;
    int tmp[7];
    int en_col = ((color==BLACK)?WHITE:BLACK);
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            //横向判断
            if(j+5<=15){
                tmp[0] = map[i][j];
                tmp[1] = map[i][j+1];
                tmp[2] = map[i][j+2];
                tmp[3] = map[i][j+3];
                tmp[4] = map[i][j+4];
                tmp[5] = map[i][j+5];
                int tmp1 = calc_five(tmp,color,0);
                int tmp2 = calc_five(tmp,en_col,1);
                res += (tmp1-tmp2);
//                res += (calc_five(tmp,color,0)-calc_five(tmp,en_col,1));
            }


            //纵向判断
            if(i+5<=15){
                tmp[0] = map[i][j];
                tmp[1] = map[i+1][j];
                tmp[2] = map[i+2][j];
                tmp[3] = map[i+3][j];
                tmp[4] = map[i+4][j];
                tmp[5] = map[i+5][j];
                int tmp1 = calc_five(tmp,color,0);
                int tmp2 = calc_five(tmp,en_col,1);
                res += (tmp1-tmp2);
//                res += (calc_five(tmp,color,0)-calc_five(tmp,en_col,1));
            }

            //左斜判断
            if(i-5>=0&&j+5<=15){
                tmp[0] = map[i][j];
                tmp[1] = map[i-1][j+1];
                tmp[2] = map[i-2][j+2];
                tmp[3] = map[i-3][j+3];
                tmp[4] = map[i-4][j+4];
                tmp[5] = map[i-5][j+5];
                int tmp1 = calc_five(tmp,color,0);
                int tmp2 = calc_five(tmp,en_col,1);
                res += (tmp1-tmp2);
//                res += (calc_five(tmp,color,0)-calc_five(tmp,en_col,1));
            }

            //右斜判断
            if(i+5<=15&&j+5<=15){
                tmp[0] = map[i][j];
                tmp[1] = map[i+1][j+1];
                tmp[2] = map[i+2][j+2];
                tmp[3] = map[i+3][j+3];
                tmp[4] = map[i+4][j+4];
                tmp[5] = map[i+5][j+5];
                int tmp1 = calc_five(tmp,color,0);
                int tmp2 = calc_five(tmp,en_col,1);
                res += (tmp1-tmp2);
//                res += (calc_five(tmp,color,0)-calc_five(tmp,en_col,1));
            }
        }
    }
    return res;
}

int gobangAI::calc_five(int a[], int color, bool is_en)
{

    int anti_col = (color==BLACK)?WHITE:BLACK;

//    成五   :
    if(a[1]==color&&a[2]==color&&a[3]==color&&a[4]==color&&a[0]==color){
        if(is_en) return 1000000;
        else return 1000000;

    }

//    活四   :
    if(a[1]==color&&a[2]==color&&a[3]==color&&a[4]==color&&a[0]==0&&a[5]==0){
        if(is_en) return 95000;
        else return 93000;
    }

//    冲四   :
    if((a[0]==0&&a[1]==color&&a[2]==color&&a[3]==color&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==color&&a[3]==color&&a[4]==color&&a[5]==0)||
        (a[0]==color&&a[1]==0&&a[2]==color&&a[3]==color&&a[4]==color)||
        (a[0]==color&&a[1]==color&&a[2]==0&&a[3]==color&&a[4]==color)||
        (a[0]==color&&a[1]==color&&a[2]==color&&a[3]==0&&a[4]==color)){
        if(is_en) return 94000;
        else return 30000;
    }

//    活三   :
    if((a[0]==0&&a[1]==color&&a[2]==color&&a[3]==color&&a[4]==0)||
        (a[0]==0&&a[1]==color&&a[2]==0&&a[3]==color&&a[4]==color&&a[5]==0)||
        (a[0]==0&&a[1]==color&&a[2]==color&&a[3]==0&&a[4]==color&&a[5]==0)){
        if(is_en) return 62000;
        else return 30000;
    }

//    眠三   :
    if((a[0]==0&&a[1]==0&&a[2]==color&&a[3]==color&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==color&&a[3]==color&&a[4]==0&&a[5]==0)||
        (a[0]==0&&a[1]==color&&a[2]==0&&a[3]==color&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==color&&a[3]==0&&a[4]==color&&a[5]==0)||
        (a[0]==0&&a[1]==color&&a[2]==color&&a[3]==0&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==0&&a[3]==color&&a[4]==color&&a[5]==0)||
        (a[0]==color&&a[1]==0&&a[2]==0&&a[3]==color&&a[4]==color)||
        (a[0]==color&&a[1]==color&&a[2]==0&&a[3]==0&&a[4]==color)||
        (a[0]==color&&a[1]==0&&a[2]==color&&a[3]==0&&a[4]==color)){
        if(is_en) return 470;
        else return 500;
    }

//    活二   :
    if((a[0]==0&&a[1]==0&&a[2]==color&&a[3]==color&&a[4]==0&&a[5]==0)||
        (a[0]==0&&a[1]==color&&a[2]==0&&a[3]==color&&a[4]==0)||
        (a[0]==0&&a[1]==color&&a[2]==0&&a[3]==0&&a[4]==color&&a[5]==0)){
        if(is_en) return 430;
        else return 450;
    }

//    眠二   :
    if((a[0]==0&&a[1]==0&&a[2]==0&&a[3]==color&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==color&&a[3]==0&&a[4]==0&&a[5]==0)||
        (a[0]==0&&a[1]==0&&a[2]==color&&a[3]==0&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==0&&a[3]==color&&a[4]==0&&a[5]==0)||
        (a[0]==0&&a[1]==color&&a[2]==0&&a[3]==0&&a[4]==color&&a[5]==anti_col)||
        (a[0]==anti_col&&a[1]==color&&a[2]==0&&a[3]==0&&a[4]==color&&a[5]==0)||
        (a[0]==color&&a[1]==0&&a[2]==0&&a[3]==0&&a[4]==color)){
        if(is_en) return 410;
        else return 430;
    }

    return 1;
}

QPoint get_pos(int a[][16], int color1, int color2,int diff){
    gobangAI root(a,color1,color2,diff);
    if(diff == 2){
        root.tanxin();
    }else{
        root.MINMAX(1,-(1<<30),(1<<30));
    }
    return root.aim_pos;
}

QPoint test_1(int a[][16], int color1, int color2,int diff)
{
    gobangAI root(a,color1,color2,diff);
    QPoint res;
    int n = (long long)rand()*rand() % 15;
    int m = (long long)rand()*rand()*rand() % 15;
    while(a[n][m] != 0){
        n = (long long)rand()*rand() % 15;
        m = (long long)rand()*rand()*rand() % 15;
    }
    res.setX(n),res.setY(m);
    return res;
}

QPoint test_2(int a[][16], int color1, int color2,int diff)
{
    int value = -(1<<30);
    QPoint res;
    gobangAI t(a,color1,color2,diff);
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            if(t.map[i][j] == 0){
                t.place(QPoint(i,j),t.my_color);
                t.calc_f(t.my_color);
                t.place(QPoint(i,j),0);
                if(t.f_v+wi[i][j] > value){
                    res = QPoint(i,j);
                    value = t.f_v+wi[i][j];
                }
            }
        }
    }
    return res;
}
