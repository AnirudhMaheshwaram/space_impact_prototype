/*
 * uartFunctions.h
 *
 *  Created on: Dec. 17, 2019
 *      Author: anirudh
 */
#ifndef UARTFUNCTIONS_H_
#define UARTFUNCTIONS_H_

#include <string.h>

#include "chip.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

#define UART_SELECTION 	LPC_UART3
#define IRQ_SELECTION 	UART3_IRQn
#define UART_HANDLER 	UART3_IRQHandler

/* Transmit and receive ring buffers */
extern RINGBUFF_T txring, rxring;

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 32	/* Receive */

/* Transmit and receive buffers */
extern uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];


void vTaskUART(void *pvParameters);
void vSendMessage(char msg);
void uartDinit();

#endif /* UARTFUNCTIONS_H_ */
