#include "button.h"
using namespace ext;
on_off::on_off(){
    mod = 0;
    b = 0;
    value = 0;
    v_max = 100;
    v_min = -100;
    cd = 90;
    end_time = 0;
}
on_off::on_off(controller::button but , int m ){
    bu1 = but;
    mod = m;
    b = 0;
    value = 0;
    v_max = 100;
    v_min = -100;
    cd = 90;
    end_time = 0;
}
on_off::on_off(controller::button b1,controller::button b2){
    mod = 2;
    bu1 = b1;
    bu2 = b2;
    b = 0;
    value = 0;
    v_max = 100;
    v_min = -100;
    cd = 90;
    end_time = 0;
}
void on_off::setcd(int c){
    cd = c;
}
void on_off::set_vm(int max,int min){
    v_max = max;
    v_min = min;
}
void on_off::prevalue(int v){
    value = v;
}
void on_off::set_d(int dist){
    dis = dist;
}

void on_off::check(){
    if (Brain.Timer.time(msec) < end_time){
        return;
    }
    end_time = Brain.Timer.time(msec) + cd;
    if (mod == 0){
        if (bu1.pressing()==0){
            return;
        }
        b = !b;
        return ;
    }
    if (mod == 1){
        if (bu1.pressing()==0){
            return;
        }
        value += dis;
        if ( value > v_max ){
            value = v_max;
        }
        return ;
    }
    if (mod == 2){
        if (bu1.pressing()==1){
            value += dis;
        }
        if (bu2.pressing()==1){
            value -= dis;
        }
        if (value > v_max){
            value = v_max;
        }
        if (value < v_min){
            value = v_min;
        }
        return ;
    }
}

bool on_off::b_value(){
    return b;
}

int on_off::i_value(){
    return value;
}

int on_off::mode(){
    return mod;
}