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
* @file   : app.cpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#include <new>
#include "app.hpp"
#include "app/chassis/chassis_thread.hpp"

App::App *app = nullptr;

namespace App {
App::App()
    : _pid_lf(1.0f, 1.0f, 1.0f, 3000.0f, 200.0f),
      _pid_lr(1.0f, 1.0f, 1.0f, 3000.0f, 200.0f),
      _pid_rr(1.0f, 1.0f, 1.0f, 3000.0f, 200.0f),
      _pid_rf(1.0f, 1.0f, 1.0f, 3000.0f, 200.0f),
      blink_led(board->dio_pe7),
      m3508_lf(0x201, _pid_lf),
      m3508_lr(0x202, _pid_lr),
      m3508_rr(0x203, _pid_rr),
      m3508_rf(0x204, _pid_rf)
{
}

void init()
{
    static uint8_t mem_app[sizeof(App)];
    app = new (mem_app) App;

    static ChassisThread chassis_thread;
    chassis_thread.start();
}
} // namespace App