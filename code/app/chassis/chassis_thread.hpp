/**
*********************************************************************************************************
* Copyright (C) 2023-2026 by xiongqulin - All Rights Reserved.                                              *
*                                                                                                       *
* This file is part of the project.                                                                     *
*                                                                                                       *
* This file can not be copied and/or distributed without the express permission of the project owner.   *
*********************************************************************************************************/

/**
*********************************************************************************************************
* @file   : chassis.hpp
* @author : xiongqulin
* @date   : 1 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#include "bsp.hpp"
#include "infrastructure/component/common/os.hpp"
#include "infrastructure/component/common/common.hpp"
#include "infrastructure/platform/hal/can.hpp"
#include "app_config.h"

class ChassisThread : public os::Thread<THREAD_STACK_SIZE_CHASSIS> {

private:
    static constexpr float motor_max_speed = 6600.0f; // 单轮最大速度
    static constexpr float x_max_speed     = 6600.0f; // 底盘前后最快速度
    static constexpr float y_max_speed     = 6600.0f; // 底盘平移最快速度
    static constexpr float w_max_speed     = 6600.0f; // 底盘自旋最快速度
    static constexpr uint16_t send_can_id  = 0x200;   // M3508发送电流ID

private:
    Can &_can;

    M3508 &m3508_lf; // 左前轮电机
    M3508 &m3508_lr; // 左后轮电机
    M3508 &m3508_rr; // 右后轮电机
    M3508 &m3508_rf; // 右前轮电机
private:
    int16_t _motor_speed[4];

public:
    ChassisThread(const char *name = "chassis_thread")
        : Thread(name, Thread_Prio_Chassis),
          _can(board->can1),
          m3508_lf(app->m3508_lf),
          m3508_lr(app->m3508_lr),
          m3508_rr(app->m3508_rr),
          m3508_rf(app->m3508_rf)
    {
    }

    void mecanum_calculate(float x, float y, float w) // 麦轮解算
    {
        float speed[4];
        float max_speed;
        float radio;

        clip<float>(x, x_max_speed, -x_max_speed);
        clip<float>(y, y_max_speed, -y_max_speed);
        clip<float>(w, w_max_speed, -w_max_speed);

        speed[0] = x - y + w;
        speed[1] = x + y + w;
        speed[2] = -x + y + w;
        speed[3] = -x - y + w;

        max_speed = abs_max<float>(speed, 4);

        radio = (max_speed > motor_max_speed) ? (1.0f) : (max_speed / motor_max_speed);

        _motor_speed[0] = speed[0] * radio;
        _motor_speed[1] = speed[1] * radio;
        _motor_speed[2] = speed[2] * radio;
        _motor_speed[3] = speed[3] * radio;
    }

public:
    void run() override
    {
        while (1)
        {
            /*需要在这里等待对应的事件才能触发后面的操作*/
            //  mecanum_calculate(x, y, w);
            M3508::send_current(_can, send_can_id,
                                m3508_lf.output_current(_motor_speed[0]), m3508_lr.output_current(_motor_speed[1]),
                                m3508_rr.output_current(_motor_speed[2]), m3508_rf.output_current(_motor_speed[3]));
            os::delay_ms(10);
        }
    }
};