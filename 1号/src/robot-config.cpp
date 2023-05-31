#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorLF = motor(PORT10, ratio18_1, false);
motor MotorLM = motor(PORT9, ratio18_1, false);
motor MotorLB = motor(PORT8, ratio18_1, true);
motor MotorRF = motor(PORT7, ratio18_1, false);
motor MotorRM = motor(PORT6, ratio18_1, false);
motor MotorRB = motor(PORT5, ratio18_1, true);
rotation Rotation = rotation(PORT11, false);
inertial Inertial4 = inertial(PORT21);
motor MotorShot = motor(PORT2, ratio18_1, false);
motor MotorFun = motor(PORT12, ratio18_1, true);
controller Controller1 = controller(primary);
inertial Ine = inertial(PORT3);
gps GPS = gps(PORT5, 1.00, 2.00, mm, 180);

digital_out Pne1 = digital_out(Brain.ThreeWirePort.A);
digital_out Pne2 = digital_out(Brain.ThreeWirePort.B);
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