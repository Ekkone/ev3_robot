/*
 * *************************************************************************************************
 * TTU-SG
 * Copyright (C) 2022 Friendcom
 * 
 * @file         : main.cpp
 * @author       : ekko
 * @version      : V0.1
 * @date         : 2023-01-30
 * @brief        : 
 * @details      : 
 * @attention    : 
 * 
 * Change History : 
 * 
 * 
 * 
 * *************************************************************************************************
 */
#include <iostream>
#include <thread>
#include "ev3dev.h"
#include "beep.hpp"

using namespace std;

uint8_t music_list[] = {131,147,165,175,196,220,247,262};

/**
 * @brief: 是否需要播放
 * @param &touch
 * @param &infrared
 * @param &level 播放频率
 * @retval: 
 */
bool need_play(ev3dev::touch_sensor &touch,ev3dev::infrared_sensor &infrared,int &level)
{
    //拨弦按下
    if(!touch.is_pressed())
    {
        //获取距离 0-100 :: 0-70cm
        //3.5-40 -> 5-57
        auto distance = infrared.proximity();
        printf("distance : %d\n",distance);
        //计算levle 0-55
        level = (distance - 5) / 7;
        //level超限处理
        if(level >= sizeof(music_list))
            level = sizeof(music_list);
        else if(level < 0)
            level = 0;
        printf("level : %d\n",level);
    }
    return false;
}



int main(int argc, char** argv)
{
    //触摸传感器
    ev3dev::touch_sensor touch;
    //红外距离传感器
    ev3dev::infrared_sensor infrared;
    //中型电机
    ev3dev::medium_motor motor;
    //蜂鸣器
    Beep beep;
    while(!beep.open())
    {
        this_thread::sleep_for(chrono::seconds(1));
    }

    int level = 0;
    for(;;)
    {
        //需要播放
        if(need_play(touch,infrared,level))
        {
            beep.set_freq(music_list[level]);
        }
        else
            beep.set_freq(0);
        
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
