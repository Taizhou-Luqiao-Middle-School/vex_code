#include "extensions.h"
using namespace ext;

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


