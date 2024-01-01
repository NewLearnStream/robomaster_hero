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
#include "infrastructure\component\etl\delegate.h"
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
        Thread *me = reinterpret_cast<Thread *>(arg);
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
        tx_semaphore_put(&_semaphore);
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
        tx_timer_create(&_timer, const_cast<char *>(name), fun, fun_arg, UINT32_MAX, UINT32_MAX, TX_NO_ACTIVATE);
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

template <typename Object, void (Object::*Func)()>
class TimerMV : public Timer {
private:
    etl::delegate<void(void)> _d;

public:
    TimerMV(const char *name, Object &inst)
        : Timer(name, time_fun, this),
          _d(etl::delegate<void(void)>::create<Object, Func>(inst))
    {
    }

public:
    static void time_fun(uint32_t param)
    {
        TimerMV *me = reinterpret_cast<TimerMV *>(param);
        me->_d();
    }
};

template <typename TMesssage, uint32_t DETP>
class MessageQueue {
private:
    TX_QUEUE _queue;
    uint8_t _mem_sto[DETP * sizeof(TMesssage)];

public:
    MessageQueue(const char *name = "")
    {
        tx_queue_create(&_queue, const_cast<char *>(name), DETP, _mem_sto, sizeof(_mem_sto));
    }

    ~MessageQueue()
    {
        tx_queue_delete(&_queue);
    }

    void send(const TMesssage *msg)
    {
        tx_queue_send(&_queue, msg, TX_WAIT_FOREVER);
    }

    bool try_send(const TMesssage *msg)
    {
        uint32_t status = tx_queue_send(&_queue, msg, TX_NO_WAIT);
        return (status == TX_SUCCESS);
    }

    void receive(const TMesssage *msg)
    {
        tx_queue_receive(&_queue, msg, TX_WAIT_FOREVER);
    }

    bool try_receive(const TMesssage *msg)
    {
        uint32_t status = tx_queue_receive(&_queue, msg, TX_NO_WAIT);
        return (status == TX_SUCCESS);
    }
};

} // namespace os