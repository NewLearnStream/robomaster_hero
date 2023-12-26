/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2021 John Wellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef ETL_MUTEX_THREADX_INCLUDED
#define ETL_MUTEX_THREADX_INCLUDED

#include "../platform.h"

#include "tx_api.h"

namespace etl
{
  //***************************************************************************
  ///\ingroup mutex
  ///\brief This mutex class is implemented using CMSIS's RTOS2 mutexes
  //***************************************************************************
  class mutex
  {
  public:

    mutex()
    {
      tx_mutex_create(&access, const_cast<char *>("ETL"), TX_INHERIT);
    }

    ~mutex()
    {
      tx_mutex_delete(&access);
    }

    void lock()
    {
      tx_mutex_get(&access, TX_WAIT_FOREVER);
    }

    bool try_lock()
    {
      return (tx_mutex_get(&access, TX_NO_WAIT) == TX_SUCCESS);
    }

    void unlock()
    {
      tx_mutex_put(&access);
    }

  private:

    mutex(const mutex&) ETL_DELETE;
    mutex& operator=(const mutex&) ETL_DELETE;

    TX_MUTEX access;
  };
}

#endif
