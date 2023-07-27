#include "pids.h"
using namespace ext;


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