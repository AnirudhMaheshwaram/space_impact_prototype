/*
 * space_impact_prototype.c
 *
 *  Created on: Dec. 4, 2019
 *      Author: anirudh
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "linkedlist.h"
#include "definations.h"
#include "gameObjectHandlers.h"
#include "uartFunctions.h"
/*****************************************************************************
 *functions*
 ****************************************************************************/


/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	uartInt();
	/* Configure GPIO interrupt pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, JOYSTICK_UP_GPIO_PORT_NUM, JOYSTICK_UP_GPIO_BIT_NUM);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, JOYSTICK_DOWN_GPIO_PORT_NUM, JOYSTICK_DOWN_GPIO_BIT_NUM);

	/* Configure the GPIO interrupt
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, JOYSTICK_UP_GPIO_PORT_NUM, 1 << JOYSTICK_UP_GPIO_BIT_NUM);
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, JOYSTICK_DOWN_GPIO_PORT_NUM, 1 << JOYSTICK_DOWN_GPIO_BIT_NUM);
	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME2);
	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME2);
	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME3);
	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME3);
	/* Initial state for each LED is off */
	Board_LED_Set(Red, false);
	Board_LED_Set(Green, false);
	Board_LED_Set(Blue, false);
}


void GPIO_IRQ_HANDLER2(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);
	//Board_LED_Toggle(0);

}

void GPIO_IRQ_HANDLER3(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);
	//Board_LED_Toggle(2);
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	/* initialize hardware */
		prvSetupHardware();
		taskParam taskParameter;
		intializeTaskParam(*taskParameter);
		/*player task*/
		xTaskCreate(vPlayerTask, (signed char *) "PlayerTask",
				configMINIMAL_STACK_SIZE, taskParameter, (tskIDLE_PRIORITY + 4UL),
						(xTaskHandle *) NULL);
		/*Enemy task*/
		xTaskCreate(vTaskEmeny, (signed char *) "EnemiesTask",
				configMINIMAL_STACK_SIZE, taskParameter, (tskIDLE_PRIORITY + 1UL),
						(xTaskHandle *) NULL);
		/*Bullet task*/
		xTaskCreate(vTaskBullets, (signed char *) "BulletsTask",
				configMINIMAL_STACK_SIZE, taskParameter, (tskIDLE_PRIORITY + 2UL),
						(xTaskHandle *) NULL);
		/*game object handler*/
		xTaskCreate(vTaskgameObjectHandler, (signed char *) "gameObjectTask",
				configMINIMAL_STACK_SIZE, taskParameter, (tskIDLE_PRIORITY + 3UL),
						(xTaskHandle *) NULL);
		/*game object position update task*/
		xTaskCreate(vTaskGOPosition, (signed char *) "gameObjectTask",
				configMINIMAL_STACK_SIZE, taskParameter, (tskIDLE_PRIORITY + 2UL),
						(xTaskHandle *) NULL);
		/*UART position*/
		xTaskCreate(vTaskUart, (signed char *) "UartTask",
				configMINIMAL_STACK_SIZE, taskParameter, (tskIDLE_PRIORITY + 3UL),
						(xTaskHandle *) NULL);
		vTaskStartScheduler();
		uartDinit();

}

/**
 * @}
 */
