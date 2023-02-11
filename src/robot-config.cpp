#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Cont = controller(primary);
motor Motor = motor(PORT1, ratio18_1, false);
motor MotorLF = motor(PORT8, ratio18_1, false);
motor MotorLM = motor(PORT8, ratio18_1, false);
motor MotorLB = motor(PORT8, ratio18_1, false);
motor MotorRF = motor(PORT8, ratio18_1, false);
motor MotorRM = motor(PORT8, ratio18_1, false);
motor MotorRB = motor(PORT8, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vis = vision (PORT2, 50);
/*vex-vision-config:end*/
inertial Ine = inertial(PORT3);
rotation Rota = rotation(PORT4, false);
gps GPS = gps(PORT5, 1.00, 2.00, mm, 180);
digital_out Pne = digital_out(Brain.ThreeWirePort.A);

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