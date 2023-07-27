#include "autofunctions.h"
using namespace ext;
// walk for degree 
  void ext::go(int goal , go_mode mode , int speed){
    if (goal == 0 or speed == 0 ){
      return ;
    }
    if (mode == ext::go_mode::pid){

      pids go ;
      go.pre(goal,10,0.5,0.02,0.7,3);
      float movement;
      reset();
      while ( go.check(MotorLB.position(degrees)) ) {
        movement = go.moving() * speed / 100;
        move(movement,movement);
      }
      stop();
      wait (0.8,sec);
      return ;
    }
    if (goal*speed <0){
      speed = -speed;
    }
    if (goal < 0){
      if (speed > 0){
        speed = -speed;
      }
    }
    if (mode == ext::go_mode::ms){
      reset();
      move(speed,speed);
      waitUntil( Brain.Timer.time(msec) > goal);
      stop();
      wait (0.8,sec);
    }

    if (mode == ext::go_mode::degree){
      reset();
      move(speed,speed);
      if (goal >0) waitUntil( MotorLF.position(degrees) > goal);
      else if (goal < 0) waitUntil ( MotorLF.position(degrees) < goal);
      stop();
      wait (0.8,sec);
    }

    return ;
    
  }

  const float turning_k = (2608.5)/360/3;
// turn for degree
  void ext::turn(int goal , ext::turn_mode mode){
    if (mode == ext::turn_mode::dipan){
      pids go ;
      go.pre(goal * turning_k,10);
      float movement;
      reset();
      while ( go.check (MotorLB.position(degrees)) )  {
        movement = go.moving();
        move(-movement * 0.4,+movement * 0.4);
      }
      stop();
      wait (0.8,sec);
      return ;
    }
    if (mode == ext::turn_mode::ine){
      pids go ;
      go.pre(goal,10);
      float movement;
      Ine.calibrate();
      while ( go.check (Ine.heading(degrees)) )  {
        movement = go.moving();
        move(-movement *0.4,movement *0.4);
      }
      
      stop();
      wait (0.8,sec);
    }
    return ;
  }

  void ext::turnto(int x,int y){
    const float goal = atan( (y - GPS.yPosition(mm)) / (x-GPS.xPosition(mm)) );
    pids turning;
    turning.pre (goal,5,0.5,0.7,0.7);
    float movement;
    while (turning.check(GPS.heading())){
      movement = turning.moving();
      move (movement,-movement);
    }
  }
  void ext::walkto(int x,int y){
    pids turning , walking;
    float tgoal;
    tgoal = atan( (y-GPS.yPosition(mm)) / (x-GPS.xPosition(mm)) );
    float dist;
    dist = pow( (y-GPS.yPosition(mm))*(y-GPS.yPosition(mm)) + (x-GPS.xPosition(mm))*(x-GPS.xPosition(mm)) , 0.5 );
    turning.pre(tgoal,5,0.5,0.7,0.7);
    walking.pre(0,5,0.5,0.7,0.7);
    float wa,tu;// walk , turn
    while (dist > 10){
      tgoal = atan( (y-GPS.yPosition(mm)) / (x-GPS.xPosition(mm)) );
      dist = pow( (y-GPS.yPosition(mm))*(y-GPS.yPosition(mm)) + (x-GPS.xPosition(mm))*(x-GPS.xPosition(mm)) , 0.5 );
      wa = walking.moving();
      tu = turning.moving();
      move(wa-tu , wa+tu);
    }
  }
