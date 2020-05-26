#include <iostream>
#include <cmath>
//#include"Matrix.cpp"
using namespace std;
void question5(){
    int functiontype = 1;
    cout<<"请输入数字选择拟合函数："<<endl;
    cout<<"输入1选择二次线函数"<<endl;
    cout<<"输入2选择正态函数"<<endl;
    cin>>functiontype;
    switch(functiontype){
        case 1:{
            cout<<"请输入数据点个数"<<endl;
            int sjds = 1;
            cin>>sjds;//数据点个数
            double AA[sjds*3];//由于矩阵初始化需要用一维数组存矩阵A
            for(int i = 0; i < sjds*3; i+=3){
                AA[i] = 1;
            }
            cout<<"请按顺序输入各个点自变量值"<<endl;
            for(int i = 1; i < sjds*3; i+=3){
                cin>>AA[i];
            }
            for(int i = 2; i < sjds*3; i+=3){
                AA[i] = AA[i-1]*AA[i-1];
            }
            Matrix A(sjds,3);
            A = AA;//用数组AA初始化矩阵A

            double bb[sjds];//用一维数组存b
            cout<<"请按顺序输入各个点因变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                cin>>bb[i];
            }
            Matrix b(sjds,1);
            b = bb;//用数组bb初始化矩阵b

           
            Matrix C = A.T() * A;
            Matrix D = C.inv();
            Matrix E = A.T() * b;
            Matrix x = D * E;


            //x：[a0,a1,a2]
            //y = a0 + a1x + a2x^2
            double a0 = x.getpoint(0,0);
            double a1 = x.getpoint(1,0);
            double a2 = x.getpoint(2,0);
            cout<<"拟合结果："<<"y = "<<a0<<" + "<<a1<<"x + "<<a2<<"x^2"<<endl;


            double Y[sjds];//数组Y用于存储估计值
            double dmax = 0;//最大差值
            double djfc = 0;//均方差
            for(int i = 0; i<sjds; i++){
                Y[i] = a0 + a1*AA[i*3+1]+a2*AA[i*3+1]*AA[i*3+1];//计算估计值存入Y
                if(dmax<=abs(Y[i]-bb[i]))dmax = abs(Y[i]-bb[i]);//计算最大差值
                djfc = djfc + (Y[i]-bb[i])*(Y[i]-bb[i]);
            }
            cout<<"最大偏差为："<<dmax<<endl;
            cout<<"均方差为："<<sqrt(djfc)<<endl;
            break;
        };
        case 2:{
            cout<<"请输入数据点个数"<<endl;
            int sjds = 1;
            cin>>sjds;//数据点个数
            double AA[sjds*3];//由于矩阵初始化需要用一维数组存矩阵A
            for(int i = 0; i < sjds*3; i+=3){
                AA[i] = 1;
            }
            cout<<"请按顺序输入各个点自变量值"<<endl;
            for(int i = 1; i < sjds*3; i+=3){
                cin>>AA[i];
            }
            for(int i = 2; i < sjds*3; i+=3){
                AA[i] = AA[i-1]*AA[i-1];
            }
            Matrix A(sjds,3);
            A = AA;//用数组AA初始化矩阵A

            double bb[sjds];//用一维数组存b
            cout<<"请按顺序输入各个点因变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                double b;
                cin>>b;
                bb[i] = log(b);
            }
            Matrix b(sjds,1);
            b = bb;//用数组bb初始化矩阵b

           
            Matrix C = A.T() * A;
            Matrix D = C.inv();
            Matrix E = A.T() * b;
            Matrix x = D * E;


            //x：[a0,a1,a2]
            //y = a0 + a1x + a2x^2
            double a0 = x.getpoint(0,0);
            double a1 = x.getpoint(1,0);
            double a2 = x.getpoint(2,0);
            cout<<"拟合结果："<<"lny = "<<a0<<" + "<<a1<<"x + "<<a2<<"x^2"<<endl;
            cout<<"拟合结果："<<"y = e^("<<a0<<" + "<<a1<<"x + "<<a2<<"x^2)"<<endl;


            double Y[sjds];//数组Y用于存储估计值
            double dmax = 0;//最大差值
            double djfc = 0;//均方差
            for(int i = 0; i<sjds; i++){
                Y[i] = a0 + a1*AA[i*3+1]+a2*AA[i*3+1]*AA[i*3+1];//计算估计值存入Y
                if(dmax<=abs(Y[i]-bb[i]))dmax = abs(Y[i]-bb[i]);//计算最大差值
                djfc = djfc + (Y[i]-bb[i])*(Y[i]-bb[i]);
            }
            cout<<"最大偏差为："<<dmax<<endl;
            cout<<"均方差为："<<sqrt(djfc)<<endl;
            break;
        };
        default:{
            cout<<"输入的数字无效"<<endl;
            break;
        };
    } 
 }