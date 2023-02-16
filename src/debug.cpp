#include "debug.h"

using namespace debug;

int debug::OutPut(){
    if (Controller1.ButtonLeft.pressing() == 1){
        reset();
    }
    Controller1.Screen.newLine();
    Controller1.Screen.print("t:%.1f l:%.2f",Brain.Timer.time(sec),MotorLB.position(degrees));
    return 1;
}

void debug::reput(){
    if (Controller1.ButtonB.pressing()){
        af::reset();
    }
}

