#include "debug.h"

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
        af::reset();
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
                    af::Stop();

                    go.pre(-500);
                    MotorLF.resetPosition();
                    while (go.check(MotorLF.position(degrees))){
                        m = go.moving();
                        move(m,m);
                    }
                    af::Stop();

                    Controller1.Screen.clearLine();
                    Controller1.Screen.print ("%.1f %.1f %.1f %d t:%.1f",p,i,d,imax,Brain.Timer.time(sec)/2.0);
                    wait (2,sec);
                }
            }
            af::Stop();
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
