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
* @file   : led.hpp
* @author : xiongqulin
* @date   : 3 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#include "infrastructure/platform/hal/dio.hpp"

class Led {
private:
    Dio &_dio;
    uint32_t _active_status; // 是否为反逻辑

public:
    Led(Dio &dio, uint32_t active_status = 0)
        : _dio(dio),
          _active_status(active_status)
    {
    }

    void open()
    {
        uint32_t status = _active_status ? 1 : 0;
        _dio.write(status);
    }

    void close()
    {
        uint32_t status = _active_status ? 0 : 1;
        _dio.write(status);
    }

    void toggle()
    {
        _dio.toggle();
    }
};