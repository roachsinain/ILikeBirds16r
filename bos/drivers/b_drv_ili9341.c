/**
 *!
 * \file        b_drv_ili9341.c
 * \version     v0.0.1
 * \date        2020/03/02
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
#include "drivers/inc/b_drv_ili9341.h"

/**
 * \addtogroup BABYOS
 * \{
 */

/**
 * \addtogroup B_DRIVER
 * \{
 */

/**
 * \addtogroup ILI9341
 * \{
 */

/**
 * \defgroup ILI9341_Private_TypesDefinitions
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup ILI9341_Private_Defines
 * \{
 */
#ifndef _LCD_X_SIZE
#define _LCD_X_SIZE 240
#endif

#ifndef _LCD_Y_SIZE
#define _LCD_Y_SIZE 320
#endif
/**
 * \}
 */

/**
 * \defgroup ILI9341_Private_Macros
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup ILI9341_Private_Variables
 * \{
 */
const static bILI9341_HalIf_t bILI9341_HalIf = HAL_ILI9341_IF;
bILI9341_Driver_t             bILI9341_Driver;
/**
 * \}
 */

/**
 * \defgroup ILI9341_Private_FunctionPrototypes
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup ILI9341_Private_Functions
 * \{
 */

static void _bLcdWriteData(uint16_t dat)
{
    if (bILI9341_HalIf.is_rw_addr)
    {
        ((bLcdRWAddress_t *)bILI9341_HalIf._if.rw_addr)->dat = dat;
    }
    else
    {
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rs.port, bILI9341_HalIf._if._io.rs.pin, 1);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rd.port, bILI9341_HalIf._if._io.rd.pin, 1);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 0);
        bHalGPIODriver.pGpioWritePort(bILI9341_HalIf._if._io.data.port, dat);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.wr.port, bILI9341_HalIf._if._io.wr.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.wr.port, bILI9341_HalIf._if._io.wr.pin, 1);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 1);
    }
}

static void _bLcdWriteCmd(uint16_t cmd)
{

    if (bILI9341_HalIf.is_rw_addr)
    {
        ((bLcdRWAddress_t *)bILI9341_HalIf._if.rw_addr)->reg = cmd;
    }
    else
    {
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rs.port, bILI9341_HalIf._if._io.rs.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rd.port, bILI9341_HalIf._if._io.rd.pin, 1);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 0);
        bHalGPIODriver.pGpioWritePort(bILI9341_HalIf._if._io.data.port, cmd);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.wr.port, bILI9341_HalIf._if._io.wr.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.wr.port, bILI9341_HalIf._if._io.wr.pin, 1);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 1);
    }
}

static uint16_t _bLcdReadData()
{
    uint16_t dat;

    if (bILI9341_HalIf.is_rw_addr)
    {
        dat = ((bLcdRWAddress_t *)bILI9341_HalIf._if.rw_addr)->dat;
    }
    else
    {
        bHalGPIODriver.pGpioConfig(bILI9341_HalIf._if._io.data.port, bILI9341_HalIf._if._io.data.pin,
                        B_HAL_GPIO_INPUT, B_HAL_GPIO_NOPULL);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rs.port, bILI9341_HalIf._if._io.rs.pin, 1);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rd.port, bILI9341_HalIf._if._io.rd.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rd.port, bILI9341_HalIf._if._io.rd.pin, 1);
        dat = bHalGPIODriver.pGpioReadPort(bILI9341_HalIf._if._io.data.port);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 1);
        bHalGPIODriver.pGpioConfig(bILI9341_HalIf._if._io.data.port, bILI9341_HalIf._if._io.data.pin,
                        B_HAL_GPIO_OUTPUT, B_HAL_GPIO_NOPULL);
    }
    return dat;
}

/*
static uint16_t _bLcdReadCmd()
{
    uint16_t cmd;

    if (bILI9341_HalIf.is_rw_addr)
    {
        cmd = ((bLcdRWAddress_t *)bILI9341_HalIf._if.rw_addr)->reg;
    }
    else
    {
        bHalGPIODriver.pGpioConfig(bILI9341_HalIf._if._io.data.port, bILI9341_HalIf._if._io.data.pin,
                        B_HAL_GPIO_INPUT, B_HAL_GPIO_NOPULL);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rs.port, bILI9341_HalIf._if._io.rs.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rd.port, bILI9341_HalIf._if._io.rd.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 0);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.rd.port, bILI9341_HalIf._if._io.rd.pin, 1);
        cmd = bHalGPIODriver.pGpioReadPort(bILI9341_HalIf._if._io.data.port);
        bHalGPIODriver.pGpioWritePin(bILI9341_HalIf._if._io.cs.port, bILI9341_HalIf._if._io.cs.pin, 1);
        bHalGPIODriver.pGpioConfig(bILI9341_HalIf._if._io.data.port, bILI9341_HalIf._if._io.data.pin,
                        B_HAL_GPIO_OUTPUT, B_HAL_GPIO_NOPULL);
    }
    return cmd;
}
*/

