#include "dipan.h"

// 此 布尔值 代表 颠倒左右底盘
    bool moving_reserve = 0;

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