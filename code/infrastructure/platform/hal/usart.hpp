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
* @file   : usart.hpp
* @author : liyoyan
* @date   : 2 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

class Usart {
public:
    virtual void Usart_Send(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size) = 0;

    virtual void Usart_Receive(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size) = 0;
};