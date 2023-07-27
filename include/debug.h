#pragma once

#include "vex.h"
#include "extensions.h"

/**
 * @brief 程序员调试代码时才用的到的一些函数，在正式的代码中不起到任何作用
*/
namespace debug{
    /**
     * @brief 检测机器人状态数据
     * @return 在手柄上显示 time 和 position
    */
    int OutPut();
    /**
     * @brief 手动重置机器人参数
     * @param 手柄上的按键B
     * @return 执行ext::reset()
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
*/
    void turning_test( float n = 4);
}

