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
void myAuto()
{
    move(100,100);
    wait(720,msec);
    move(100,-80);
    wait(610,msec);
    Stop();
    wait(300,msec);
    shot();
    MotorFun.spin(fwd,-100,pct);
    wait(400,msec);
    move(100,-100);
    wait(250,msec); // 运行前必须调试此参数
    move(100,100);
    wait(1175,msec);
    move(20,100);
    wait(448,msec);
    Stop();
    move(5,5);
    wait(770,msec);
    MotorFun.stop();


    Stop();
}