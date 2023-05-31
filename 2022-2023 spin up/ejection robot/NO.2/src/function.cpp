#include "vex.h"
using namespace vex;

void Start(float vl,float vr)
{
  MotorLF.spin(forward,vl,percent);
  MotorLM.spin(forward,vl,percent);
  MotorLB.spin(forward,vl,percent);
  MotorRF.spin(forward,vr,percent);
  MotorRM.spin(forward,vr,percent);
  MotorRB.spin(forward,vr,percent);
}

void Stop()
{
  MotorLF.stop(hold);
  MotorLM.stop(hold);
  MotorLB.stop(hold);
  MotorRF.stop(hold);
  MotorRM.stop(hold);
  MotorRB.stop(hold);
  wait(0.2,sec);
  MotorLF.stop(coast);
  MotorLM.stop(coast);
  MotorLB.stop(coast);
  MotorRF.stop(coast);
  MotorRM.stop(coast);
  MotorRB.stop(coast);
}

void GoForDegree(float speed,float degree,motor Motor4Encoder)
{
  Motor4Encoder.resetPosition();
  while(fabs( float (degree))>fabs( float (Motor4Encoder.position(degrees))))
    Start(speed, speed);
  Stop();
}

double kp=1.0,ki=0.0000000000,kd=0.0;
double error=0.0,i=0.0,d=0.0,lastError=0.0;
double targetDegree;
double delta;

int turnCalc()
{
  while(1)
  {
    error =targetDegree- Inertial4.rotation();
    i = i + error;
    d = error - lastError;
  }
}

void Turn(inertial InertialDefault, double degree, double seconds,double speedDefault)
{
  Brain.Timer.reset();
  targetDegree = degree;
  double degreeBegin = InertialDefault.rotation();
  delta = targetDegree - degreeBegin;
  kp = 0.9+(delta-90)/90.0*0.9;
  kd = 0.5 + delta/10.0;
  error=delta,i=0.0,d=0.0,lastError=0.0;
  double k;
  double speed;  
  task taskPidCalc=task(turnCalc);
  taskPidCalc.resume();
  while(Brain.Timer.time(sec)< seconds)
  {
    k = (kp*error + ki*i + kd*d)/delta;
    speed= speedDefault*k;
    Start(speed, -speed);
    lastError = error;
  }
  taskPidCalc.suspend();
  Stop();
}

double now_;

int get_()
{
  while(1)
    now_ = Rotation.position(deg);
}

void shot()
{
  task t_get = task(get_);
  t_get.resume();
  MotorShot.spin(fwd,100,pct);
  waitUntil(fabs( float (now_) ) <= degr);
  MotorShot.stop(hold);
  MotorShot.spin(fwd,100,pct);
  waitUntil(fabs( float (now_) ) >=degr);
  MotorShot.stop();
  // waitUntil(fabs( float (now)>=100);
  // MotorShot.spin(fwd,100,pct);
  // waitUntil(fabs( float (now) == degr-5);
  // MotorShot.stop(hold);
}