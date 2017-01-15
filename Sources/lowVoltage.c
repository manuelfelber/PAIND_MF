/*
 * lowVoltage.c
 *
 *  Created on: 02.12.2016
 *      Author: Manuel
 */

#include "lowVoltage.h"

static portTASK_FUNCTION(lowVoltage, pvParameters) {
	(void)pvParameters; /* parameter not used */
	for(;;) {
		//mesure Battery Level
		uint16_t value = 0;
		ANALOG_IN_Measure(TRUE);
		ANALOG_IN_GetValue16(&value);
		float voltage = (float)value * (3.3/65536.0) * (1830.0/820.0)+1.5;
		if(voltage < 7.7){
			//show "low Voltage" on eyes
			LedSetLowBat();
		}

		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	}
}


void initLowVoltage(){
	if (FRTOS1_xTaskCreate(
		lowVoltage,  /* pointer to the task */
		"LowVoltage", /* task name for kernel awareness debugging */
		configMINIMAL_STACK_SIZE-60, /* task stack size */
		(void*)NULL, /* optional task startup argument */
		tskIDLE_PRIORITY,  /* initial priority */
		(xTaskHandle*)NULL /* optional task handle to create */
	  ) != pdPASS) {
	/*lint -e527 */
	for(;;){}; /* error! probably out of memory */
	/*lint +e527 */
	}
}
