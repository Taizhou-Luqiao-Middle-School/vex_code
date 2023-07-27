#pragma once

#include "extensions.h"
#include "pids.h"
#include "dipan.h"

/**
 * @brief 所有机器人通用的拓展 （extensions） , 悬停在你所不知道的函数或变量上就可以直接看到注释信息
 * @exception debug 时需要的函数 使用了 namespace debug 
*/
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

