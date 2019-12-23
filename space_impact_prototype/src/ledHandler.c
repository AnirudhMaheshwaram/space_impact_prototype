/* LED Red task/thread */
static void vLEDTaskRed(void *pvParameters)
{
	colour_t *colourCS;
	colourCS = (colour_t *) pvParameters;
	palette_t		col = colourCS[Red].colour;
	portTickType	numticks = colourCS[Red].delayTicks;
	portTickType	xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		Board_LED_Set(col, true);
		vTaskDelayUntil(&xLastWakeTime, numticks);
		Board_LED_Set(col, false);
		vTaskDelayUntil(&xLastWakeTime, (numticks << 1));
	}
}

/* LED Green task/thread */
static void vLEDTaskGreen(void *pvParameters)
{
	colour_t *colourCS;
	colourCS = (colour_t *) pvParameters;
	palette_t		col = colourCS[Green].colour;
	portTickType	numticks = colourCS[Green].delayTicks;
	portTickType	xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, numticks);
		Board_LED_Set(col, true);
		vTaskDelayUntil(&xLastWakeTime, numticks);
		Board_LED_Set(col, false);
		vTaskDelayUntil(&xLastWakeTime, numticks);
	}
}

/* LED Green task/thread */
static void vLEDTaskBlue(void *pvParameters)
{
	colour_t *colourCS;
	colourCS = (colour_t *) pvParameters;
	palette_t		col = colourCS[Blue].colour;
	portTickType	numticks = colourCS[Blue].delayTicks;
	portTickType	xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, (numticks << 1));
		Board_LED_Set(col, true);
		vTaskDelayUntil(&xLastWakeTime, numticks);
		Board_LED_Set(col, false);
	}
}
