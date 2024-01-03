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
* @file   : Board.hpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#include "bsp_cpu.h"
#include "bsp_gpio.h"
#include "bsp_can.h"

#include "infrastructure/platform/arch/stm32f4xx/can_driver.hpp"
#include "infrastructure/platform/arch/stm32f4xx/dio_driver.hpp"

namespace BSP {
class Board {
public:
    DioDriver dio_pe7;
    CanDriver can1;
    CanDriver can2;
    Board();
};

void init();

void deinit();

void enable_irqs();

}; // namespace BSP

extern BSP::Board *board;