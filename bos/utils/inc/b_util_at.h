/**
 *!
 * \file        b_util_at.h
 * \version     v0.0.1
 * \date        2019/12/23
 * \author      Bean(notrynohigh@outlook.com)
 *******************************************************************************
 * @attention
 *
 * Copyright (c) 2019 Bean
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
#ifndef __B_UTIL_AT_H__
#define __B_UTIL_AT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*Includes ----------------------------------------------*/
#include <stdlib.h>
#include <string.h>

#include "b_config.h"

/**
 * \addtogroup B_UTILS
 * \{
 */

/**
 * \addtogroup AT
 * \{
 */

/**
 * \defgroup AT_Exported_TypesDefinitions
 * \{
 */
typedef void (*bAtCallback_t)(uint8_t id, uint8_t result, void *arg);
/**
 * \}
 */

/**
 * \defgroup AT_Exported_Defines
 * \{
 */
#define AT_INVALID_ID (0XFF)

#define AT_STA_NULL (0)
#define AT_STA_OK (1)
#define AT_STA_ERR (2)
#define AT_STA_ID_INVALID (3)
/**
 * \}
 */
#if (defined(_AT_ENABLE) && (_AT_ENABLE == 1))
/**
 * \defgroup AT_Exported_Functions
 * \{
 */
int bAtGetStat(uint8_t id);
int bAtRegistCallback(bAtCallback_t cb, void *arg);
int bAtFeedRespData(uint8_t *pbuf, uint16_t len);
int bAtCmdSend(const char *pcmd, uint16_t cmd_len, const char *presp, uint16_t resp_len,
               uint8_t uart, uint32_t timeout);
/**
 * \}
 */

#endif

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif
/************************ Copyright (c) 2019 Bean *****END OF FILE****/
