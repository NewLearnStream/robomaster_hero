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
* @file   : motor_base.hpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#pragma once
#include <math.h>

class MotorBase {
public:
    struct Message {
        uint16_t angle;
        uint16_t speed;
        uint16_t current;
        uint8_t temperture;
    };

private:
    const uint16_t _motor_id;

public:
    MotorBase(const uint16_t motor_id)
        : _motor_id(motor_id)
    {
    }

    void decode(Message *message, uint8_t *buf)
    {
        memcpy(message->data, buf, sizeof(message->data));
    }

    uint16_t get_id()
    {
        return _motor_id;
    }

    virtual uint16_t send_current() = 0;
};