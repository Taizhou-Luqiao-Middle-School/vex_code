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
// MotorLF              motor         11              
// MotorLB              motor         15              
// MotorRF              motor         1               
// MotorRB              motor         8               
// MotorShot1           motor         20              
// MotorShot2           motor         4               
// MotorGet1            motor         17              
// MotorGet2            motor         13              
// Controller1          controller                    
// Ine                  inertial      16              
// Pne                  digital_out   A               
// Vis                  vision        19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

/*
IIIIIIIIIIIIII
      I
      I
      I
      I
      I
      I
      I
IIIIIIIIIIIIII
class的定义
*/

class on_off{
  private:bool opening;float cd;float check_time;
  public:
    void button(bool check){if (check && Brain.Timer.time(sec) >= check_time){opening = !opening;check_time = Brain.Timer.time(sec) + cd;}}
    void button(bool check,bool flag){if ( (check && Brain.Timer.time(sec) >= check_time) or flag == true){opening = !opening;}}
    bool op(){return opening;}
    void prepare(){check_time = Brain.Timer.time(msec);cd = 20;}
    void prepare(float cd_in){check_time = Brain.Timer.time(msec);cd = cd_in;}
    on_off(){prepare();}
    on_off(float cd_in){prepare(cd_in);}
    on_off(float cd_in,bool b){prepare(cd_in);opening = b;}
};

class change{
  private:float speed;float min,max;float d;float check_time;float cd;
  public:
    void button(bool check){if (check && Brain.Timer.time(sec)>=check_time ){check_time = Brain.Timer.time(sec) + cd;speed += d;if (speed > max){speed = min;}Controller1.Screen.clearLine();Controller1.Screen.print("shot speed:%d",speed);}}
    void button(bool check1,bool check2){if ( (check1 || check2) && Brain.Timer.time(sec) >= check_time){check_time = Brain.Timer.time(sec) + cd;if (check1 == 1){speed += d;}if (check2 == 1){speed -= d;}if (speed > max){speed = min;}if (speed < min){speed = max;}Controller1.Screen.clearLine();Controller1.Screen.print("shot speed:%d",speed);}}
    int num(){return speed;}

    change(){min=0;max=100;d=20;check_time=0;cd=0.02;speed = (min + max) / 2;}
    change(float t){min=0;max=100;d=20;cd=t;speed = (min + max) / 2;}
    change(float min_,float max_,float d_,float cd_){min = min_;max = max_;d = d_;cd = cd_;speed = (min + max) / 2;}
};

void maxmin (float& a){
  const int speed_max = 80 , speed_min = 0;
  if (fabs(a)>speed_max){
  if (a>0){a=speed_max;}else {a=-speed_max;}}
  if (fabs(a)<speed_min){if (a>0){a=speed_min;}else {a=-speed_min;}}
}
void maxmin (float& a,int speed_max,int speed_min){
  if (fabs(a)>speed_max){if (a>0){a=speed_max;}else {a=-speed_max;}}
  if (fabs(a)<speed_min){if (a>0){a=0;}else {a=0;}}
}

class pid{
  private:float lasttime;int goal;float p;float pk;float i;float ik;float imax;float lastd;float dk;float jump;float jumptime;float outtime;
  public:
  void pre(){lasttime = Brain.Timer.time(sec);i=0;lastd = 0;jumptime = 0.5;outtime = Brain.Timer.time(sec) + 999;}
  void pre(int g){pre();goal = g;jump = fabs(g*0.1);}
  void pre(int g,int j){pre(g);jump = j;}
  void pre(int g,float pkin,float ikin,float dkin){pre(g);pk = pkin;ik = ikin;dk = dkin;}
  void pre(int g,float pkin,float ikin,float dkin,float imaxin){pre(g,pkin,ikin,dkin);imax = imaxin;}
  pid(){pre(50,0.7,0.3,0.3,30);}
  pid(int g){pre(g,0.7,0.3,0.3,30);}
  pid(int g,int j){pre(g,j);}
  pid(int g,int j,float pkin,float ikin,float dkin){pre(g,pkin,ikin,dkin);jump = j;}

