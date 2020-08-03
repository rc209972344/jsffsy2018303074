#include <iostream>
#include"Matrix.cpp"
#include"question1.h"
#include"question2.h"
#include"question3.h"
#include"question4.h"
#include"question5.h"
using namespace std;

int main()
{
    char question = 'a';
    while(question!='q'){
        cout<<"输入a进入实验报告第一题程序"<<endl;
        cout<<"输入b进入实验报告第二题程序"<<endl;
        cout<<"输入c进入实验报告第三题程序"<<endl;
        cout<<"输入d进入实验报告第四题程序"<<endl;
        cout<<"输入e进入实验报告第五题程序"<<endl;
        cout<<"输入q退出"<<endl;
        cin>>question;
        switch(question){
            case 'a':{
                question1();
                break;
            }
            case 'b':{
                question2();
                break;
            }
            case 'c':{
                question3();
                break;
            }
            case 'd':{
                question4();
                break;
            }
            case 'e':{
                question5();
                break;
            }
            case 'q':{
                break;
            }
            default:{
                cout<<"输入的字母无效"<<endl;
                break;
            };
        }
    }
    return 0;
}
