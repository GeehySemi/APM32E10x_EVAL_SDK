/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.0
 *
 * @date        2022-09-30
 *
 * @attention
 *
 *  Copyright (C) 2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "main.h"

/** @addtogroup Examples
  * @brief USB HID examples
  @{
  */

/** @addtogroup USB_HID
  @{
  */

/** @defgroup USB_HID_Macros Macros
  @{
*/


typedef enum {FALSE, TRUE} BOOL;

/* printf using USART1  */
#define DEBUG_USART           USART1

/**@} end of group USB_HID_Macros*/

/** @defgroup USB_HID_Variables Variables
  @{
  */

/* Timer tick */
uint16_t cntTick = 0;

/* Menu title string*/
const char *menuTitleStr[] =
{
    "    USB HID Example   ",
};

/* Menu item string*/
const char *menuItemStr[] =
{
    "KEY1 to Right key",
    "KEY2 to Left key",
    "KEY3 to UP key",
};

/* Menu bottom column string*/
const char *menuBottomColStr[] =
{
    "   GEEHY SEMICONDUCTOR   ",
};

/**@} end of group USB_HID_Variables*/

/** @defgroup USB_HID_Functions Functions
  @{
  */

void APM_EVAL_Init(void);

/* Test USB HID */
void APM_USB_HID_Init(void);

void Menu_DisplayInit(void);
void APM_EVAL_TMR7_Init(uint16_t period, uint16_t div);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    APM_EVAL_Init();
    printf("This is an example of USB HID \r\n");

    while(1)
    {
        HidMouse_Proc();
    }
}

/*!
 * @brief       Init EVAL board
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_EVAL_Init(void)
{
    USART_Config_T usartConfigStruct;

    /* Init delay function */
    APM_EVAL_DelayInit();

    APM_EVAL_LEDInit(LED1);
    APM_EVAL_LEDInit(LED2);
    APM_EVAL_LEDInit(LED3);

    APM_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
    APM_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_GPIO);
    APM_EVAL_PBInit(BUTTON_KEY3, BUTTON_MODE_GPIO);

    usartConfigStruct.baudRate = 115200;
    usartConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    usartConfigStruct.mode = USART_MODE_TX_RX;
    usartConfigStruct.parity = USART_PARITY_NONE;
    usartConfigStruct.stopBits = USART_STOP_BIT_1;
    usartConfigStruct.wordLength = USART_WORD_LEN_8B;
    APM_EVAL_COMInit(COM1, &usartConfigStruct);

    APM_EVAL_TMR7_Init(1000, 72);

    APM_LCDInit();
    LCD_Clear(0, 0, LCD_WIDTH, LCD_HEIGHT, LCD_BCOLOR);

    APM_USB_HID_Init();

    APM_EVAL_DelayMs(100);

    Menu_DisplayInit();
}

/*!
 * @brief       Write and read EEPROM
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void APM_USB_HID_Init(void)
{
    GPIO_Config_T gpioConfigStruct;

    /* Enable USB Connect Pin Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOE);

    gpioConfigStruct.mode = GPIO_MODE_OUT_PP;
    gpioConfigStruct.pin = GPIO_PIN_14;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOE, &gpioConfigStruct);

    /* Enable USB Connect */
    GPIO_ResetBit(GPIOE, GPIO_PIN_14);

    /* HID mouse init */
    HidMouse_Init();
}

/*!
 * @brief       Initialize the Menu UI
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void Menu_DisplayInit(void)
{
    /* Menu title*/
    LCD_Clear(0, 0, LCD_WIDTH, 40, LCD_FCOLOR);
    LCD_DisplayString(20, LCD_LINE_TITLE, menuTitleStr[0], LCD_TEXT_SELECT_FC, LCD_TEXT_SELECT_BC, 16, 0);

    /* Menu item*/
    LCD_DisplayString(20, LCD_LINE_0, "ID Vendor =  0x314B", LCD_TEXT_FC, LCD_TEXT_BC, 16, 0);
    LCD_DisplayString(20, LCD_LINE_1, "ID Product = 0x0107", LCD_TEXT_FC, LCD_TEXT_BC, 16, 0);
    LCD_DisplayString(20, LCD_LINE_3, menuItemStr[0], LCD_TEXT_FC, LCD_TEXT_BC, 16, 0);
    LCD_DisplayString(20, LCD_LINE_4, menuItemStr[1], LCD_TEXT_FC, LCD_TEXT_BC, 16, 0);
    LCD_DisplayString(20, LCD_LINE_5, menuItemStr[2], LCD_TEXT_FC, LCD_TEXT_BC, 16, 0);

    /* Menu bottom*/
    LCD_Clear(0, LCD_LINE_BOTTOM, LCD_WIDTH, LCD_HEIGHT, LCD_FCOLOR);
    LCD_DisplayString(60, LCD_LINE_BOTTOM, menuBottomColStr[0], LCD_TEXT_SELECT_FC, LCD_TEXT_SELECT_BC, 16, 0);
}

/*!
 * @brief       TMR7 init
 *
 * @param       None
 *
 * @retval      None
 *
 */
void APM_EVAL_TMR7_Init(uint16_t period, uint16_t div)
{
    TMR_BaseConfig_T  timeBaseConfig;

    /* Enable Clock*/
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR7);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CLOCK_DIV_1;
    /* Up-counter */
    timeBaseConfig.countMode =  TMR_COUNTER_MODE_UP;
    /* Set divider */
    timeBaseConfig.division = div - 1 ;
    /* Set counter = 0xffff */
    timeBaseConfig.period = period - 1;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;

    TMR_ConfigTimeBase(TMR7, &timeBaseConfig);

    /* Enable update interrupt*/
    TMR_EnableInterrupt(TMR7, TMR_INT_UPDATE);
    NVIC_EnableIRQRequest(TMR7_IRQn, 2, 2);

    /* Enable TMR7  */
    TMR_Enable(TMR7);
}

/*!
 * @brief       TMR4 interrupt service runtine
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into TMR7_IRQHandler() in apm32f0xx_int.c
 */
void TMR7_Isr(void)
{
    if (TMR_ReadIntFlag(TMR7, TMR_INT_UPDATE) == SET)
    {
        TMR_ClearIntFlag(TMR7, TMR_INT_UPDATE);
        cntTick++;

        if (cntTick >= 500)
        {
            cntTick = 0;
            APM_EVAL_LEDToggle(LED1);
        }
    }
}

/*!
 * @brief       Redirect C Library function printf to serial port.
 *              After Redirection, you can use printf function.
 *
 * @param       ch:  The characters that need to be send.
 *
 * @param       *f:  pointer to a FILE that can recording all information
 *              needed to control a stream
 *
 * @retval      The characters that need to be send.
 */
int fputc(int ch, FILE *f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

/**@} end of group USB_HID_Functions */
/**@} end of group USB_HID */
/**@} end of group Examples */
