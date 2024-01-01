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
#include "infrastructure/platform/hal/can.hpp"
#include "app_config.h"

class ChassisThread : public os::Thread<THREAD_STACK_SIZE_CHASSIS> {
private:
    Can &_can;

public:
    ChassisThread(const char *name = "chassis_thread")
        : Thread(name, Thread_Prio_Chassis),
          _can(board->can1)
    {
    }

public:
    void run() override
    {
        while (1)
        {
            os::delay_ms(10);
        }
    }
};