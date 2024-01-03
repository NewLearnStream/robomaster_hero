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
* @file   : dio.hpp
* @author : xiongqulin
* @date   : 3 Jan 2023
* @brief  :
*
*********************************************************************************************************
*/
#pragma once

class Dio {
public:
    virtual void write(uint32_t status) = 0;

    virtual void toggle() = 0;

    virtual bool read_input() = 0;

    virtual bool read_output() = 0;
};