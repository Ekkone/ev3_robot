/*
 * *************************************************************************************************
 * TTU-SG
 * Copyright (C) 2022 
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

//
// ┌─────┬─────────────────────────┐
// │note │         octave          │
// │name │  3     4     5      6   │
// ├─────├─────────────────────────┤
// │ C   │ 131   262    523   1047 │
// │ C#  │ 139   277    554   1109 │
// │ D   │ 147   294    587   1175 │
// │ D#  │ 156   311    622   1245 │
// │ E   │ 165   330    659   1319 │
// │ F   │ 175   349    698   1397 │
// │ F#  │ 185   370    740   1480 │
// │ G   │ 196   392    784   1568 │
// │ G#  │ 208   415    831   1661 │
// │ A   │ 220   440    880   1760 │
// │ A#  │ 233   466    932   1865 │
// │ B   │ 247   494    988   1976 │
// │ C   │ 262   523   1047   2093 │
// └─────┴─────────────────────────┘
int music_list[] = {131,147,165,175,196,220,247,262};

/**
 * @brief: 计算当前播放level
 * @param &touch
 * @param &infrared
 * @retval: 
 */
int cal_level(ev3dev::touch_sensor &touch,ev3dev::infrared_sensor &infrared)
{
    int level = 0;
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
    return level;
}

/**
 * @brief: 
 * @param argc
 * @param argv
 * @retval: 
 */
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
        sleep(1);
    }
    for(;;)
    {
        beep.set_freq(music_list[cal_level(touch,infrared)]);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
