#ifndef __B_HAL_IF_H__
#define __B_HAL_IF_H__

#include "b_config.h"

// debug
#define HAL_LOG_UART B_HAL_UART_1

#define HAL_TESTFLASH_IF            \
    {                               \
        .e_size = 4096, .w_size = 1 \
    }

#endif
