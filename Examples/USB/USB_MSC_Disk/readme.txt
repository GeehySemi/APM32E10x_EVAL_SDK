/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
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

&par Example Description

This example describes how to use the USB device module on APM32E103 to
enumerated as a MSC USB disk. This example use PC as host, and APM32E103 use
ram to simulate usb flash drives. PC will recognizes the motherboard as a
disk, and formatting the U disk. This example will be Used to test usb speed.

&par Directory contents

  - USB/USB_MSC_Disk/Source/apm32e10x_int.c     Interrupt handlers
  - USB/USB_MSC_Disk/Source/main.c              Main program

&par IDE environment

  - MDK-ARM V5.29
  - EWARM V8.50.5.26295

&par Hardware and Software environment

  - This example runs on APM32E103_EVAL Devices.
