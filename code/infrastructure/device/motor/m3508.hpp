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
* @file   : m3508.hpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#include "motor_base.hpp"
#include "infrastructure/component/common/pid.hpp"
#include "infrastructure/platform/hal/can.hpp"

class M3508 : public MotorBase {
private:
    IncrementalPid<float> &_pid;
    struct Message _msg;

public:
    M3508(const uint16_t motor_id, IncrementalPid<float> &pid)
        : MotorBase(motor_id),
          _pid(pid)
    {
    }

    float output_current(uint32_t target)
    {
        return _pid.run(target, _msg.current);
    }

    void updata_message(const uint16_t id, uint8_t *buf, uint32_t len)
    {
        if (id == _motor_id)
            this->decode(&_msg, buf, len);
    }

public:
    static void send_current(Can &can, const uint32_t send_id, int16_t current_0, int16_t current_1, int16_t current_2, int16_t current_3)
    {
        uint8_t current[8];
        current[0] = current_0 >> 8;
        current[1] = current_0;
        current[2] = current_1 >> 8;
        current[3] = current_1;
        current[4] = current_2 >> 8;
        current[5] = current_2;
        current[6] = current_3 >> 8;
        current[7] = current_3;

        can.write(send_id, current, 8);
    }
};