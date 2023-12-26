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
* @file   : main.cpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#include "stm32f4xx.h"
#include "app_config.h"
#include "app.hpp"
#include "board.hpp"
#include "tx_api.h"

#include "infrastructure\component\common\pid.hpp"

int main()
{
    Board::init();

    tx_kernel_enter();
}

extern "C" {

extern uint32_t g_pfnVectors;

void _tx_initialize_low_level(void)
{
    __set_PRIMASK(1);         // 关闭全部中断
    SCB->VTOR = g_pfnVectors; // 设置中断向量表偏移

    NVIC_SetPriority(SVCall_IRQn, 0xFF);

    NVIC_SetPriority(PendSV_IRQn, 0xFF);

    NVIC_SetPriority(SysTick_IRQn, ISR_Prio_SysTick);
}

void tx_application_define(void *first_unused_memory)
{
    App::init();
}
}