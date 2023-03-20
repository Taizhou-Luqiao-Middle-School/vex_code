#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorLF = motor(PORT4, ratio18_1, false);
motor MotorLM = motor(PORT8, ratio18_1, true);
motor MotorLB = motor(PORT10, ratio18_1, true);
motor MotorRF = motor(PORT9, ratio18_1, true);
motor MotorRM = motor(PORT6, ratio18_1, false);
motor MotorRB = motor(PORT13, ratio18_1, false);
rotation Rotation = rotation(PORT15, false);
inertial Inertial4 = inertial(PORT14);
motor MotorShot = motor(PORT1, ratio18_1, true);
motor MotorFun = motor(PORT11, ratio18_1, false);
controller Controller1 = controller(primary);
inertial Ine = inertial(PORT3);
gps GPS = gps(PORT5, 1.00, 2.00, mm, 180);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}