  bool check(int input,float& move){ // 使用样例 pid.pre(500);
                                     //         while(pid.check(MotorLF.position(),move)) walk(move,move);
    float delta = goal - input;
    if (Brain.Timer.time(sec) >= outtime) {return 0;}
    if ( fabs(delta) > jump){outtime = Brain.Timer.time(sec) + jumptime;}
    float timenow = Brain.Timer.time(sec);float delattime = timenow - lasttime;lasttime = timenow;delattime /= 1;p = delta * pk;i = i + delta * ik *delattime;maxmin(i,imax,0);int d = ( delta - lastd ) * dk / delattime;lastd = delta;move = p + i + d;return 1;}
};
/*
IIIIIIIIIIIIIIII
     I    I
     I    I
     I    I
     I    I
     I    I
     I    I
IIIIIIIIIIIIIIII
底盘
*/
void move(float r,float l){
  MotorLF.spin(forward,l,pct);
  MotorLB.spin(forward,l,pct);
  MotorRF.spin(forward,r,pct);
  MotorRB.spin(forward,r,pct);
}

void Stop(){
  MotorLF.stop();
  MotorLB.stop();
  MotorRF.stop();
  MotorRB.stop();
}
void Stop(bool flag){
  if (flag == true ){
    MotorLF.stop(hold);
    MotorLB.stop(hold);
    MotorRF.stop(hold);
    MotorRB.stop(hold);
    return;
  }
  else {
    MotorLF.stop();
    MotorLB.stop();
    MotorRF.stop();
    MotorRB.stop();
    return;
  }
}

void reset(){
  MotorLF.resetPosition();
  MotorLB.resetPosition();
  MotorRF.resetPosition();
  MotorRB.resetPosition();
}


void walk_con(){
  float a1 = Controller1.Axis1.position();
  float a2 = Controller1.Axis2.position();
  float a3 = Controller1.Axis3.position();
  float a4 = Controller1.Axis4.position();
  maxmin(a1);
  maxmin(a2);
  maxmin(a3);
  maxmin(a4);

  move(a2,a3);
}

/*
IIIIIIIIIIIIIIIIIIIII
      I   I   I
      I   I   I
      I   I   I
      I   I   I
      I   I   I
      I   I   I
      I   I   I
IIIIIIIIIIIIIIIIIIIIII
功能项
*/

/*
R2 ---  shot
R1 ---  pne
L2 ---  get _ down
L1 ---  get _ up
Y  ---  walk mode
^  ---  shot speed up
\/ ---  shot speed down

change(float min_,float max_,float d_,int cd_)
*/

on_off pne(600,0) , shot(200,0) ;
change shotspeed(70,100,10,50) ;

void check(){
  pne.button(Controller1.ButtonR1.pressing());
  shot.button(Controller1.ButtonR2.pressing());

  shotspeed.button(Controller1.ButtonUp.pressing(),Controller1.ButtonDown.pressing());
}

void work(){
  if (pne.op() == 1){
    pne.button(true,true);
    Pne.set(true);
    wait(500,msec);
    pne.button(true,true);
  }
  if (shot.op() == 1){
    MotorShot1.spin(forward,shotspeed.num(),pct);
    MotorShot2.spin(forward,shotspeed.num(),pct);
  }
  if (shot.op() == 0){
    MotorShot1.stop();
    MotorShot2.stop();
  }
  int getspeed = 0;
  if (Controller1.ButtonL1.pressing()){
    getspeed += 100;
  }
  if (Controller1.ButtonL2.pressing()){
    getspeed -= 100;
  }
  MotorGet1.spin(forward,getspeed,pct);
  MotorGet2.spin(forward,getspeed,pct);
}

/*
IIIIIIIIII           I
    I     I         I
    I      I       I
    I       I     I
    I        I   I
    I         I I
IIIIIIIII      I
自动 auton

void pre(int g,float pkin,float ikin,float dkin,float imaxin)
bool check(int input,float& move)
pid(int g,int j,float pkin,float ikin,float dkin)
*/

void gofordegree(int goal){
  pid go ;
  go.pre(goal,0.7,0.3,0.3,goal*0.1);
  float movement;
  MotorLB.resetPosition();
  while ( go.check(MotorLB.position(degrees) , movement) ) move(movement,movement);
}

void turnfordegree(int goal){
  pid go ;
  go.pre(goal,0.7,0.3,0.3,goal*0.1);
  float movement = 50;
  Ine.calibrate();
  while ( Ine.heading(degrees) , movement)  move(movement,-movement);
}

/*
    I           I
     I         I
      I       I
       I     I
        I   I
         I I
          I
主函数区 pre  auton  usercontrol
*/


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  reset();
  MotorGet1.resetPosition();
  MotorGet2.resetPosition();
  MotorShot1.resetPosition();
  MotorShot2.resetPosition();

  Ine.calibrate();

  Pne.set(0);

  Brain.Timer.reset();

  Controller1.Screen.print("Ready!");
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    check();
    walk_con();
    work();

    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
