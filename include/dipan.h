#pragma once

#include "vex.h"
#include "extensions.h"

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

