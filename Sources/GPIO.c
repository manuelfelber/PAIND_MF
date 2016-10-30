/*
 * Pins.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */
#include "WAIT1.h"
#include "Application.h"
#include "FRTOS1.h"

#include "ROT.h"
#include "GRUN.h"
#include "BLAU.h"

#include "Buzzer.h"
#include "Switch_A.h"
#include "Switch_B.h"
#include "ANALOG_IN.h"

#include "GPIO.h"


static uint16_t value;

static void GPIOTask(void *pvParameters){
	for(;;){
		//ANALOG_IN_Measure(TRUE);
		//ANALOG_IN_GetValue16(&value);
		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	}
}


void GPIO_Init(void){
  if (FRTOS1_xTaskCreate(GPIOTask, "GPIOs", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


void GPIO_Deinit(void){

}
