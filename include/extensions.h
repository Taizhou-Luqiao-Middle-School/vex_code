#pragma once

#include "vex.h"
//#include "autofunctions.h"
//#include "button.h"
//#include "debug.h"
//#include "dipan.h"
//#include "pids.h"

/**
 * @brief 所有机器人通用的拓展 （extensions） , 悬停在你所不知道的函数或变量上就可以直接看到注释信息
 * @warning debug 时需要的函数 使用了 namespace debug 
*/
namespace ext{
    // 控制某一变量在一定的范围之内
    void maxmin (float& a,int speed_max = 80,int speed_min = 0);
}


