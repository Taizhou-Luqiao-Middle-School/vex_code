#include "vex.h"
#include "tfiles.h"
//auto functions written by LXB

void af::on_off::button(bool check){
    if (check && Brain.Timer.time(sec) >= check_time){
      opening = !opening;
      check_time = Brain.Timer.time(sec) + cd;
    }
}
void af::on_off::button(bool check,bool flag){
    if ( (check && Brain.Timer.time(sec) >= check_time) or flag == true){
        opening = !opening;
        //check_time = Brain.Timer.time(msec) + cd;
    }
}
bool af::on_off::op(){
    return opening;
}
          
void af::on_off::prepare(){
    check_time = Brain.Timer.time(msec);
    cd = 20;
}
void af::on_off::prepare(float cd_in){
    check_time = Brain.Timer.time(msec);
    cd = cd_in;
}

af::on_off::on_off(){
    prepare();
}

af::on_off::on_off(float cd_in){
    prepare(cd_in);
}

af::on_off::on_off(float cd_in,bool b){
    prepare(cd_in);
    opening = b;
}

void af::change::button(bool check){
        if (check && Brain.Timer.time(sec)>=check_time ){
          check_time = Brain.Timer.time(sec) + cd;
          speed += d;
          if (speed > max){
            speed = min;
          }
          Controller1.Screen.clearLine();
          Controller1.Screen.print("shot speed:%d",speed);
        }
      }
void af::change::button(bool check1,bool check2){
        if ( (check1 || check2) && Brain.Timer.time(sec) >= check_time){
          check_time = Brain.Timer.time(sec) + cd;
          if (check1 == 1){
            speed += d;
          }
          if (check2 == 1){
            speed -= d;
          }
          if (speed > max){
            speed = min;
          }
          if (speed < min){
            speed = max;
          }
          Controller1.Screen.clearLine();
          Controller1.Screen.print("shot speed:%d",speed);
        }
      }

int af::change::num(){
        return speed;
      }

af::change::change(){
        min=0;
        max=100;
        d=20;
        check_time=0;
        cd=0.02;
        speed = (min + max) / 2;
      }
af::change::change(float t){
        min=0;
        max=100;
        d=20;
        cd=t;
        speed = (min + max) / 2;
      }
af::change::change(float min_,float max_,float d_,float cd_){
        min = min_;
        max = max_;
        d = d_;
        cd = cd_;
        speed = (min + max) / 2;
      }

// 控制某一变量在一定的范围之内
void af::maxmin (float& a,int speed_max,int speed_min){
    if (fabs(a)>speed_max){
      if (a>0){
        a=speed_max;
      }
      else {
        a=-speed_max;
      }
    }
    if (fabs(a)<speed_min){
      if (a>0){
        a=0;
      }
      else {
        a=0;
      }
    }
  }

// pids system
void af::pids::pre (int g,int j,float pkin ,float ikin ,float dkin ,float imaxin ){
        goal = g;
        jump = j;
        pk = pkin;
        ik = ikin;
        dk = dkin;
        imax = imaxin;
        i=0;
        lasttime = Brain.Timer.time(sec);
        lastd = 0;
        jumptime = 1.0;
      }
af::pids::pids (){
        pre (100);
      }
af::pids::pids (int g){
        pre (g);
      }
af::pids::pids (int g,int j){
        pre (g,j);
      }
bool af::pids::check(int input){
        delta = goal - input;
        
        if (Brain.Timer.time(sec) >= outtime) {
          return 0;
        }
        if ( fabs(delta) > jump){
          outtime = Brain.Timer.time(sec) + jumptime;
        }
        return 1;
      }



float af::pids::moving(){
        Controller1.Screen.newLine();
        
        float timenow = Brain.Timer.time(sec);
        float delattime = timenow - lasttime;
        lasttime = timenow;
        delattime /= 0.05;

        p = delta * pk;

        i = i + delta * ik *delattime;

        maxmin(i,imax,0);

        int d = ( delta - lastd ) * dk / delattime;
        lastd = delta;
        
        float result = p+i+d;
        //Controller1.Screen.print("d:%.1f jt:%.1f    ", delta,jumptime);
        //Controller1.Screen.print("p:%.1f", MotorLF.position(degrees));
        //Controller1.Screen.print("dt:%.1f    ",delattime);
        //Controller1.Screen.print("p:%.1f i:%.1f d:%.1f", p,i,d);
        return result;
}

void af::move(float r,float l){
    MotorLF.spin(forward,l,pct);
    MotorLB.spin(forward,l,pct);
    MotorLM.spin(forward,l,pct);
    MotorRF.spin(forward,r,pct);
    MotorRB.spin(forward,r,pct);
    MotorRM.spin(forward,r,pct);
  }

  void af::stop(bool flag ){
    if (flag == true ){
      MotorLF.stop(hold);
      MotorLB.stop(hold);
      MotorLM.stop(hold);
      MotorRF.stop(hold);
      MotorRB.stop(hold);
      MotorRM.stop(hold);
      return;
    }
    else {
      MotorLF.stop(coast);
      MotorLB.stop(coast);
      MotorLM.stop(coast);
      MotorRF.stop(coast);
      MotorRB.stop(coast);
      MotorRM.stop(coast);
      return;
    }
  }

  void af::reset(){
    MotorLF.resetPosition();
    MotorLB.resetPosition();
    MotorLM.resetPosition();
    MotorRF.resetPosition();
    MotorRB.resetPosition();
    MotorRM.resetPosition();
    //Ine.calibrate();
    Brain.Timer.reset();
  }

// walk for degree 
  void af::go(int goal , go_mode mode , int speed){
    if (goal == 0 or speed == 0 ){
      return ;
    }
    if (mode == af::go_mode::pid){

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
    if (mode == af::go_mode::ms){
      reset();
      move(speed,speed);
      waitUntil( Brain.Timer.time(msec) > goal);
      stop();
      wait (0.8,sec);
    }

    if (mode == af::go_mode::degree){
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
  void af::turn(int goal , af::turn_mode mode){
    if (mode == af::turn_mode::dipan){
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
    if (mode == af::turn_mode::ine){
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

  void af::turnto(int x,int y){
    const float goal = atan( (y - GPS.yPosition(mm)) / (x-GPS.xPosition(mm)) );
    pids turning;
    turning.pre (goal,5,0.5,0.7,0.7);
    float movement;
    while (turning.check(GPS.heading())){
      movement = turning.moving();
      move (movement,-movement);
    }
  }
  void af::walkto(int x,int y){
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
