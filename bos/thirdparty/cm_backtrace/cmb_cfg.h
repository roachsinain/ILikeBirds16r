/*
 * This file is part of the CmBacktrace Library.
 *
 * Copyright (c) 2016, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is the configure head file for this library.
 * Created on: 2016-12-15
 */

#ifndef _CMB_CFG_H_
#define _CMB_CFG_H_

#include "b_config.h"
#include "utils/inc/b_util_log.h"
/* print line, must config by user */

#if (defined(_CMBACKTRACE_ENABLE) && (_CMBACKTRACE_ENABLE == 1))

#define cmb_println(...)    \
    do                      \
    {                       \
        b_log(__VA_ARGS__); \
        b_log("\r\n");      \
    } while (0)

//<o> ARM Cortex M ?
//<0=> ARM_CORTEX_M0
//<1=> ARM_CORTEX_M3
//<2=> ARM_CORTEX_M4
//<3=> ARM_CORTEX_M7
//<4=> ARM_CORTEX_M33
#if defined(TRACE_ARM_CORTEX_M0)
#define CMB_CPU_PLATFORM_TYPE 0
#elif defined(TRACE_ARM_CORTEX_M3)
#define CMB_CPU_PLATFORM_TYPE 1
#elif defined(TRACE_ARM_CORTEX_M4)
#define CMB_CPU_PLATFORM_TYPE 2
#elif defined(TRACE_ARM_CORTEX_M7)
#define CMB_CPU_PLATFORM_TYPE 3
#elif defined(TRACE_ARM_CORTEX_M33)
#define CMB_CPU_PLATFORM_TYPE 4
#else
#define CMB_CPU_PLATFORM_TYPE 1
#endif

#endif /* _CMB_CFG_H_ */
