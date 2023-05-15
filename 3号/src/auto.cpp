#include "vex.h"
#include "tfiles.h"
using namespace vex;

/*
void Blue()
{
    Start(-20,-20);
    MotorFun.spin(fwd,100,pct);
    shot();
    wait(0.05,sec);
    Stop();
    MotorFun.stop();
    GoForDegree(20,20,MotorLB);
    
}
void Red()
{
    Start(-20,-20);
    MotorFun.spin(fwd,100,pct);
    shot();
    wait(0.05,sec);
    Stop();
    MotorFun.stop();
    GoForDegree(20,20,MotorLB);
    
}
//*/

// ?

using namespace af;
/*
void Right(){
    go(770);
    turn(90);
    MotorFun.spin(fwd,100,pct);
    go(100,af::go_mode::degree);
    wait(1,sec);
    go(-100,af::go_mode::degree);
    turn(-90);
    go(50);
    turn (-45);
    go(1000);
    turn (-90);
}
void Left (){
    go(880);
    turn(-80);
    shot();
    turn(-90);

}
//*/
const float u = 1.00;
void moveintime(float l,float r,int t,bool st=0){
    move(l,r);
    wait(t*u,msec);
    if (st==1){
        af::stop(1);
        wait(500,msec);
        af::stop(0);
    }
    return ;
}

void myAuto()
{
    moveintime(100,100,720);
    moveintime(100,-80,540,1);
    shot();
    MotorFun.spin(fwd,100,pct);
    wait(400,msec);
    moveintime(100,-100,170);
    moveintime(100,100,1180);
    moveintime(20,100,448,1);
    moveintime(60,60,200);
    MotorFun.stop();
    moveintime(-60,-60,350,1);

    

    Pne1.set(1);
    af::stop(0);
}