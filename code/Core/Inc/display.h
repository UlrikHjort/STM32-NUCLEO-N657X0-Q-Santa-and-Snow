/**************************************************************************
 --  STM32N6 3.5inch Arduino 8BIT Module MAR3501 Display driver (write only)
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
#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "gpio.h"
#include <stdint.h>

#define LCD_HEIGHT 320
#define LCD_WIDTH 480



#define LCD_CS_CLR GPIOA->BRR = LCD_CS_Pin
#define LCD_CS_SET GPIOA->BSRR = LCD_CS_Pin

#define LCD_RD_CLR GPIOF->BRR = LCD_RD_Pin
#define LCD_RD_SET GPIOF->BSRR = LCD_RD_Pin

#define LCD_RS_CLR GPIOF->BRR = LCD_RS_Pin
#define LCD_RS_SET GPIOF->BSRR = LCD_RS_Pin

#define LCD_RST_CLR GPIOC->BRR = LCD_RST_Pin
#define LCD_RST_SET GPIOC->BSRR = LCD_RST_Pin

#define LCD_WR_CLR GPIOC->BRR = LCD_WR_Pin
#define LCD_WR_SET GPIOC->BSRR = LCD_WR_Pin



void display_init();
void lcd_draw_pixel(uint16_t x, uint16_t y, uint16_t color);


void lcd_draw_area(uint16_t start_x, uint16_t start_y, uint16_t width, uint16_t height, uint32_t *buffer);
void lcd_clear(uint16_t color, uint16_t width, uint16_t height);
void lcd_clear_area(uint16_t start_x, uint16_t start_y, uint16_t width, uint16_t height, uint16_t color);
void lcd_set_window(uint16_t x_start, uint16_t y_start,uint16_t x_end,uint16_t y_end);


#endif /* INC_DISPLAY_H_ */
