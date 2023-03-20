using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorLF;
extern motor MotorLM;
extern motor MotorLB;
extern motor MotorRF;
extern motor MotorRM;
extern motor MotorRB;
extern rotation Rotation;
extern inertial Inertial4;
extern motor MotorShot;
extern motor MotorFun;
extern controller Controller1;
extern gps GPS;
extern inertial Ine;

extern float degr;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );