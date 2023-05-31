#include "extensions.h"
using namespace ext;

void ext::move(int l,int r){
    if (moving_reserve == 1){
        int t = l;
        l = r;
        r = t;
    }
    MotorLF.spin(fwd , l , pct);
    MotorLM.spin(fwd , l , pct);
    MotorLB.spin(fwd , l , pct);
    MotorRF.spin(fwd , r , pct);
    MotorRM.spin(fwd , r , pct);
    MotorRB.spin(fwd , r , pct);
}
using namespace vex;
void ext::stop(stop_mode m){
    if (m==coast){
        MotorLF.stop(vex::coast);
        MotorLM.stop(vex::coast);
        MotorLB.stop(vex::coast);
        MotorRF.stop(vex::coast);
        MotorRM.stop(vex::coast);
        MotorRB.stop(vex::coast);
    }
    else {
        MotorLF.stop(vex::hold);
        MotorLM.stop(vex::hold);
        MotorLB.stop(vex::hold);
        MotorRF.stop(vex::hold);
        MotorRM.stop(vex::hold);
        MotorRB.stop(vex::hold);
    }
}

void ext::reset(){
    Brain.Timer.reset();
    Ine.calibrate();
    MotorLF.resetPosition();
    MotorLM.resetPosition();
    MotorLB.resetPosition();
    MotorRF.resetPosition();
    MotorRM.resetPosition();
    MotorRB.resetPosition();
}

on_off::on_off(){
    mod = 0;
    b = 0;
    value = 0;
    v_max = 100;
    v_min = -100;
    cd = 90;
    end_time = 0;
}
on_off::on_off(controller::button but , int m ){
    bu1 = but;
    mod = m;
    b = 0;
    value = 0;
    v_max = 100;
    v_min = -100;
    cd = 90;
    end_time = 0;
}
on_off::on_off(controller::button b1,controller::button b2){
    mod = 2;
    bu1 = b1;
    bu2 = b2;
    b = 0;
    value = 0;
    v_max = 100;
    v_min = -100;
    cd = 90;
    end_time = 0;
}
void on_off::setcd(int c){
    cd = c;
}
void on_off::set_vm(int max,int min){
    v_max = max;
    v_min = min;
}
void on_off::prevalue(int v){
    value = v;
}
void on_off::set_d(int dist){
    dis = dist;
}

void on_off::check(){
    if (Brain.Timer.time(msec) < end_time){
        return;
    }
    end_time = Brain.Timer.time(msec) + cd;
    if (mod == 0){
        if (bu1.pressing()==0){
            return;
        }
        b = !b;
        return ;
    }
    if (mod == 1){
        if (bu1.pressing()==0){
            return;
        }
        value += dis;
        if ( value > v_max ){
            value = v_max;
        }
        return ;
    }
    if (mod == 2){
        if (bu1.pressing()==1){
            value += dis;
        }
        if (bu2.pressing()==1){
            value -= dis;
        }
        if (value > v_max){
            value = v_max;
        }
        if (value < v_min){
            value = v_min;
        }
        return ;
    }
}

bool on_off::b_value(){
    return b;
}

int on_off::i_value(){
    return value;
}

int on_off::mode(){
    return mod;
}

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


void ext::maxmin (float& a,int speed_max,int speed_min){
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
void ext::pids::pre (int g,int j,float pkin ,float ikin ,float dkin ,float imaxin ){
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
ext::pids::pids (){
        pre (100);
      }
ext::pids::pids (int g){
        pre (g);
      }
ext::pids::pids (int g,int j){
        pre (g,j);
      }
bool ext::pids::check(int input){
        delta = goal - input;
        
        if (Brain.Timer.time(sec) >= outtime) {
          return 0;
        }
        if ( fabs(delta) > jump){
          outtime = Brain.Timer.time(sec) + jumptime;
        }
        return 1;
      }



float ext::pids::moving(){
        Controller1.Screen.newLine();
        
        float timenow = Brain.Timer.time(sec);
        float delattime = timenow - lasttime;
        lasttime = timenow;
        delattime /= 0.05;

        p = delta * pk;

        i = i + delta * ik *delattime;

        ext::maxmin(i,imax,0);

        int d = ( delta - lastd ) * dk / delattime;
        lastd = delta;
        
        float result = p+i+d;
        //Controller1.Screen.print("d:%.1f jt:%.1f    ", delta,jumptime);
        //Controller1.Screen.print("p:%.1f", MotorLF.position(degrees));
        //Controller1.Screen.print("dt:%.1f    ",delattime);
        //Controller1.Screen.print("p:%.1f i:%.1f d:%.1f", p,i,d);
        return result;
}

using namespace debug;

int debug::OutPut(){
    if (Controller1.ButtonLeft.pressing() == 1){
        reset();
    }
    Controller1.Screen.clearLine();
    Controller1.Screen.print("t:%.1f l:%.2f",Brain.Timer.time(sec),MotorLB.position(degrees));
    return 1;
}

void debug::reput(){
    if (Controller1.ButtonB.pressing()){
        ext::reset();
    }
}

void debug::turning_test ( float n){
    const float d = 360/n;
    while (1){
        turn (d);
    }
}

void debug::experiment(){
    pids go;
    for (float p=0.1 ; p < 0.9 ; p+=0.1){
        for (float i=0.1 ; i < 0.9 ; i+=0.1){
            for (float d=0.1 ; d < 0.9 ; d+=0.1){
                for (float imax = 2; imax <=30 ;imax += 2){
                    go.pre(500,10,p,i,d,imax);
                    reset();
                    float m = 0;
                    while (go.check(MotorLF.position(degrees))){
                        m = go.moving();
                        move(m,m);
                    }
                    ext::stop();

                    go.pre(-500);
                    MotorLF.resetPosition();
                    while (go.check(MotorLF.position(degrees))){
                        m = go.moving();
                        move(m,m);
                    }
                    ext::stop();

                    Controller1.Screen.clearLine();
                    Controller1.Screen.print ("%.1f %.1f %.1f %d t:%.1f",p,i,d,imax,Brain.Timer.time(sec)/2.0);
                    wait (2,sec);
                }
            }
            ext::stop();
            Controller1.Screen.clearLine();
            Controller1.Screen.print("正在检查电机温度...");
            float high_t = MotorLF.temperature();
            
            if ( MotorLM.temperature() > high_t ) high_t = MotorLM.temperature();
            if ( MotorLB.temperature() > high_t ) high_t = MotorLB.temperature();
            if ( MotorRF.temperature() > high_t ) high_t = MotorRF.temperature();
            if ( MotorRM.temperature() > high_t ) high_t = MotorRM.temperature();
            if ( MotorRB.temperature() > high_t ) high_t = MotorRB.temperature();

            Controller1.Screen.clearLine();
            if ( high_t >= 60 ){
                
                Controller1.Screen.print("等待几分钟,之后待电机恢复25°C时继续实验");
                while ( high_t > 25);
                
            }
            else {
                Controller1.Screen.print("温度正常 , 电机最高温度:%.1f°C",high_t);
                wait(1.5,sec);
            }
            Controller1.Screen.clearLine();
            Controller1.Screen.print("即将继续实验 , 3秒后做好准备");
            wait(3,sec);
            Controller1.Screen.clearLine();
            
        }
        
    }
}
