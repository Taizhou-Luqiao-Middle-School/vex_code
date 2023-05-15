//#include "vex.h"
//#include "tfiles.h"
#include "debug.h"
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
    go(700);
    MotorFun.spin(fwd,-80,pct);
    turn(-90);
    go(1000 , af::go_mode::ms , 60);
    wait(1,sec);
    go(-100 );
    turn(-90);
    go(100);
    turn (-45);
    go(1200);
    turn (90);
    //go(-80 , af::go_mode::degree);
    shot();
    MotorFun.stop();
}
//*/
/*
void Left ();
void Left1 (){
    go(1000);
    Brain.Timer.reset();
    move (100 , -100);
    waitUntil( Brain.Timer.time(msec) >= 430);
    af::stop();
    wait (0.5,sec);
    af::stop(true);
}
void Left2(){
    shot();
    Pne2.set(1);
}
void Left(){
    Left1();
    Left2();
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

void auto_1(){
    moveintime(100,100,720);
    moveintime(100,-80,585,1);
    shot();
    MotorFun.spin(fwd,100,pct);
    wait(400,msec);
    moveintime(100,-100,235);
    moveintime(100,100,1180);
    moveintime(20,100,448,1);
    moveintime(60,60,200);
    MotorFun.stop();
    moveintime(-60,-60,350,1);

    

    Pne1.set(1);
    af::stop(0);
}

void auto_2(){
    moveintime(-10,-100,580);
    moveintime(-50,-50,300,1);
    shot();

    MotorFun.spin(fwd,100,pct);
    moveintime(70,-70,275,1);
    moveintime(70,70,250);
    moveintime(40,90,270);
    moveintime(10,10,200);

    moveintime(-50,-50,100);
    moveintime(-100,100,520,1);
    moveintime(100,100,1000);
    moveintime(100,-100,470,1);
    wait(800,msec);
    shot();

    af::stop();
    MotorFun.stop();
    Pne1.set(0);
}

void myAuto()
{
    auto_1();
}