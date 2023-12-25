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

#include "infrastructure/platform/hal/can.hpp"
#include "stm32f4xx.h"

class CanDriver : public Can {
private:
    uint32_t can_tx_mailbox;
    CAN_TxHeaderTypeDef can_tx_hander;
    bool is_error = false;

private:
    CAN_HandleTypeDef *_hcan;

public:
    CanDriver(CAN_HandleTypeDef *hcan)
        : _hcan(hcan)

    {
    }

    void send(const uint32_t id, uint8_t *buf, uint32_t len)
    {
        can_tx_hander.StdId              = id;
        can_tx_hander.ExtId              = 0x00;
        can_tx_hander.RTR                = CAN_RTR_DATA;
        can_tx_hander.IDE                = CAN_ID_STD;
        can_tx_hander.DLC                = len;
        can_tx_hander.TransmitGlobalTime = DISABLE;
        HAL_CAN_AddTxMessage(_hcan, &can_tx_hander, buf, &can_tx_mailbox);
    }

    void rece(const uint32_t id, uint8_t *buf, uint32_t len)
    {
        can_tx_hander.StdId              = id;
        can_tx_hander.ExtId              = 0x00;
        can_tx_hander.RTR                = CAN_RTR_DATA;
        can_tx_hander.IDE                = CAN_ID_STD;
        can_tx_hander.DLC                = len;
        can_tx_hander.TransmitGlobalTime = DISABLE;
        HAL_CAN_GetRxMessage(_hcan, &can_tx_hander, buf, &can_tx_mailbox);
    }
};