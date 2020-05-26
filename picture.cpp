#include <iostream>
#include <cmath>
#include<fstream>
using namespace std;	
void function1fig(double a0,double a1,double left,double bottom,double stepx,double stepy){
    fstream f1f;
    f1f.open("picture1.txt",ios::out);
    for(double y = bottom+10*stepy;y>=bottom;y-=stepy){
        if(abs(y-0)<stepy){for(double x = left;x<=left+10*stepx;x+=stepx){f1f<<"-";}}
        else{
            for(double x = left;x<=left+10*stepx;x+=stepx){
                if(abs(x-0) < stepx)f1f<<"|";
                else{
                    if(abs(y - a0 - a1*x)<stepy*0.5){
                        f1f<<"·";
                    }
                    else f1f<<" ";
                }
            }
        }
        f1f<<endl;
    }
    f1f.close();
}
void function2fig(double a0,double a1,double a2,double left,double bottom,double stepx,double stepy){
    fstream f2f;
    f2f.open("picture2.txt",ios::out);
    for(double y = bottom+10*stepy;y>=bottom;y-=stepy){
        if(abs(y-0)<stepy){for(double x = left;x<=left+10*stepx;x+=stepx){f2f<<"-";}}
        else{
            for(double x = left;x<=left+10*stepx;x+=stepx){
                if(abs(x-0) < stepx)f2f<<"|";
                else{
                    if(abs(y - a0 - a1*x - a2*x*x )<stepy*0.5){
                        f2f<<"·";
                    }
                    else f2f<<" ";
                }
            }
        }
        f2f<<endl;
    }
    f2f.close();   
}
void function3fig(double a0,double a1,double a2,double a3,double left,double bottom,double stepx,double stepy){
    fstream f3f;
    f3f.open("picture3.txt",ios::out);
    for(double y = bottom+10*stepy;y>=bottom;y-=stepy){
        if(abs(y-0)<stepy){for(double x = left;x<=left+10*stepx;x+=stepx){f3f<<"-";}}
        else{
            for(double x = left;x<=left+10*stepx;x+=stepx){
                if(abs(x-0) < stepx)f3f<<"|";
                else{
                    if(abs(y - a0 - a1*x - a2*x*x - a3*x*x*x )<stepy*0.5){
                        f3f<<"·";
                    }
                    else f3f<<" ";
                }
            }
        }
        f3f<<endl;
    }
    f3f.close(); 
}
void function4fig(double a0,double a1,double left,double bottom,double stepx,double stepy){
    fstream f4f;
    f4f.open("picture4.txt",ios::out);
    for(double y = bottom+50*stepy;y>=bottom;y-=stepy){
        if(abs(y-0)<stepy){for(double x = left;x<=left+50*stepx;x+=stepx){f4f<<"-";}}
        else{
            for(double x = left;x<=left+50*stepx;x+=stepx){
                if(abs(x-0) < stepx)f4f<<"|";
                else{
                    if(abs(y - (x/(a0*x+a1)))<stepy/2){
                        f4f<<".";
                    }
                    else f4f<<" ";
                }
            }
        }
        f4f<<endl;
    }
    f4f.close();
}
void function5fig(double a0,double a1,double left,double bottom,double stepx,double stepy){
    fstream f5f;
    f5f.open("picture5.txt",ios::out);
    for(double y = bottom+50*stepy;y>=bottom;y-=stepy){
        if(abs(y-0)<stepy){for(double x = left;x<=left+50*stepx;x+=stepx){f5f<<"-";}}
        else{
            for(double x = left;x<=left+50*stepx;x+=stepx){
                if(abs(x-0) < stepx)f5f<<"|";
                else{
                    if(abs(y - (a0*exp(a1/x)))<stepy/2){
                        f5f<<".";
                    }
                    else f5f<<" ";
                }
            }
        }
        f5f<<endl;
    }
    f5f.close();
}