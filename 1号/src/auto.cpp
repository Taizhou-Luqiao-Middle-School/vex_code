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

void myAuto()
{
    move(100,100);
    wait(300,msec);

    Stop();
}