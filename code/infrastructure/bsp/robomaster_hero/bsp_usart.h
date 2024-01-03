/**
*********************************************************************************************************
* Copyright (C) 2023-2026 by liyoyan - All Rights Reserved.                                              *
*                                                                                                       *
* This file is part of the project.                                                                     *
*                                                                                                       *
* This file can not be copied and/or distributed without the express permission of the project owner.   *
*********************************************************************************************************/

/**
*********************************************************************************************************
* @file   : bsp_usart.h
* @author : liyoyan
* @date   : 2 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "main.h"

extern UART_HandleTypeDef huart1;

void MX_USART_Init(void);



void USART1_IRQHandler(void)；
void DMA2_Stream2_IRQHandler(void)；

#ifdef __cplusplus
}
#endif // __cplusplus