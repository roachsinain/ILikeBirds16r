/**
 *!
 * \file        b_drv_ili9320.c
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
#include "drivers/inc/b_drv_ili9320.h"

/**
 * \addtogroup BABYOS
 * \{
 */

/**
 * \addtogroup B_DRIVER
 * \{
 */

/**
 * \addtogroup ILI9320
 * \{
 */

/**
 * \defgroup ILI9320_Private_TypesDefinitions
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup ILI9320_Private_Defines
 * \{
 */

#define DRIVER_NAME ILI9320

#ifndef LCD_X_SIZE
#define LCD_X_SIZE 240
#endif

#ifndef LCD_Y_SIZE
#define LCD_Y_SIZE 320
#endif
/**
 * \}
 */

/**
 * \defgroup ILI9320_Private_Macros
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup ILI9320_Private_Variables
 * \{
 */
bDRIVER_HALIF_TABLE(bILI9320_HalIf_t, DRIVER_NAME);
/**
 * \}
 */

/**
 * \defgroup ILI9320_Private_FunctionPrototypes
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup ILI9320_Private_Functions
 * \{
 */

static void _bLcdWriteData(bDriverInterface_t *pdrv, uint16_t dat)
{
    bDRIVER_GET_HALIF(_if, bILI9320_HalIf_t, pdrv);
    if (_if->if_type == LCD_IF_TYPE_RWADDR)
    {
        ((bLcdRWAddress_t *)_if->_if.rw_addr)->dat = dat;
    }
    else if (_if->if_type == LCD_IF_TYPE_IO)
    {
        bHalGpioWritePin(_if->_if._io.rs.port, _if->_if._io.rs.pin, 1);
        bHalGpioWritePin(_if->_if._io.rd.port, _if->_if._io.rd.pin, 1);
        bHalGpioWritePin(_if->_if._io.cs.port, _if->_if._io.cs.pin, 0);
        bHalGpioWritePort(_if->_if._io.data.port, dat);
        bHalGpioWritePin(_if->_if._io.wr.port, _if->_if._io.wr.pin, 0);
        bHalGpioWritePin(_if->_if._io.wr.port, _if->_if._io.wr.pin, 1);
        bHalGpioWritePin(_if->_if._io.cs.port, _if->_if._io.cs.pin, 1);
    }
}

static void _bLcdWriteCmd(bDriverInterface_t *pdrv, uint16_t cmd)
{
    bDRIVER_GET_HALIF(_if, bILI9320_HalIf_t, pdrv);
    if (_if->if_type == LCD_IF_TYPE_RWADDR)
    {
        ((bLcdRWAddress_t *)_if->_if.rw_addr)->reg = cmd;
    }
    else if (_if->if_type == LCD_IF_TYPE_IO)
    {
        bHalGpioWritePin(_if->_if._io.rs.port, _if->_if._io.rs.pin, 0);
        bHalGpioWritePin(_if->_if._io.rd.port, _if->_if._io.rd.pin, 1);
        bHalGpioWritePin(_if->_if._io.cs.port, _if->_if._io.cs.pin, 0);
        bHalGpioWritePort(_if->_if._io.data.port, cmd);
        bHalGpioWritePin(_if->_if._io.wr.port, _if->_if._io.wr.pin, 0);
        bHalGpioWritePin(_if->_if._io.wr.port, _if->_if._io.wr.pin, 1);
        bHalGpioWritePin(_if->_if._io.cs.port, _if->_if._io.cs.pin, 1);
    }
}

static uint16_t _bLcdReadData(bDriverInterface_t *pdrv)
{
    uint16_t dat = 0;
    bDRIVER_GET_HALIF(_if, bILI9320_HalIf_t, pdrv);
    if (_if->if_type == LCD_IF_TYPE_RWADDR)
    {
        dat = ((bLcdRWAddress_t *)_if->_if.rw_addr)->dat;
    }
    else if (_if->if_type == LCD_IF_TYPE_IO)
    {
        bHalGpioConfig(_if->_if._io.data.port, _if->_if._io.data.pin, B_HAL_GPIO_INPUT,
                       B_HAL_GPIO_NOPULL);
        bHalGpioWritePin(_if->_if._io.rs.port, _if->_if._io.rs.pin, 1);
        bHalGpioWritePin(_if->_if._io.rd.port, _if->_if._io.rd.pin, 0);
        bHalGpioWritePin(_if->_if._io.cs.port, _if->_if._io.cs.pin, 0);
        bHalGpioWritePin(_if->_if._io.rd.port, _if->_if._io.rd.pin, 1);
        dat = bHalGpioReadPort(_if->_if._io.data.port);
        bHalGpioWritePin(_if->_if._io.cs.port, _if->_if._io.cs.pin, 1);
        bHalGpioConfig(_if->_if._io.data.port, _if->_if._io.data.pin, B_HAL_GPIO_OUTPUT,
                       B_HAL_GPIO_NOPULL);
    }
    return dat;
}

static void _bILI9320WriteReg(bDriverInterface_t *pdrv, uint16_t reg, uint16_t dat)
{
    _bLcdWriteCmd(pdrv, reg);
    _bLcdWriteData(pdrv, dat);
}

static void _bILI9320SetCursor(bDriverInterface_t *pdrv, uint16_t Xpos, uint16_t Ypos)
{
    _bILI9320WriteReg(pdrv, 0X20, Xpos);
    _bILI9320WriteReg(pdrv, 0X21, Ypos);
    _bLcdWriteCmd(pdrv, 0X22);
}

