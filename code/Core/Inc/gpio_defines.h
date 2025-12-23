/**************************************************************************
 --        STM32N6 3.5inch Arduino 8BIT Module MAR3501 GPIO mapping
 --
 --           Copyright (C) 2025 By Ulrik Hørlyk Hjort
 --
 --  This Program is Free Software; You Can Redistribute It and/or
 --  Modify It Under The Terms of The GNU General Public License
 --  As Published By The Free Software Foundation; Either Version 2
 --  of The License, or (at Your Option) Any Later Version.
 --
 --  This Program is Distributed in The Hope That It Will Be Useful,
 --  But WITHOUT ANY WARRANTY; Without Even The Implied Warranty of
 --  MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See The
 --  GNU General Public License for More Details.
 --
 -- You Should Have Received A Copy of The GNU General Public License
 -- Along with This Program; if not, See <Http://Www.Gnu.Org/Licenses/>.
 ***************************************************************************/
#ifndef INC_GPIO_DEFINES_H_
#define INC_GPIO_DEFINES_H_

#define LCD_WR_Pin GPIO_PIN_10
#define LCD_WR_GPIO_Port GPIOC
#define LCD_D3_Pin GPIO_PIN_9
#define LCD_D3_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_10
#define LCD_D5_GPIO_Port GPIOE
#define LCD_RST_Pin GPIO_PIN_12
#define LCD_RST_GPIO_Port GPIOC
#define LCD_D0_Pin GPIO_PIN_12
#define LCD_D0_GPIO_Port GPIOD
#define LCD_D2_Pin GPIO_PIN_0
#define LCD_D2_GPIO_Port GPIOD
#define LCD_D6_Pin GPIO_PIN_5
#define LCD_D6_GPIO_Port GPIOD
#define LCD_D7_Pin GPIO_PIN_11
#define LCD_D7_GPIO_Port GPIOE
#define LCD_D1_Pin GPIO_PIN_7
#define LCD_D1_GPIO_Port GPIOD
#define LCD_D4_Pin GPIO_PIN_0
#define LCD_D4_GPIO_Port GPIOE
#define LCD_RS_Pin GPIO_PIN_6
#define LCD_RS_GPIO_Port GPIOF
#define LCD_RD_Pin GPIO_PIN_5
#define LCD_RD_GPIO_Port GPIOF
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOA

#endif /* INC_GPIO_DEFINES_H_ */
