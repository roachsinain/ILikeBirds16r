/**
 *!
 * \file        mcu_n32l40x_gpio.c
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SGPIOL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 */

/*Includes ----------------------------------------------*/
#include "b_config.h"
#include "hal/inc/b_hal_gpio.h"

#if (defined(NATION_L40X))

//         Register Address

#define GPIO_REG_OFF (0x400UL)
#define GPIO_REG_BASE (0x40010800UL)

typedef struct
{
    volatile uint32_t PMODE;  /*offset 0x00*/
    volatile uint32_t POTYPE; /*offset 0x04*/
    volatile uint32_t SR;     /*offset 0x08*/
    volatile uint32_t PUPD;   /*offset 0x0C*/
    volatile uint32_t PID;    /*offset 0x10*/
    volatile uint32_t POD;    /*offset 0x14*/
    volatile uint32_t PBSC;   /*offset 0x18*/
    volatile uint32_t PLOCK;  /*offset 0x1C*/
    volatile uint32_t AFL;    /*offset 0x20*/
    volatile uint32_t AFH;    /*offset 0x24*/
    volatile uint32_t PBC;    /*offset 0x28*/
    volatile uint32_t DS;     /*offset 0x2C*/
} McuGpioReg_t;

void bMcuGpioConfig(bHalGPIOPort_t port, bHalGPIOPin_t pin, bHalGPIODir_t dir, bHalGPIOPull_t pull)
{
    uint32_t      dir_val  = 0;
    uint32_t      pull_val = 0;
    McuGpioReg_t *pGpio    = (McuGpioReg_t *)(GPIO_REG_BASE + port * GPIO_REG_OFF);
    if (!B_HAL_GPIO_ISVALID(port, pin) || (port > B_HAL_GPIOD))
    {
        return;
    }
    if (dir == B_HAL_GPIO_OUTPUT)
    {
        dir_val = (pin == B_HAL_PINAll) ? 0x55555555 : 1;
    }
    if (pull == B_HAL_GPIO_PULLUP)
    {
        pull_val = (pin == B_HAL_PINAll) ? 0x55555555 : 1;
    }
    else if (pull == B_HAL_GPIO_PULLDOWN)
    {
        pull_val = (pin == B_HAL_PINAll) ? 0xAAAAAAAA : 2;
    }

    if (pin == B_HAL_PINAll)
    {
        pGpio->PMODE = dir_val;
        pGpio->PUPD  = pull_val;
    }
    else
    {
        pGpio->PMODE &= ~(0x3 << (pin * 2));
        pGpio->PMODE |= (dir_val << (pin * 2));

        pGpio->PUPD &= ~(0x3 << (pin * 2));
        pGpio->PUPD |= (pull_val << (pin * 2));
    }
}

void bMcuGpioWritePin(bHalGPIOPort_t port, bHalGPIOPin_t pin, uint8_t s)
{
    uint32_t      cs_val = 0x1 << pin;
    McuGpioReg_t *pGpio  = (McuGpioReg_t *)(GPIO_REG_BASE + port * GPIO_REG_OFF);
    if (!B_HAL_GPIO_ISVALID(port, pin) || (port > B_HAL_GPIOD))
    {
        return;
    }
    if (s == 0)
    {
        cs_val <<= 16;
    }
    pGpio->PBSC = cs_val;
}

uint8_t bMcuGpioReadPin(bHalGPIOPort_t port, bHalGPIOPin_t pin)
{
    uint32_t      id_val = 0;
    McuGpioReg_t *pGpio  = (McuGpioReg_t *)(GPIO_REG_BASE + port * GPIO_REG_OFF);
    if (!B_HAL_GPIO_ISVALID(port, pin) || port > B_HAL_GPIOD || pin == B_HAL_PINAll)
    {
        return 0;
    }
    id_val = pGpio->PID;
    return ((id_val & (0x0001 << pin)) != 0);
}

void bMcuGpioWritePort(bHalGPIOPort_t port, uint16_t dat)
{
    McuGpioReg_t *pGpio = (McuGpioReg_t *)(GPIO_REG_BASE + port * GPIO_REG_OFF);
    if (port > B_HAL_GPIOD)
    {
        return;
    }
    pGpio->POD = dat;
}

uint16_t bMcuGpioReadPort(bHalGPIOPort_t port)
{
    uint32_t      id_val = 0;
    McuGpioReg_t *pGpio  = (McuGpioReg_t *)(GPIO_REG_BASE + port * GPIO_REG_OFF);
    if (port > B_HAL_GPIOD)
    {
        return 0;
    }
    id_val = pGpio->PID;
    return (id_val & 0xffff);
}

#endif
/************************ Copyright (c) 2020 Bean *****END OF FILE****/
