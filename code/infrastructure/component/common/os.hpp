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
* @file   : os.hpp
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#include "tx_api.h"
#include <cstdint>

namespace os {

void inline delay_ms(uint32_t tick)
{
    tx_thread_sleep(tick);
}

template <uint32_t STACK_SIZE>
class Thread {
private:
    TX_THREAD _thread;
    uint8_t _stack_sto[STACK_SIZE];

public:
    Thread(const char *name, uint32_t priority)
    {
        tx_thread_create(&_thread, const_cast<char *>(name),
                         entry, reinterpret_cast<uint32_t>(this),
                         &_stack_sto, STACK_SIZE,
                         priority, priority,
                         TX_NO_TIME_SLICE, TX_DONT_START);
    }
    ~Thread()
    {
        tx_thread_delete(&_thread);
    }

    void start()
    {
        tx_thread_resume(&_thread);
    }

private:
    virtual void run() = 0;

private:
    static void entry(uint32_t arg)
    {
        Thread *me = reinterpret_cast<Thread *>(arg_me);
        me->run();
    }
};

class Semaphore {
private:
    TX_SEMAPHORE _semaphore;

public:
    Semaphore(const char *name, uint32_t initial = 0)
    {
        tx_semaphore_create(&_semaphore, const_cast<char *>(name), initial);
    }

    ~Semaphore()
    {
        tx_semaphore_delete(&_semaphore);
    }

    void get()
    {
        tx_semaphore_get(&_semaphore, TX_WAIT_FOREVER);
    }

    void try_get()
    {
        tx_semaphore_get(&_semaphore, TX_NO_WAIT);
    }

    void wait_get(uint32_t ms)
    {
        tx_semaphore_get(&_semaphore, ms);
    }

    void put()
    {
        tx_semaphore_put();
    }
};

class Mutex {
private:
    TX_MUTEX _mutex;

public:
    Mutex(const char *name)
    {
        tx_mutex_create(&_mutex, const_cast<char *>(name), TX_INHERIT);
    }

    ~Mutex()
    {
        tx_mutex_delete(&_mutex);
    }

    void lock()
    {
        tx_mutex_get(&_mutex, TX_WAIT_FOREVER);
    }

    void try_lock()
    {
        tx_mutex_get(&_mutex, TX_NO_WAIT);
    }

    void unlock()
    {
        tx_mutex_put(&_mutex);
    }
};

class Timer {
private:
    TX_TIMER _timer;

public:
    Timer(const char *name, void (*fun)(uint32_t), uint32_t fun_arg)
    {
        tx_timer_create(&_timer, name, fun, fun_arg, UINT32_MAX, UINT32_MAX, TX_NO_ACTIVATE);
    }

    ~Timer()
    {
        tx_timer_delete(&_timer);
    }

    void start(uint32_t initial_tick, uint32_t reschedule_ticks)
    {
        tx_timer_change(&_timer, initial_tick, reschedule_ticks);
        tx_timer_activate(&_timer);
    }
};

} // namespace os