#pragma once

#include "vex.h"
#include "extensions.h"

/**
 * @brief 所有机器人通用的拓展 （extensions） , 悬停在你所不知道的函数或变量上就可以直接看到注释信息
 * @exception debug 时需要的函数 使用了 namespace debug 
*/
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
