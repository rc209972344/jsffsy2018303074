#ifndef QUESTION2_H
#define QUESTION2_H
#include <iostream>
#include <cmath>
#include <ctime>
//#include "Matrix.cpp"
using namespace std;

void question2(){
    //输入数据
    cout<<"请输入增广矩阵的行数和列数,其中系数矩阵须为方阵:"<<endl;
    int r = 0, c = 0;
    cin>>r>>c;
    if((r!=c-1)){
		cout<<"矩阵不符合要求"<<endl;
		abort();
	}
    Matrix * zg = new Matrix(r,c);//创建增广矩阵
    cout<<"请输入增广矩阵元素:"<<endl;
    cin>>*zg;
    double seidel[r][c];
    cout<<"请按顺序输入初始向量:"<<endl;
    for(int i = 0; i < r; i++){//用增广矩阵初始化Seidel矩阵用于计算
        for(int j = 0; j < c; j++){
            if((i != j)&&(j != c-1))seidel[i][j] = -zg->getpoint(i,j)/zg->getpoint(i,i);
            else if(i == j)cin>>seidel[i][j];
            else if(j == c-1)seidel[i][j] = zg->getpoint(i,j)/zg->getpoint(i,i);
        }
    }
    /*
    计算原理：（以4x3矩阵为例）
    4x3的seidel矩阵形如：
    x1(S[0,0])  a12(S[0,1]) a13(S[0,2]) g1(S[0,3])
    a21(S[1,0]) x2(S[1,1])  a23(S[1,2]) g2(S[1,3])
    a31(S[2,0]) a32(S[2,1]) x3(S[2,2])  g3(S[2,3])
    其中两角标相等的元素在初始化时存入了初始向量x1，x2，x3
    而Seidel迭代计算为（以第二行为例）：x2(k+1) = a1*x1(k+1) + a3*x3(k) + g2
    而由于该矩阵的特殊结构，观察可以发现
    按行计算xi(k+1)时（即计算每一行行列角标相等的元素时），只需：
    1.循环某行时先将此行xi=0
    2.当行列角标不等且列角标不等于3时，xi(S[m,m]) = xi(S[m,m]) + S[m,n]*S[n,n]，其中m为行角标，n为列角标
    3.逐行计算，遇到xi(行列角标相等)跳过，否则按2计算，每循环完一行，xi(S[m,m]) = xi(S[m,m]) + gi(S[m,3])。
      以计算第二行为例，就变成x2 = x2 + a21*x1，跳过，x2 = x2 + a23*x3，x2 = x2 + g2
    4.每次循环完三行，可得到一组新的x1，x2，x3。
    5.至于记录两次xi差值的方法不做赘述
    第2、3条的原理在于：由于结构特殊（开始只是想节省储存空间），按行循环时，算过的行中的xi(行列角标相等)为xi(k+1)，如以第二行为例计算时用到的的x1
                     而没有算过的行中的xi为xi(k)，如以第二行为例计算时的x3。看见正在计算的行中的xi就可以按这种方法计算。
                     且主要算法实现简单代码简洁，少用了一次循环降低了复杂度。

    */
    delete zg;
    
    //定义一些用于判断停止条件的变量
    double d = 100;
    cout<<"请输入最大误差:"<<endl;
    cin>>d;//要求的最大差值
    double D = 1;//用于记录每次算完一轮所有xi(k+1)之后得到的最大的xi(k+1)-xi(k)
    double flag = 0;//用于记录每行计算前改行的原来的xi，用于和算完后的xi(k+1)作差算最大差值
    clock_t start,current;//用于记录时间，计算时间过长可能是Seidel迭代对所选初始向量不收敛
    start = clock();
    
    //公式计算
    while(D>d){
        D = 0;
        for(int i = 0; i < r; i++){
            flag = seidel[i][i];
            seidel[i][i] = 0;
            for(int j = 0; j < c-1; j++){
                if(i == j)continue;
                else{
                    seidel[i][i] = seidel[i][i] + seidel[j][j]*seidel[i][j];
                }
            }
            seidel[i][i] = seidel[i][i] + seidel[i][c-1];
            D = abs(flag - seidel[i][i])>D?abs(flag - seidel[i][i]):D;
        }
        current = clock();
        if(((current-start)/CLOCKS_PER_SEC)>10){
            cout<<"用时"<<((current-start)/CLOCKS_PER_SEC)<<"秒,计算超时"<<endl;
            cout<<"Seidel迭代法对此初始向量可能不收敛!"<<endl;
            cout<<"计算终止!"<<endl;
            abort();
        }//不收敛就终止程序
    }

    //输出结果
    cout<<"结果为："<<endl;
    for(int i = 0; i<r; i++){
        cout<<"x"<<i+1<<" = "<<seidel[i][i]<<endl;
    }

}

#endif
