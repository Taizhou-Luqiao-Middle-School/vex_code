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
#include "tfiles.h"
using namespace vex;

competition Competition;
float degr = 55; 
void pre_auton(void) {
  af::reset();
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

void DiPan()
{
  int a1 = Controller1.Axis3.position(percent)*-0.8;
  int a3 = Controller1.Axis1.position(percent)*-0.6;
  Start(a3+a1,a3-a1);
}


double now;

int getinf()
{
  while(1)
    now = Rotation.position(deg);
}

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
void get()
{
  
  Controller1.ButtonL1.pressed(get1);
  Controller1.ButtonL2.pressed(get2);
}
//*
void p1(){
  Pne1.set( !Pne1.value() );
  Pne2.set( !Pne2.value() );
}

void p()
{
  Controller1.ButtonDown.pressed(p1);
}

void spread(){
  Pne2.set(1);
}

void usercontrol(void) {
  while (1) {
    DiPan();
    Shot();
    get();
    p();
    Controller1.Screen.clearLine();
    //Controller1.Screen.print("Shot temp:%.2f ℃",MotorShot.temperature(celsius));
    wait(20, msec);
    Controller1.ButtonUp.pressed(spread);
  }
}

int t_printing(){
    while(1){
        Controller1.Screen.newLine();
        Controller1.Screen.print("p:%.1f t:%.1f        ",MotorLF.position(degrees),Brain.Timer.time(sec));
    }
    return 1;
}
task printing= task(t_printing);

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  printing.resume();
  while (true) {
    Brain.Screen.printAt(1,30,"%.2f",Rotation.position(deg));
    Controller1.Screen.newLine();
    Controller1.Screen.print("p:%.1f t:%.1f",MotorLF.position(degrees),Brain.Timer.time(msec));
    wait(100, msec);
    if(Controller1.ButtonLeft.pressing()) myAuto();
  }
  printing.suspend();
}