static int _bILI9320Write(bDriverInterface_t *pdrv, uint32_t addr, uint8_t *pbuf, uint32_t len)
{
    uint16_t     x      = addr % LCD_X_SIZE;
    uint16_t     y      = addr / LCD_X_SIZE;
    bLcdWrite_t *pcolor = (bLcdWrite_t *)pbuf;
    if (y >= LCD_Y_SIZE || pbuf == NULL || len < sizeof(bLcdWrite_t))
    {
        return -1;
    }
    _bILI9320SetCursor(pdrv, x, y);
    _bLcdWriteData(pdrv, pcolor->color);
    return 2;
}

/**
 * \}
 */

/**
 * \addtogroup ILI9320_Exported_Functions
 * \{
 */
int bILI9320_Init(bDriverInterface_t *pdrv)
{
    bDRIVER_STRUCT_INIT(pdrv, DRIVER_NAME, bILI9320_Init);
    pdrv->write = _bILI9320Write;

    _bLcdWriteCmd(pdrv, 0x0);
    if (_bLcdReadData(pdrv) != 0x9320)
    {
        return -1;
    }
    _bILI9320WriteReg(pdrv, 0x00, 0x0000);
    _bILI9320WriteReg(pdrv, 0x01, 0x0100);  // Driver Output Contral.
    _bILI9320WriteReg(pdrv, 0x02, 0x0700);  // LCD Driver Waveform Contral.
    _bILI9320WriteReg(pdrv, 0x03, 0x1010);  // Entry Mode Set.

    _bILI9320WriteReg(pdrv, 0x04, 0x0000);    // Scalling Contral.
    _bILI9320WriteReg(pdrv, 0x08, 0x0202);    // Display Contral 2.(0x0207)
    _bILI9320WriteReg(pdrv, 0x09, 0x0000);    // Display Contral 3.(0x0000)
    _bILI9320WriteReg(pdrv, 0x0a, 0x0000);    // Frame Cycle Contal.(0x0000)
    _bILI9320WriteReg(pdrv, 0x0c, (1 << 0));  // Extern Display Interface Contral 1.(0x0000)
    _bILI9320WriteReg(pdrv, 0x0d, 0x0000);    // Frame Maker Position.
    _bILI9320WriteReg(pdrv, 0x0f, 0x0000);    // Extern Display Interface Contral 2.
    bHalDelayMs(50);
    _bILI9320WriteReg(pdrv, 0x07, 0x0101);  // Display Contral.
    bHalDelayMs(50);
    _bILI9320WriteReg(
        pdrv, 0x10,
        (1 << 12) | (0 << 8) | (1 << 7) | (1 << 6) | (0 << 4));     // Power Control 1.(0x16b0)
    _bILI9320WriteReg(pdrv, 0x11, 0x0007);                          // Power Control 2.(0x0001)
    _bILI9320WriteReg(pdrv, 0x12, (1 << 8) | (1 << 4) | (0 << 0));  // Power Control 3.(0x0138)
    _bILI9320WriteReg(pdrv, 0x13, 0x0b00);                          // Power Control 4.
    _bILI9320WriteReg(pdrv, 0x29, 0x0000);                          // Power Control 7.

    _bILI9320WriteReg(pdrv, 0x2b, (1 << 14) | (1 << 4));
    _bILI9320WriteReg(pdrv, 0x50, 0);  // Set X Star

    _bILI9320WriteReg(pdrv, 0x51, 239);  // Set Y Star
    _bILI9320WriteReg(pdrv, 0x52, 0);    // Set Y End.t.
    _bILI9320WriteReg(pdrv, 0x53, 319);  //

    _bILI9320WriteReg(pdrv, 0x60, 0x2700);  // Driver Output Control.
    _bILI9320WriteReg(pdrv, 0x61, 0x0001);  // Driver Output Control.
    _bILI9320WriteReg(pdrv, 0x6a, 0x0000);  // Vertical Srcoll Control.

    _bILI9320WriteReg(pdrv, 0x80, 0x0000);  // Display Position? Partial Display 1.
    _bILI9320WriteReg(pdrv, 0x81, 0x0000);  // RAM Address Start? Partial Display 1.
    _bILI9320WriteReg(pdrv, 0x82, 0x0000);  // RAM Address End-Partial Display 1.
    _bILI9320WriteReg(pdrv, 0x83, 0x0000);  // Displsy Position? Partial Display 2.
    _bILI9320WriteReg(pdrv, 0x84, 0x0000);  // RAM Address Start? Partial Display 2.
    _bILI9320WriteReg(pdrv, 0x85, 0x0000);  // RAM Address End? Partial Display 2.

    _bILI9320WriteReg(pdrv, 0x90, (0 << 7) | (16 << 0));  // Frame Cycle Contral.(0x0013)
    _bILI9320WriteReg(pdrv, 0x92, 0x0000);                // Panel Interface Contral 2.(0x0000)
    _bILI9320WriteReg(pdrv, 0x93, 0x0001);                // Panel Interface Contral 3.
    _bILI9320WriteReg(pdrv, 0x95, 0x0110);                // Frame Cycle Contral.(0x0110)
    _bILI9320WriteReg(pdrv, 0x97, (0 << 8));              //
    _bILI9320WriteReg(pdrv, 0x98, 0x0000);                // Frame Cycle Contral.
    _bILI9320WriteReg(pdrv, 0x07, 0x0173);                //(0x0173)

    return 0;
}

bDRIVER_REG_INIT(B_DRIVER_ILI9320, bILI9320_Init);

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

/************************ Copyright (c) 2020 Bean *****END OF FILE****/