static void _bILI9341SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    _bLcdWriteCmd(0X2A);
    _bLcdWriteData(Xpos >> 8);
    _bLcdWriteData(Xpos & 0XFF);
    _bLcdWriteCmd(0X2B);
    _bLcdWriteData(Ypos >> 8);
    _bLcdWriteData(Ypos & 0XFF);
    _bLcdWriteCmd(0X2C);
}

static int _bILI9341Write(bILI9341_Driver_t *pdrv, uint32_t addr, uint8_t *pbuf, uint16_t len)
{
    uint16_t     x      = addr % _LCD_X_SIZE;
    uint16_t     y      = addr / _LCD_X_SIZE;
    bLcdWrite_t *pcolor = (bLcdWrite_t *)pbuf;
    if (y >= _LCD_Y_SIZE || pbuf == NULL || len < sizeof(bLcdWrite_t))
    {
        return -1;
    }
    _bILI9341SetCursor(x, y);
    _bLcdWriteData(pcolor->color);
    return 2;
}

/**
 * \}
 */

/**
 * \addtogroup ILI9341_Exported_Functions
 * \{
 */
int bILI9341_Init()
{
    uint16_t id;
    _bLcdWriteCmd(0XD3);
    id = _bLcdReadData();
    id = _bLcdReadData();
    id = _bLcdReadData();
    id <<= 8;
    id |= _bLcdReadData();
    b_log("id:%x\r\n", id);
    if (id != 0x9341)
    {
        bILI9341_Driver.status = -1;
        return -1;
    }
    _bLcdWriteCmd(0xCF);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0xC1);
    _bLcdWriteData(0X30);
    _bLcdWriteCmd(0xED);
    _bLcdWriteData(0x64);
    _bLcdWriteData(0x03);
    _bLcdWriteData(0X12);
    _bLcdWriteData(0X81);
    _bLcdWriteCmd(0xE8);
    _bLcdWriteData(0x85);
    _bLcdWriteData(0x10);
    _bLcdWriteData(0x7A);
    _bLcdWriteCmd(0xCB);
    _bLcdWriteData(0x39);
    _bLcdWriteData(0x2C);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x34);
    _bLcdWriteData(0x02);
    _bLcdWriteCmd(0xF7);
    _bLcdWriteData(0x20);
    _bLcdWriteCmd(0xEA);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteCmd(0xC0);
    _bLcdWriteData(0x1B);
    _bLcdWriteCmd(0xC1);
    _bLcdWriteData(0x01);
    _bLcdWriteCmd(0xC5);
    _bLcdWriteData(0x30);
    _bLcdWriteData(0x30);
    _bLcdWriteCmd(0xC7);
    _bLcdWriteData(0XB7);
    _bLcdWriteCmd(0x36);
    _bLcdWriteData(0x08);
    _bLcdWriteCmd(0x3A);
    _bLcdWriteData(0x55);
    _bLcdWriteCmd(0xB1);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x1A);
    _bLcdWriteCmd(0xB6);
    _bLcdWriteData(0x0A);
    _bLcdWriteData(0xA2);
    _bLcdWriteCmd(0xF2);
    _bLcdWriteData(0x00);
    _bLcdWriteCmd(0x26);
    _bLcdWriteData(0x01);
    _bLcdWriteCmd(0xE0);
    _bLcdWriteData(0x0F);
    _bLcdWriteData(0x2A);
    _bLcdWriteData(0x28);
    _bLcdWriteData(0x08);
    _bLcdWriteData(0x0E);
    _bLcdWriteData(0x08);
    _bLcdWriteData(0x54);
    _bLcdWriteData(0XA9);
    _bLcdWriteData(0x43);
    _bLcdWriteData(0x0A);
    _bLcdWriteData(0x0F);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteCmd(0XE1);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x15);
    _bLcdWriteData(0x17);
    _bLcdWriteData(0x07);
    _bLcdWriteData(0x11);
    _bLcdWriteData(0x06);
    _bLcdWriteData(0x2B);
    _bLcdWriteData(0x56);
    _bLcdWriteData(0x3C);
    _bLcdWriteData(0x05);
    _bLcdWriteData(0x10);
    _bLcdWriteData(0x0F);
    _bLcdWriteData(0x3F);
    _bLcdWriteData(0x3F);
    _bLcdWriteData(0x0F);
    _bLcdWriteCmd(0x2B);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x01);
    _bLcdWriteData(0x3f);
    _bLcdWriteCmd(0x2A);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0x00);
    _bLcdWriteData(0xef);
    _bLcdWriteCmd(0x11);
    bHalDelayMs(120);
    _bLcdWriteCmd(0x29);
    bILI9341_Driver.status = 0;
    bILI9341_Driver.close  = NULL;
    bILI9341_Driver.read   = NULL;
    bILI9341_Driver.ctl    = NULL;
    bILI9341_Driver.open   = NULL;
    bILI9341_Driver.write  = _bILI9341Write;
    return 0;
}

bDRIVER_REG_INIT(bILI9341_Init);

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

/************************ Copyright (c) 2019 Bean *****END OF FILE****/
