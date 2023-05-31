using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor Motor;
extern motor MotorLF ;
extern motor MotorLM ;
extern motor MotorLB ;
extern motor MotorRF ;
extern motor MotorRM ;
extern motor MotorRB ;
extern signature Vis__SIG_1;
extern signature Vis__SIG_2;
extern signature Vis__SIG_3;
extern signature Vis__SIG_4;
extern signature Vis__SIG_5;
extern signature Vis__SIG_6;
extern signature Vis__SIG_7;
extern vision Vis;
extern inertial Ine;
extern rotation Rota;
extern gps GPS;
extern digital_out Pne;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );