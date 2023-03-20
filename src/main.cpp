/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorLF              motor         10              
// MotorLM              motor         9               
// MotorLB              motor         8               
// MotorRF              motor         5               
// MotorRM              motor         6               
// MotorRB              motor         7               
// Rotation             rotation      11              
// Inertial4            inertial      21              
// MotorShot            motor         2               
// MotorFun             motor         12              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "debug.h"

using namespace vex;

competition Competition;
float degr = 55; 
void pre_auton(void) {
  Controller1.Screen.clearScreen();
  Rotation.resetPosition();
  MotorShot.spin(fwd,100,pct);
  waitUntil(fabs( float (Rotation.position(deg))) >= degr);
  MotorShot.stop(hold);
  Inertial4.calibrate();
  waitUntil(!Inertial4.isCalibrating());
  Controller1.Screen.print("Ready!");
  vexcodeInit();
}


void autonomous(void) {
  myAuto();
}

// 遥感控制前进左右
void DiPan()
{
  int a3 = Controller1.Axis3.position(percent)*0.8;
  int a1 = Controller1.Axis1.position(percent)*0.6;
  Start(a3+a1,a3-a1);
}


double now;

int getinf()
{
  while(1)
    now = Rotation.position(deg);
}

// 发射disc
void Shot()
{
  if(Controller1.ButtonR1.pressing())
  {
    task t_get = task(getinf);
    t_get.resume();
    MotorShot.spin(fwd,100,pct);
    waitUntil(fabs( float (now) )<= degr);
    MotorShot.stop(hold);
    MotorShot.spin(fwd,100,pct);
    waitUntil(fabs( float (now) )>=degr);
    MotorShot.stop();
    // waitUntil(fabs( float (now)>=100);
    // MotorShot.spin(fwd,100,pct);
    // waitUntil(fabs( float (now) == degr-5);
    // MotorShot.stop(hold);
  }
}
int cnt1 = 0,cnt2 = 0;
void get1()
{
  if(cnt1%2 == 1)
      MotorFun.spin(fwd,100,pct);
  else MotorFun.stop(hold);
  cnt1++;
}
void get2()
{
  if(cnt2%2 == 1)
      MotorFun.spin(fwd,-100,pct);
  else MotorFun.stop(hold);
  cnt2++;
}
// 手动程序
void get()
{
  
  Controller1.ButtonL1.pressed(get1);
  Controller1.ButtonL2.pressed(get2);
}
//*
void p()
{
  if(Controller1.ButtonUp.pressing())
  {
    //Pne1.set(true);
    //Pne2.set(true);
  }
  else if(Controller1.ButtonDown.pressing())
  {
    //Pne1.set(false);
    //Pne2.set(false);
  }
}
//*/

const bool debuging = 1;
void usercontrol(void) {
  Brain.Timer.reset();
  while (1) {
    if ( Brain.Timer.time(sec) >= 102 ) {
      Pne1.set(1);
    }
    
    //if ( Controller1.ButtonY.pressing() ) { Pne2.set(1);}
    //if ( Controller1.ButtonX.pressing() ) { Pne2.set(0);}

    if (debuging == 1) debug::OutPut();
    DiPan();
    Shot();
    get();
    p();
    if (debuging == 1)debug::reput();
    if (debuging == 0 ) {
      Controller1.Screen.clearLine();
      Controller1.Screen.print("Shot temp:%.2f ℃",MotorShot.temperature(celsius));
    }
    wait(20, msec);
  }

}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    Brain.Screen.printAt(1,30,"%.2f",Rotation.position(deg));
    wait(100, msec);
    if(Controller1.ButtonLeft.pressing()) myAuto();
  }
}
