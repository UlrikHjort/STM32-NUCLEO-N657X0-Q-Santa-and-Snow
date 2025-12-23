/**************************************************************************
 --  STM32N6 3.5inch Arduino 8BIT Module MAR3501 Display Santa and snow
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

#include "main.h"
#include "gpio.h"
#include <stdio.h>
#include "xmas_main.h"


void SystemClock_Config(void);

int main(void) {

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();

	HAL_Delay(1000);
	display_init();
	run_xmas();
	while (1) {

	}

}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	if (HAL_PWREx_ConfigSupply(PWR_EXTERNAL_SOURCE_SUPPLY) != HAL_OK) {
		Error_Handler();
	}

	/* Enable HSI */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Get current CPU/System buses clocks configuration and if necessary switch
	 to intermediate HSI clock to ensure target clock can be set
	 */
	HAL_RCC_GetClockConfig(&RCC_ClkInitStruct);
	if ((RCC_ClkInitStruct.CPUCLKSource == RCC_CPUCLKSOURCE_IC1)
			|| (RCC_ClkInitStruct.SYSCLKSource == RCC_SYSCLKSOURCE_IC2_IC6_IC11)) {
		RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_CPUCLK
				| RCC_CLOCKTYPE_SYSCLK);
		RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_HSI;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
		if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK) {
			/* Initialization Error */
			Error_Handler();
		}
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
	RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL1.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL1.PLLM = 1;
	RCC_OscInitStruct.PLL1.PLLN = 25;
	RCC_OscInitStruct.PLL1.PLLFractional = 0;
	RCC_OscInitStruct.PLL1.PLLP1 = 1;
	RCC_OscInitStruct.PLL1.PLLP2 = 1;
	RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_CPUCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
			| RCC_CLOCKTYPE_PCLK5 | RCC_CLOCKTYPE_PCLK4;
	RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_HSI;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_IC2_IC6_IC11;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;
	RCC_ClkInitStruct.APB5CLKDivider = RCC_APB5_DIV1;
	RCC_ClkInitStruct.IC2Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
	RCC_ClkInitStruct.IC2Selection.ClockDivider = 4;
	RCC_ClkInitStruct.IC6Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
	RCC_ClkInitStruct.IC6Selection.ClockDivider = 4;
	RCC_ClkInitStruct.IC11Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
	RCC_ClkInitStruct.IC11Selection.ClockDivider = 4;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK) {
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	__disable_irq();
	while (1) {
	}
}

