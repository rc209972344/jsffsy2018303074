#ifndef QUESTION3_H
#define QUESTION3_H
#include <iostream>
#include <cmath>
//#include "Matrix.cpp"
using namespace std;

void question3(){
    //数据输入
    cout<<"请输入增广矩阵的行数和列数,其中系数矩阵须为方阵:"<<endl;
    int r = 0, c = 0;
    cin>>r>>c;
    if((r!=c-1)){//判断系数矩阵是否为方阵
		cout<<"矩阵不符合要求"<<endl;
		abort();
	}
    Matrix A = Matrix(r,c);
    cout<<"请输入增广矩阵元素:"<<endl;
    cin>>A;

    //计算得到三角分解后的矩阵并输出
    Matrix LU = A.Doolittle();
    cout<<"LU矩阵为:"<<endl;
    LU.printmatrix();

    //按公式计算x并输出结果
    double x[r];
    cout<<"结果为:"<<endl;
    for(int i = r-1; i >= 0; i--){
        x[i] = LU.getpoint(i,c-1);
        for(int j = r-1; j > i; j--){
            x[i] = x[i] - x[j]*LU.getpoint(i,j);
        }
        x[i] = x[i]/LU.getpoint(i,i);
        cout<<"x"<<i+1<<" = "<<x[i]<<endl;
    }
}

#endif
