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
* @file   : common.hpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#include <cstdint>
#include <math.h>

template <typename T>
static inline T clip(T value, T max, T min)
{
    if (value > max)
        value = max;
    else if (value < min)
        value = min;
    return value;
}

template <typename T>
static inline T abs_max(T *arr, uint32_t len)
{
    T max;
    for (uint32_t i = 0; i < len; i++)
    {
        if (abs(arr[i]) > max)
            max = abs(arr[i]);
    }
    return max;
}