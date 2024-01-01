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

#include "bsp.hpp"

BSP::Board *board = nullptr;

namespace BSP {
Board::Board()
    : can1(&hcan1),
      can2(&hcan1)
{
}

void init()
{
    bsp_can_init();
}

void deinit()
{
    bsp_can_deinit();
}

void enable_irqs()
{
}

} // namespace BSP