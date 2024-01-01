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
* @file   : app_config.h
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

// 中断优先级配置
enum ISRPriority {
    ISR_Prio_CAN1,    // CAN1
    ISR_Prio_CAN2,    // CAN2
    ISR_Prio_SysTick, // SysTick
    ISR_Prio_MAX,
};

// 线程优先级
enum ThreadPriority {
    Thread_Prio_Chassis,

};

#define THREAD_STACK_SIZE_CHASSIS (4 * 1024)