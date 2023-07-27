#pragma once

#include "vex.h"
#include "extensions.h"

/**
 * @brief 所有机器人通用的拓展 （extensions） , 悬停在你所不知道的函数或变量上就可以直接看到注释信息
 * @exception debug 时需要的函数 使用了 namespace debug 
*/
namespace ext{
    /*
    pid 算法的通用版 （pid system）
    使用此class , 就不用自己再去纠结p算法，i算法，d算法了
    只需要用 check(int input) 来 输入 传感器所传回的数据 ， moving()就会自动帮你计算好 运动量 了
    使用前必须告知 g (goal) 的值
    如： pids p(100);
    使用 pre() 来更改此系统的各种参数
    pid的优点是精度高，缺点是速度不是很快
    
    最后一次更新：LXB 2023.3.21
    */
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

      float delta;

    public:
    /*
    使用 pre() 来更改此系统的各种参数：
        goal    运动所期望到达的目标
        jump    结束运动时和目标的最坏期望
            //值过小会大大延长执行算法所需的时间
            //值过大会降低算法的精度
        pk      p算法的权
        ik      i算法的权
        dk      d算法的权
            //上述三种 k的取值 在 0-1 之间
        imax    i算法的最大影响度
    */
      void pre (int g,int j = 10,float pkin = 0.5,float ikin = 0.3,float dkin = 0.8,float imaxin = 10.0);
      pids ();
      pids (int g);
      pids (int g,int j);
      /**
      @param 传感器的返回数值
      @return 该函数仅返回是否完成运动
      */
      bool check(int input);
      /**
      @return 所需运动的大小
      @exception 使用前确保已经运行过check()
      */
      float moving();
  };
}



