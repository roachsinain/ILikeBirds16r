/**
 *!
 * \file        algo_md5.h
 * \version     v0.0.1
 * \date        2020/04/27
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
#ifndef __ALGO_MD5_H__
#define __ALGO_MD5_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "b_config.h"

#if (defined(_ALGO_MD5_ENABLE) && (_ALGO_MD5_ENABLE == 1))

/**
 * \addtogroup ALGORITHM
 * \{
 */

/**
 * \addtogroup MD5
 * \{
 */

/**
 * \defgroup SORT_Exported_Functions
 * \{
 */

// 结果未小写的字符串
void md5_16(uint8_t* input, uint32_t ilen, uint8_t output[16]);
void md5_32(uint8_t* input, uint32_t ilen, uint8_t output[32]);

// 结果为十六进制数组
void md5_hex_8(uint8_t* input, uint32_t ilen, uint8_t output[8]);
void md5_hex_16(uint8_t* input, uint32_t ilen, uint8_t output[16]);

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

#endif

#ifdef __cplusplus
}
#endif

#endif
