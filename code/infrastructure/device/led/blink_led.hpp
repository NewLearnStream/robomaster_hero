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
* @file   : blink_led.hpp
* @author : xiongqulin
* @date   : 3 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#include "led.hpp"

class BlinkLed : public Led {
public:
    static constexpr uint32_t PERIOD_MS_MIN = 10; // 最小周期
private:
    uint32_t _period_ms        = 1000; // 闪烁周期
    uint8_t _duty_cycle        = 50;   // 占空比
    uint8_t _duty_cycle_offset = 0;    // 占空比偏移量(启动时led亮灭)
    uint32_t _on_offset_ms     = 0;
    uint32_t _off_offset_ms    = 0;

public:
    BlinkLed(Dio &dio, uint32_t active_status = 0)
        : Led(dio, active_status)
    {
    }

    void setup(uint32_t period_ms, uint8_t duty_cycle = 50, uint8_t duty_cycle_offset = 0)
    {
        _period_ms  = period_ms < PERIOD_MS_MIN ? PERIOD_MS_MIN : period_ms;
        _duty_cycle = duty_cycle > 100 ? 100 : duty_cycle;

        uint32_t duty_cycle_offset_max = 100 - _duty_cycle;
        _duty_cycle_offset             = duty_cycle_offset > duty_cycle_offset_max ? duty_cycle_offset_max : duty_cycle_offset;
        _on_offset_ms                  = _period_ms * _duty_cycle_offset / 100;
        _off_offset_ms                 = _period_ms * (_duty_cycle_offset + _duty_cycle) / 100;
    }

    void constant_open()
    {
        setup(1000, 100, 0);
    }

    void constant_close()
    {
        setup(1000, 0, 0);
    }

    void blink(uint32_t timestamp_ms)
    {
        if (_duty_cycle == 0)
        {
            close();
        }
        else if (_duty_cycle >= 100)
        {
            open();
        }
        else
        {
            uint32_t mod = timestamp_ms % _period_ms;
            if (mod <= _on_offset_ms)
                close();
            else if (mod <= _off_offset_ms)
                open();
            else
                close();
        }
    }
};