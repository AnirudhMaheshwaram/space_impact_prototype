/*
 * definations.h
 *
 *  Created on: Dec. 17, 2019
 *      Author: anirudh
 */
#include "linkedlist.h"
#ifndef DEFINATIONS_H_
#define DEFINATIONS_H_
/*****************************************************************************
 * Private types/enumerations/variables*
 ****************************************************************************/
#define JOYSTICK_UP_GPIO_PORT_NUM               GPIOINT_PORT2
#define JOYSTICK_UP_GPIO_BIT_NUM                12
#define JOYSTICK_DOWN_GPIO_PORT_NUM             GPIOINT_PORT2
#define JOYSTICK_DOWN_GPIO_BIT_NUM              13
#define framerate 								400

/* EINT2 vector. */
#define GPIO_IRQ_HANDLER2  			EINT2_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME2    EINT2_IRQn	/* GPIO interrupt NVIC interrupt name */

/* EINT3 vector. */
#define GPIO_IRQ_HANDLER 3 			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME3    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */


#define xAxisRes 								50  //number of vertical pixels
#define yAxisRes 								120 //number of horizontal pixels
#define xAxisSpeed 								0	//minimum vertical speed of GO //taken as 0 for intial version
#define yAxisSpeed 								4	//minimum horizontal speed of GO
#define intialPlayerxPosition					4
#define intialPlayeryPosition					4
#define UART_SELECTION 	LPC_UART3
#define IRQ_SELECTION 	UART3_IRQn
#define HANDLER_NAME 	UART3_IRQHandler


/* Transmit and receive ring buffers */
STATIC RINGBUFF_T txring, rxring;

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 32	/* Receive */

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];


struct player_STRUCT		//	struct for storing current player data
{
	const short id = 1;
	volatile short posx;
	volatile short posy;
	volatile short health;
};
typedef struct player_STRUCT player;
struct user_input_STRUCT	// struct for storing user input
{
	const short id = 10;
	volatile short up;
	volatile short down;
};
typedef struct user_input_STRUCT user_input_str;


struct task_param_struct
{
	volatile player * playerAddr;
	volatile user_input_str * userInputAddr;
	volatile Bool playerAlive;
	volatile xList * bulletsAddr;
	volatile xList * enemiesAddr;
};
typedef struct task_param_struct taskParam;

#endif /* DEFINATIONS_H_ */
