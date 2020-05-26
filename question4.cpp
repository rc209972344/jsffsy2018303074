#include <iostream>
#include <cmath>
//#include"Matrix.cpp"
using namespace std;
const double MINIUM = 1e-8;//小于10^(-10)置零
void question4()
{
    //数据输入
    int n = 3;
    cout<<"请输入方阵维数:"<<endl;
    cin>>n;
    Matrix A(n,n);
    cout<<"请按顺序输入矩阵各元素:"<<endl;
    cin>>A;
    double e = 0.0001;
    cout<<"请输入最大误差e（E(A)<e时停止迭代）:"<<endl;
    cin>>e;//E(A)<e停止迭代
    int maxi = 0,maxj = 1;//记录元素绝对值最大值所在行、列
    double maxij = 0;//记录元素绝对值最大值
    double EA = 1;//用于计算E(A)
    Matrix Q = Matrix::eye(n);//用于存V0*V1*……Vn求特征向量
    int cnt = 0;//记录迭代次数。迭代次数过多停止（原因一般是无法计算复数解，也可能程序不稳定）

    //公式计算
    while(EA>e){
        EA = 0;//先将本次初始EA置零
        
        //确定绝对值最大元素及其位置
        maxij = 0;
        for(int i = 0;i<n;i++){//确定maxi、maxj、maxij
            for(int j = 0; j<n; j ++){
                if(i == j)continue;
                else if(abs(A.getpoint(i,j))>maxij){
                    maxi = i;
                    maxj = j;
                    maxij = abs(A.getpoint(i,j));   
                }
            }
        }

        //计算sin、cos
        double a=0,b=0,c=0,d=0;
        int signa = 1;
        if(A.getpoint(maxi,maxj)!=0){
            a = (A.getpoint(maxi,maxi)-A.getpoint(maxj,maxj))/(2*A.getpoint(maxi,maxj));
            signa = a<0?-1:1;
            b = signa*(sqrt(a*a+1)-abs(a));
            c = 1/(sqrt(1+b*b));
            d = b*c;
        }
        else{//当maxA[i,j] = 0说明除对角元素外都为0
            a = 0;
            b = 0;
            c = 1;
            d = 0;
        }
        //cout<<"i&j:"<<maxi+1<<" "<<maxj+1<<endl;

        //先构造V、VT再根据V*A*VT计算
        Matrix * V = new Matrix(n,n);//用于暂时存储V
        Matrix * VT = new Matrix(n,n);//用于暂时存储VT
        *V = Matrix::eye(n);//构造单位矩阵
        V->changepoint(maxi,maxi,c);//在单位矩阵基础上构造V
        V->changepoint(maxj,maxj,c);
        V->changepoint(maxi,maxj,d);
        V->changepoint(maxj,maxi,-d);
        Q = (*V)*Q;//记录Q用于计算特征值
        *VT = V->T();
        A = (*V)*A*(*VT);//迭代：A = V*A*V.T
        for(int i = 0;i<n;i++){//计算E(A)
            for(int j = 0; j<n; j ++){
                if(abs(A.getpoint(i,j))<MINIUM)A.changepoint(i,j,0);
                if(i!=j){
                       EA = EA + A.getpoint(i,j)*A.getpoint(i,j);
                }
            }
        }

        //迭代次数是否过多时终止计算
        if(cnt==10000000){
            cout<<"超时！迭代终止！"<<endl;
            cout<<"当前矩阵A为"<<endl;
            A.printmatrix();
            abort();
        }
        //A.printmatrix();
        delete V;
        delete VT;
        cnt++;
    }

    //输出特征值
    cout<<"特征值:"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"λ"<<i+1<<" = "<<A.getpoint(i,i)<<endl;
    }

    //分别按行切分矩阵Q存入Qi得到特征向量并输出
    Matrix Qi(n,1);
    cout<<"特征向量:"<<endl;
    for(int i = 0; i < n; i++){
        cout<<"λ"<<i+1<<"对应的特征向量为:"<<endl;
        Qi = Q.spilt(0,i,n-1,i);
        Qi.printmatrix();
    }
}