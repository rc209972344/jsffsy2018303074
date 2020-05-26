#include <iostream>
#include <cmath>
//#include"Matrix.cpp"
#include"picture.cpp"
using namespace std;
void question1(){
    int functiontype = 1;
    cout<<"请输入数字选择拟合函数："<<endl;
    cout<<"输入1选择一次函数(默认)"<<endl;
    cout<<"输入2选择二次线函数"<<endl;
    cout<<"输入3选择三次函数"<<endl;
    cout<<"输入4选择双曲线函数"<<endl;
    cout<<"输入5选择指数函数"<<endl;
    cin>>functiontype;
    switch(functiontype){
        case 1:{

            //输入数据
            cout<<"请输入数据点个数"<<endl;
            int sjds = 1;
            cin>>sjds;//数据点个数
            double AA[sjds*2];//由于矩阵初始化需要用一维数组存矩阵A
            for(int i = 0; i < sjds*2; i+=2){
                AA[i] = 1;
            }
            cout<<"请按顺序输入各个点自变量值"<<endl;
            for(int i = 1; i < sjds*2; i+=2){
                cin>>AA[i];
            }
            Matrix A(sjds,2);
            A = AA;//用数组AA初始化矩阵A

            double bb[sjds];//用一维数组存b
            cout<<"请按顺序输入各个点因变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                cin>>bb[i];
            }
            Matrix b(sjds,1);
            b = bb;//用数组bb初始化矩阵b

            //公式计算
            //由A.T * A * x = A.T * b 求系数矩阵x
            //x = (A.T * A).inv * A.T * b
            //记C = A.T * A ，D = C.inv
            //记E = A.T * b
            //则x = D * E
            Matrix C = A.T() * A;
            Matrix D = C.inv();
            Matrix E = A.T() * b;
            Matrix x = D * E;
            //x.printmatrix();

            //输出结果
            //x：[a0,a1]
            //y = a0 + a1x
            double a0 = x.getpoint(0,0);
            double a1 = x.getpoint(1,0);
            cout<<"拟合结果："<<"y = "<<a0<<" + "<<a1<<"x"<<endl;

            //计算差值并输出
            double Y[sjds];//数组Y用于存储估计值
            double dmax = 0;//最大差值
            double djfc = 0;//均方差
            for(int i = 0; i<sjds; i++){
                Y[i] = a0 + a1*AA[i*2+1];//计算估计值存入Y
                if(dmax<=abs(Y[i]-bb[i]))dmax = abs(Y[i]-bb[i]);//计算最大差值
                djfc = djfc + (Y[i]-bb[i])*(Y[i]-bb[i]);
            }
            cout<<"最大偏差为："<<dmax<<endl;
            cout<<"均方差为："<<sqrt(djfc)<<endl;

            //绘制图像
            double x0 = 0,y0 = 0, stepx = 0,stepy = 0;
            cout<<"请输入作图起始点x、y坐标、x轴步长、y轴步长"<<endl;
            cout<<"默认其中作图范围为x-[x0,x0+10stepx],y-[y0,y0+10stepy],可以在picture.cpp中修改"<<endl;
            cin>>x0>>y0>>stepx>>stepy;
            function1fig(a0,a1,x0,y0,stepx,stepy);
            cout<<"结果已输出至当前路径下picture1.txt文件中"<<endl;
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
            double x0 = 0,y0 = 0, stepx = 0,stepy = 0;
            cout<<"请输入作图起始点x、y坐标、x轴步长、y轴步长"<<endl;
            cout<<"默认其中作图范围为x-[x0,x0+10stepx],y-[y0,y0+10stepy],可以在picture.cpp中修改"<<endl;
            cin>>x0>>y0>>stepx>>stepy;
            function2fig(a0,a1,a2,x0,y0,stepx,stepy);
            cout<<"结果已输出至当前路径下picture2.txt文件中"<<endl;
            break;
        };
        case 3:{
            cout<<"请输入数据点个数"<<endl;
            int sjds = 1;
            cin>>sjds;//数据点个数
            double AA[sjds*4];//由于矩阵初始化需要用一维数组存矩阵A
            for(int i = 0; i < sjds*4; i+=4){
                AA[i] = 1;
            }
            cout<<"请按顺序输入各个点自变量值"<<endl;
            for(int i = 1; i < sjds*4; i+=4){
                cin>>AA[i];
            }
            for(int i = 2; i < sjds*4; i+=4){
                AA[i] = AA[i-2]*AA[i-2];
            }
            for(int i = 3; i < sjds*4; i+=4){
                AA[i] = AA[i-3]*AA[i-3]*AA[i-3];
            }
            Matrix A(sjds,4);
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
            //y = a0 + a1x + a2x^2 +a3x^3
            double a0 = x.getpoint(0,0);
            double a1 = x.getpoint(1,0);
            double a2 = x.getpoint(2,0);
            double a3 = x.getpoint(3,0);
            cout<<"拟合结果："<<"y = "<<a0<<" + "<<a1<<"x + "<<a2<<"x^2 +"<<a3<<"x^3"<<endl;


            double Y[sjds];//数组Y用于存储估计值
            double dmax = 0;//最大差值
            double djfc = 0;//均方差
            for(int i = 0; i<sjds; i++){
                Y[i] = a0 + a1*AA[i*4+1] + a2*AA[i*4+1]*AA[i*4+1] + a3*AA[i*4+1]*AA[i*4+1]*AA[i*4+1];//计算估计值存入Y
                if(dmax<=abs(Y[i]-bb[i]))dmax = abs(Y[i]-bb[i]);//计算最大差值
                djfc = djfc + (Y[i]-bb[i])*(Y[i]-bb[i]);
            }
            cout<<"最大偏差为："<<dmax<<endl;
            cout<<"均方差为："<<sqrt(djfc)<<endl;
            double x0 = 0,y0 = 0, stepx = 0,stepy = 0;
            cout<<"请输入作图起始点x、y坐标、x轴步长、y轴步长"<<endl;
            cout<<"默认其中作图范围为x-[x0,x0+10stepx],y-[y0,y0+10stepy],可以在picture.cpp中修改"<<endl;
            cin>>x0>>y0>>stepx>>stepy;
            function3fig(a0,a1,a2,a3,x0,y0,stepx,stepy);
            cout<<"结果已输出至当前路径下picture3.txt文件中"<<endl;
            break;
        };
        case 4:{
            cout<<"请输入数据点个数"<<endl;
            int sjds = 1;
            cin>>sjds;//数据点个数
            double AA[sjds*2];//由于矩阵初始化需要用一维数组存矩阵A（计算用）
            double AAA[sjds];//用于存原自变量
            for(int i = 0; i < sjds*2; i+=2){
                AA[i] = 1;
            }
            cout<<"请按顺序输入各个点自变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                cin>>AAA[i];
            }
            for(int i = 0; i < sjds; i++){
                AA[i*2+1] = 1.0/AAA[i];
            }
            Matrix A(sjds,2);
            A = AA;//用数组AA初始化矩阵A

            double bb[sjds];//用一维数组存b(计算用)
            double bbb[sjds];//存原因变量
            cout<<"请按顺序输入各个点因变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                cin>>bbb[i];
            }
            for(int i = 0; i < sjds; i++){
                bb[i] = 1.0/bbb[i];
            }
            Matrix b(sjds,1);
            b = bb;//用数组bb初始化矩阵b


            Matrix C = A.T() * A;
            Matrix D = C.inv();
            Matrix E = A.T() * b;
            Matrix x = D * E;


            //x：[a0,a1,a2]
            //1/y = a0 + a1*1/x = 1/(a0x + a1)
            double a0 = x.getpoint(0,0);
            double a1 = x.getpoint(1,0);
            cout<<"拟合结果："<<"y = x/("<<a0<<"x + "<<a1<<")"<<endl;


            double Y[sjds];//数组Y用于存储估计值
            double dmax = 0;//最大差值
            double djfc = 0;//均方差
            for(int i = 0; i<sjds; i++){
                Y[i] = AAA[i]/(a0*AAA[i] + a1);//计算估计值存入Y
                if(dmax<=abs(Y[i]-bbb[i]))dmax = abs(Y[i]-bbb[i]);//计算最大差值
                djfc = djfc + (Y[i]-bbb[i])*(Y[i]-bbb[i]);
            }
            cout<<"最大偏差为："<<dmax<<endl;
            cout<<"均方差为："<<sqrt(djfc)<<endl;
            double x0 = 0,y0 = 0, stepx = 0,stepy = 0;
            cout<<"请输入作图起始点x、y坐标、x轴步长、y轴步长"<<endl;
            cout<<"默认其中作图范围为x-[x0,x0+50stepx],y-[y0,y0+50stepy],可以在picture.cpp中修改"<<endl;
            cin>>x0>>y0>>stepx>>stepy;
            function4fig(a0,a1,x0,y0,stepx,stepy);
            cout<<"结果已输出至当前路径下picture4.txt文件中"<<endl;
            break;
        };
        case 5:{
            cout<<"请输入数据点个数"<<endl;
            int sjds = 1;
            cin>>sjds;//数据点个数
            double AA[sjds*2];//由于矩阵初始化需要用一维数组存矩阵A（计算用）
            double AAA[sjds];//用于存原自变量
            for(int i = 0; i < sjds*2; i+=2){
                AA[i] = 1;
            }
            cout<<"请按顺序输入各个点自变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                cin>>AAA[i];
            }
            for(int i = 0; i < sjds; i++){
                AA[i*2+1] = 1/AAA[i];
            }
            Matrix A(sjds,2);
            A = AA;//用数组AA初始化矩阵A

            double bb[sjds];//用一维数组存b(计算用)
            double bbb[sjds];//存原因变量
            cout<<"请按顺序输入各个点因变量值"<<endl;
            for(int i = 0; i < sjds; i++){
                cin>>bbb[i];
            }
            for(int i = 0; i < sjds; i++){
                bb[i] = log(bbb[i]);
            }
            Matrix b(sjds,1);
            b = bb;//用数组bb初始化矩阵b


            Matrix C = A.T() * A;
            Matrix D = C.inv();
            Matrix E = A.T() * b;
            Matrix x = D * E;


            //x：[a0,a1]
            //lny = a0 + a1/x,y = exp(a0)exp(a1/x)
            double a0 = x.getpoint(0,0);
            double a1 = x.getpoint(1,0);
            cout<<"拟合结果："<<"y = "<<exp(a0)<<"e^("<<a1<<"/x)"<<endl;


            double Y[sjds];//数组Y用于存储估计值
            double dmax = 0;//最大差值
            double djfc = 0;//均方差
            for(int i = 0; i<sjds; i++){
                Y[i] = exp(a0+a1/AAA[i]);//计算估计值存入Y
                if(dmax<=abs(Y[i]-bbb[i]))dmax = abs(Y[i]-bbb[i]);//计算最大差值
                djfc = djfc + (Y[i]-bbb[i])*(Y[i]-bbb[i]);
            }
            cout<<"最大偏差为："<<dmax<<endl;
            cout<<"均方差为："<<sqrt(djfc)<<endl;
            a0 = exp(a0);
            double x0 = 0,y0 = 0, stepx = 0,stepy = 0;
            cout<<"请输入作图起始点x、y坐标、x轴步长、y轴步长"<<endl;
            cout<<"默认其中作图范围为x-[x0,x0+50stepx],y-[y0,y0+50stepy],可以在picture.cpp中修改"<<endl;
            cin>>x0>>y0>>stepx>>stepy;
            function5fig(a0,a1,x0,y0,stepx,stepy);
            cout<<"结果已输出至当前路径下picture5.txt文件中"<<endl;
            break;
        };
        default:{
            cout<<"输入的数字无效"<<endl;
            break;
        };
    } 
 }