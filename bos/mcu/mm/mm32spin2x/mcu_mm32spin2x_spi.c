/**
 *!
 * \file        mcu_mm32spin2x_spi.c
 * \version     v0.0.1
 * \date        2020/03/25
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SSPIL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 */

/*Includes ----------------------------------------------*/
#include "b_config.h"
#include "hal/inc/b_hal_spi.h"
#include "utils/inc/b_util_spi.h"

#if (_MCU_PLATFORM == 3001)

#ifndef NULL
#define NULL ((void *)0)
#endif

static int _SpiSetSpeed(bHalSPIIf_t *spi_if, bHalSPISpeed_t speed)
{
    if (IS_NULL(spi_if))
    {
        return -1;
    }
    switch (spi_if->_if.spi)
    {
        case B_HAL_SPI_1:

            break;
        default:
            break;
    }
    return 0;
}

static uint8_t _SpiTransfer(bHalSPIIf_t *spi_if, uint8_t dat)
{
    uint8_t    tmp;
    bUtilSPI_t simulating_spi;
    if (IS_NULL(spi_if))
    {
        return 0;
    }
    if (spi_if->is_simulation == 1)
    {
        simulating_spi.clk  = spi_if->_if.simulating_spi.clk;
        simulating_spi.mosi = spi_if->_if.simulating_spi.mosi;
        simulating_spi.miso = spi_if->_if.simulating_spi.miso;
        simulating_spi.CPHA = spi_if->_if.simulating_spi.CPHA;
        simulating_spi.CPOL = spi_if->_if.simulating_spi.CPOL;
        tmp                 = bUtilSPI_WriteRead(simulating_spi, dat);
    }
    else
    {
        switch (spi_if->_if.spi)
        {
            case B_HAL_SPI_1:

                break;
            default:
                break;
        }
    }
    return tmp;
}

static int _SpiSend(bHalSPIIf_t *spi_if, const uint8_t *pbuf, uint16_t len)
{
    int i = 0;
    if (IS_NULL(spi_if) || IS_NULL(pbuf))
    {
        return -1;
    }
    for (i = 0; i < len; i++)
    {
        _SpiTransfer(spi_if, pbuf[i]);
    }
    return 0;
}

static int _SpiReceive(bHalSPIIf_t *spi_if, uint8_t *pbuf, uint16_t len)
{
    int i = 0;
    if (IS_NULL(spi_if) || IS_NULL(pbuf))
    {
        return -1;
    }
    for (i = 0; i < len; i++)
    {
        pbuf[i] = _SpiTransfer(spi_if, 0xff);
    }
    return 0;
}

bHalSPIDriver_t bHalSPIDriver = {
    .pSetSpeed = _SpiSetSpeed,
    .pSend     = _SpiSend,
    .pReceive  = _SpiReceive,
    .pTransfer = _SpiTransfer,
};

#endif

/************************ Copyright (c) 2020 Bean *****END OF FILE****/
