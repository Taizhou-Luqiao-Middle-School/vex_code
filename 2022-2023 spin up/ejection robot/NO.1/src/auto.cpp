#include "vex.h"
#include "tfiles.h"
using namespace vex;

/*/
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
    MotorFun.spin(fwd,-100,pct);
    shot();
    wait(0.05,sec);
    Stop();
    MotorFun.stop();
    GoForDegree(20,20,MotorLB);
    
}
//*/
using namespace af;

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
    MotorFun.spin(fwd,100,pct);
    wait(60,msec);
    moveintime(30,30,260,1);
    wait(500,msec);
    MotorFun.stop(coast);
    wait(100,msec);
    moveintime(-80,-80,200);
    stop(0);
    wait(600,msec);
    MotorFun.spin(fwd,100,pct);

    moveintime(100,-100,415,1);
    moveintime(100,100,1100);
    moveintime(-80,100,440,1);
    //moveintime(-80,-80,230,1);
    shot();

    MotorFun.stop();
    stop(1);
    Pne1.set(1);
}