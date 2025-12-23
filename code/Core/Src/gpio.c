/**************************************************************************
 --  STM32N6 3.5inch Arduino 8BIT Module MAR3501 Display gpio setup for 8080
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


#include "gpio.h"


void MX_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, LCD_WR_Pin | LCD_RST_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, LCD_D3_Pin | LCD_D5_Pin | LCD_D7_Pin | LCD_D4_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, LCD_D0_Pin | LCD_D2_Pin | LCD_D6_Pin | LCD_D1_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOF, LCD_RS_Pin | LCD_RD_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : LCD_WR_Pin */
	GPIO_InitStruct.Pin = LCD_WR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(LCD_WR_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LCD_D3_Pin LCD_D5_Pin LCD_D7_Pin LCD_D4_Pin */
	GPIO_InitStruct.Pin = LCD_D3_Pin | LCD_D5_Pin | LCD_D7_Pin | LCD_D4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : LCD_RST_Pin */
	GPIO_InitStruct.Pin = LCD_RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LCD_D0_Pin LCD_D2_Pin LCD_D6_Pin LCD_D1_Pin */
	GPIO_InitStruct.Pin = LCD_D0_Pin | LCD_D2_Pin | LCD_D6_Pin | LCD_D1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : LCD_RS_Pin LCD_RO_Pin */
	GPIO_InitStruct.Pin = LCD_RS_Pin | LCD_RD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/*Configure GPIO pin : LCD_CS_Pin */
	GPIO_InitStruct.Pin = LCD_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_CS_GPIO_Port, &GPIO_InitStruct);

}

