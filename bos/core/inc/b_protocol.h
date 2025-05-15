/**
 *!
 * \file        b_protocol.h
 * \version     v0.1.0
 * \date        2020/03/15
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
#ifndef __B_PROTOCOL_H__
#define __B_PROTOCOL_H__

#ifdef __cplusplus
 extern "C" {
#endif

/*Includes ----------------------------------------------*/
#include "b_config.h"
#if _PROTO_ENABLE
/** 
 * \addtogroup BABYOS
 * \{
 */

/** 
 * \addtogroup PROTOCOL
 * \{
 */

/** 
 * \defgroup PROTOCOL_Exported_TypesDefinitions
 * \{
 */

#if _PROTO_FID_SIZE == 2
typedef uint16_t        bProtoID_t;  
#define INVALID_ID      0XFFFF
#else
typedef uint32_t        bProtoID_t; 
#define INVALID_ID      0XFFFFFFFF
#endif

#if _PROTO_FLEN_SIZE == 1
typedef uint8_t         bProtoLen_t;      
#else
typedef uint16_t        bProtoLen_t;  
#endif

/**
|      |                    |                     |       |          |       |
| :--- | ------------------ | ------------------- | ----- | -------- | ----- |
| Head | Device ID          | Len（cmd+param）    | Cmd   |  Param   | Check |
| 0xFE | sizeof(bProtoID_t) | sizeof(bProtoLen_t) | 1Byte | 0~nBytes | 1Byte |
*/
#pragma pack(1) 

typedef struct
{
    uint8_t head;
    bProtoID_t device_id;
    bProtoLen_t len;
    uint8_t cmd;
}bProtocolHead_t;   

#pragma pack()

typedef int (*pdispatch)(uint8_t cmd, uint8_t *param, bProtoLen_t param_len);

typedef struct
{
    bProtoID_t id;
    pdispatch f;
}bProtocolInfo_t;


/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Exported_Defines
 * \{
 */


#define PROTOCOL_HEAD       0xFE

/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Exported_Macros
 * \{
 */
      
/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Exported_Variables
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Exported_Functions
 * \{
 */
int bProtocolRegist(bProtoID_t id, pdispatch f);
int bProtocolSetID(int no, bProtoID_t id);
int bProtocolParse(int no, uint8_t *pbuf, bProtoLen_t len);
int bProtocolPack(int no, uint8_t cmd, uint8_t *param, bProtoLen_t param_size, uint8_t *pbuf);
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

/************************ Copyright (c) 2019 Bean *****END OF FILE****/

