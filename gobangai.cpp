#include "gobangai.h"

gobangAI::gobangAI()
{
    memset(map,0,sizeof(map));
}

gobangAI::gobangAI(int a[][15], int color1, int color2)
{
    my_color = color1;
    e_color = color2;
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
            map[i][j] = a[i][j];
        }
    }
}

QPoint gobangAI::calc_point()
{
    QPoint res;
    int n = (long long)rand()*rand() % 15;
    int m = (long long)rand()*rand()*rand() % 15;
    while(map[n][m] != 0){
        n = (long long)rand()*rand() % 15;
        m = (long long)rand()*rand()*rand() % 15;
    }
    res.setX(n),res.setY(m);
    return res;

}
