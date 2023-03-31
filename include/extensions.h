#include "vex.h"
using namespace vex;

/**
 * @brief 所有机器人通用的拓展 （extensions） , 悬停在你所不知道的函数或变量上就可以直接看到注释信息
 * @exception debug 时需要的函数 使用了 namespace debug 
*/
namespace ext{
    /*
    此枚举类适用于 ext::stop()   // 完整定义 void ext::stop(stop_mode m = coast);
    两个值 :
        hold    停止并锁死底盘
        coast   停止运动；松开底盘；
    值得注意的是，hold 不应多用，因为在底盘锁死时外力的冲撞会增大电机损坏的概率
                 coast 较为常用，但无法使机器人立刻停止（由于惯性）
    */
    enum class stop_mode{
        // 停止并锁死底盘
        hold = 0,
        // 停止运动；松开底盘；
        coast
    };

}

namespace ext{
// 此 布尔值 代表 颠倒左右底盘
    extern bool moving_reserve = 0;

// 停止并锁死底盘
    extern const stop_mode hold  ;
// 停止运动；松开底盘；
    extern const stop_mode coast ;
}

namespace ext{
    /*
    前进
    l 代表 左轮速度 （left）
    r 代表 右轮速度 （right）
    全局变量 extern bool ext::moving_reserve 影响此函数
    */
    void move(int l,int r);
    /**
    @brief 停止运动
    @param 可以不用填入，默认是coast,hold少用
    */
    void stop(stop_mode m = coast);
    /*
    重置底盘所记录的数据，包括：
    时间    （brain.Timer.time()）
    陀螺仪  （Ine.heading()）
    运动距离（motor.position()）
    */
    void reset();
    
}

namespace ext{
    // 控制某一变量在一定的范围之内
    void maxmin (float& a,int speed_max = 80,int speed_min = 0);
}


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

namespace ext{
    /**
    @brief cont需要被初始化
    */
    extern controller cont;
};

namespace ext{
    /**
    @brief 绑定一个按键，实现开关、调档的功能
    @author LXB
    @date 2023-3-21
    */
    class on_off{
        private :
            // bu1 up , bu2 down
            controller::button bu1,bu2;
            unsigned short n;
            /*
            mode 0 means bool_mode 
            mode 1 means value_mode single button
            mode 2 means value_mode double button
            */
            int  mod ; 

            //in mode 0
            bool b;

            /// @brief in mode 1 and 2
            int value,v_max,v_min,dis;

            int cd;
            int end_time;
        public:
            on_off();
            on_off(controller::button but , int m = 0);
            on_off(controller::button b1,controller::button b2);
            void setcd(int c);
            void set_vm(int max,int min);
            void set_d(int dist);
            void prevalue(int v);

            /**
             * @brief 更新按键状态
            */
            void check();
            /**
             * @brief 在 mode 0 下适用
            */
            bool b_value();
            /**
             * @brief 在 mode 1 or 2 下适用
            */
            int i_value();
            /**
            @returns mode 0 - bool_mode ; mode 1 - value_mode single button ; mode 2 - value_mode double button
            */
            int mode();
    };
};

namespace ext{
    //前进模式
    enum class go_mode{
        pid = 0,
        ms = 1,
        degree
    };

    //旋转模式
    enum class turn_mode{
        dipan = 0,
        ine
    };

    /**
     * @brief ext::go( ) 中的 pid 模式
    */
    extern const go_mode pid;
    /**
     * @brief ext::go( ) 中的计时模式(单位：ms)
    */
    extern const go_mode ms;
    /**
     * @brief ext::go( ) 中的角度模式
    */
    extern const go_mode degree;

    /**
     * @brief ext::turn( ) 中的底盘模式 (以底盘电机的position()来作为传感器)
    */
    extern const turn_mode dipan;
    /**
     * @brief ext::turn( ) 中的陀螺仪模式 (以陀螺仪的参数来作为传感器)
    */
    extern const turn_mode ine;

}

namespace ext{
    /**
     * @brief 前进,用于自动函数中前进一定的距离
     * @param 前进目标必须输入,模式默认pid,限速默认100
     * @return 无
     * @author LXB
     * @date 2023-3-21
     * @version 2.0
    */
    void go(int goal , go_mode mode = pid , int speed = 100);
    /**
     * @brief 旋转,用于自动函数旋转一定角度
     * @param 旋转目标必须输入,模式默认dipan
     * @exception 机社里的Ine不知为何大多都很阴间没法用，底盘作为第二方案又不是很准确，而且必须测出准确的turning_k （extensions.cpp）
     * @return 无
     * @author LXB
     * @date 2023-3-21
     * @version 2.0
    */
    void turn(int goal , turn_mode mode = dipan);

    /**
     * @brief 转向(x,y)处 ; 仅仅适用于安装了GPS的机器人！
     * @param (x,y)坐标
     * @exception 由于没有在任何一台机器人上实装了GPS，所以此函数不保证可用性！仅供参考！
     * @return 无
     * @author LXB
     * @date 2023-3-21
     * @version 0.8
    */
    void turnto(int x,int y);
    /**
     * @brief 移动到(x,y)处 ; 仅仅适用于安装了GPS的机器人！
     * @param (x,y)坐标
     * @exception 由于没有在任何一台机器人上实装了GPS，所以此函数不保证可用性！仅供参考！
     * @return 无
     * @author LXB
     * @date 2023-3-21
     * @version 0.8
    */
    void walkto(int x,int y);
}

using namespace ext;

/**
 * @brief 程序员调试代码时才用的到的一些函数，在正式的代码中不起到任何作用
 * @exception 请注意 namespace 为 debug , 不要误用为ext
*/
namespace debug{
    /**
     * @brief 检测机器人状态数据
     * @return 在手柄上显示 time 和 position
     * @exception 请注意该函数有没有使用namespace debug , 不要误用为ext
    */
    int OutPut();
    /**
     * @brief 手动重置机器人参数
     * @param 手柄上的按键B
     * @return 执行ext::reset()
     * @exception 请注意该函数有没有使用namespace debug , 不要误用为ext
    */
    void reput();
/**
 * @brief 测试最佳的pid参数
 * @return 在手柄上显示每次pid的运行时间，只显示一次，数据会被刷新
 * @exception 如果电机过热了应该会有提示；测试的间歇期应当视情况将机器人摆正
*/
    void experiment();
/**
 * @brief 测试旋转是否精准；主要用来测试turning_k ( extensions.cpp ext::turn( ) 前 )
 * @param n，每次旋转的角度为 360/n
 * @return 自己看机器人转的准不准啊！
 * @exception 请注意该函数有没有使用namespace debug , 不要误用为ext
*/
    void turning_test( float n = 4);
}
