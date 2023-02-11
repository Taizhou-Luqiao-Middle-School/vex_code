#include "vex.h"
//auto functions written by LXB
namespace af{
  // for buttons
  class on_off{
    private:
      bool opening;
      float cd;
      float check_time;
    public:
      void button(bool check);
      void button(bool check,bool flag);
      bool op();
          
      void prepare();
      void prepare(float cd_in);

      on_off();

      on_off(float cd_in);

      on_off(float cd_in,bool b);
  };

  //set some levels for a score
  class change{
    private:
      float speed;
      float min,max;
      float d;
      float check_time;
      float cd;
    public:
      void button(bool check);
      void button(bool check1,bool check2);

      int num();

      change();
      change(float t);
      change(float min_,float max_,float d_,float cd_);
  };

// 控制某一变量在一定的范围之内
  void maxmin (float& a,int speed_max = 80,int speed_min = 0);

// pids system
  class pids{
    private:

      float lasttime;
      
      int goal;

      float p;
      float pk;

      float i;
      float ik;
      float imax;

      float lastd;
      float dk;

      float jump;
      float jumptime;

      float outtime;

    public:
      void pre (int g,int j=10,float pkin = 0.5,float ikin = 0.8,float dkin = 0.8,float imaxin = 20.0);
      pids ();
      pids (int g);
      pids (int g,int j);
      bool check(int input,float& move);
  };

  void move(float r,float l);

  void Stop(bool flag = false);

  void reset();

// walk for degree 
  void go(int goal);
// turn for degree
  void turn(int goal);

  void turnto(int x,int y);
  void walkto(int x,int y);

}
