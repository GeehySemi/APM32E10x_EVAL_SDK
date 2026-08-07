/*!
 * @file        main.h
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

/* Define to prevent recursive inclusion */
#ifndef __MAIN_H
#define __MAIN_H

/* Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Board.h"
#include "apm32e10x.h"
#include "apm32e10x_adc.h"
#include "apm32e10x_dma.h"
#include "apm32e10x_i2c.h"
#include "apm32e10x_eint.h"
#include "apm32e10x_rcm.h"
#include "apm32e10x_gpio.h"
#include "apm32e10x_usart.h"
#include "apm32e10x_misc.h"
#include "apm32e10x_tmr.h"
#include "apm32e10x_spi.h"

#include "usbd_hid.h"

#include "bsp_lcd.h"
#include "bsp_key.h"
#include "bsp_delay.h"
#include "bsp_i2c_ee.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup I2C_EEPROM
  @{
  */

/** @defgroup I2C_EEPROM_Functions Functions
  @{
  */
void TMR7_Isr(void);
void LCD_HomePageHandle(uint8_t menuState);
void LCD_MenuLevel1Handle(uint8_t menuState);
void LCD_MenuLevel2Handle(uint8_t menuState);
void LCD_MenuLevel3Handle(uint8_t menuState);
/** @addtogroup Examples
  @{
  */

/** @addtogroup I2C_EEPROM
  @{
  */

#endif

/**@} end of group I2C_EEPROM */
/**@} end of group Examples */


