/**
 *!
 * \file        b_util_uart.c
 * \version     v0.0.1
 * \date        2020/04/01
 * \author      Bean(notrynohigh@outlook.com)
 *******************************************************************************
 * @attention
 *
 * Copyright (c) 2020 Bean
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 */

/*Includes ----------------------------------------------*/
#include "utils/inc/b_util_uart.h"
#include "core/inc/b_section.h"
#include "hal/inc/b_hal.h"

/**
 * \addtogroup B_UTILS
 * \{
 */

/**
 * \addtogroup UART
 * \{
 */

/**
 * \defgroup UART_Private_TypesDefinitions
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup UART_Private_Defines
 * \{
 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/**
 * \}
 */

/**
 * \defgroup UART_Private_Macros
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup UART_Private_Variables
 * \{
 */
static bUitlUartInstance_t bUitlUartHead = {.next = NULL, .prev = NULL};
/**
 * \}
 */

/**
 * \defgroup UART_Private_FunctionPrototypes
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup UART_Private_Functions
 * \{
 */

static void _UtilUartListAdd(bUitlUartInstance_t *pInstance)
{
    bUitlUartInstance_t *phead = &bUitlUartHead;
    for (;;)
    {
        if (phead->next == NULL)
        {
            phead->next     = pInstance;
            pInstance->prev = phead;
            pInstance->next = NULL;
            break;
        }
        else
        {
            phead = phead->next;
        }
    }
}

static void _bUtilUartDetectIdle()
{
    uint32_t             c_tick = bHalGetSysTick();
    bUitlUartInstance_t *phead  = &bUitlUartHead;
    for (;;)
    {
        if (phead->next != NULL)
        {
            if (phead->next->index > 0)
            {
                if (phead->next->l_index == 0)
                {
                    phead->next->l_index = phead->next->index;
                    phead->next->l_tick  = bHalGetSysTick();
                }
                else
                {
                    if (phead->next->index != phead->next->l_index)
                    {
                        phead->next->l_index = phead->next->index;
                        phead->next->l_tick  = bHalGetSysTick();
                    }
                    else if (bHalGetSysTick() - phead->next->l_tick > phead->next->idle_thd_ms)
                    {
                        if (phead->next->callback != NULL)
                        {
                            phead->next->callback(phead->next->pbuf, phead->next->index);
                            phead->next->index = 0;
                        }
                    }
                }
            }
        }
        else
        {
            break;
        }
        phead = phead->next;
    }
}

BOS_REG_POLLING_FUNC(_bUtilUartDetectIdle);

/**
 * \}
 */

/**
 * \addtogroup UART_Exported_Functions
 * \{
 */

void bUtilUartRxHandler(bUitlUartInstance_t *pInstance, uint8_t dat)
{
    if (pInstance == NULL)
    {
        return;
    }

    if (pInstance->prev == NULL)
    {
        _UtilUartListAdd(pInstance);
    }

    if (pInstance->index < pInstance->buf_size)
    {
        pInstance->pbuf[pInstance->index] = dat;
        pInstance->index += 1;
    }
}

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

/************************ Copyright (c) 2020 Bean *****END OF FILE****/
