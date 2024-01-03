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
* @file   : pid.hpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#include "common.hpp"

#pragma once

template <typename T>
class PidBase {
protected:
    const T _kp;
    const T _ki;
    const T _kd;
    const T _output_max;
    const T _integral_limit;
    T _err;
    T _last_err;

public:
    PidBase(const T kp, const T ki, const T kd, const T output_max, const T integral_limit)
        : _kp(kp),
          _ki(ki),
          _kd(kd),
          _output_max(output_max),
          _integral_limit(integral_limit),
          _err(static_cast<T>(0)),
          _last_err(static_cast<T>(0))
    {
    }

    virtual T run(T target, T measure) = 0;
};

template <typename T>
class IncrementalPid : public PidBase<T> {
private:
    T _before_err;

public:
    IncrementalPid(const T kp, const T ki, const T kd, const T output_max, const T integral_limit)
        : PidBase<T>(kp, ki, kd, output_max, integral_limit),
          _before_err(static_cast<T>(0))

    {
    }

    T run(T target, T measure)
    {
        T out_put;
        T p_out, i_out, d_out;
        this->_err = measure - target;

        p_out = this->_kp * (this->_err - this->_last_err);
        i_out = this->_ki * this->_err;
        d_out = this->_kd * (this->_err - 2.0f * this->_last_err + _before_err);

        i_out = clip<T>(i_out, this->_integral_limit, -this->_integral_limit);

        out_put = p_out + i_out + d_out;

        out_put = clip<T>(out_put, this->_output_max, -this->_output_max);

        _before_err = this->_last_err;

        this->_last_err = this->_err;

        return out_put;
    }
};

template <typename T>
class PostionPid : public PidBase<T> {
private:
    T total_integral;

public:
    PostionPid(const T kp, const T ki, const T kd, const T output_max, const T integral_limit)
        : PidBase<T>(kp, ki, kd, output_max, integral_limit),
          total_integral(static_cast<T>(0))
    {
    }

    T run(T target, T measure)
    {
        T out_put;
        T p_out, i_out, d_out;
        this->_err = measure - target;

        p_out = this->_kp * this->_err;

        total_integral += this->_err;
        i_out = this->_ki * total_integral;
        i_out = clip<T>(i_out, this->_integral_limit, -this->_integral_limit);

        d_out = this->kd * (this->_err - this->_last_err);

        out_put = p_out + i_out + d_out;
        out_put = clip<T>(out_put, this->_output_max, -this->_output_max);

        this->_last_err = this->_err;

        return out_put;
    }
};

template <typename T>
class SeriesPostionPid {
private:
    PostionPid<T> &_interior_pid; // 内环PID
    PostionPid<T> &_outer_pid;    // 外环PID

public:
    SeriesPostionPid(PostionPid<T> &interior_pid, PostionPid<T> &outer_pid)
        : _interior_pid(interior_pid),
          _outer_pid(outer_pid)
    {
    }

    T run(T tar, T interior_measure, T outer_measure)
    {
        T out_put = _outer_pid.run(tar, outer_measure);
        return (_interior_pid.run(out_put, interior_measure));
    }
};
