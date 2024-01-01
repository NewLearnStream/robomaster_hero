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

class Can {
public:
    virtual void send(const uint32_t id, uint8_t *buf, uint32_t len) = 0;

    virtual void rece(const uint32_t id, uint8_t *buf, uint32_t len) = 0;
};
