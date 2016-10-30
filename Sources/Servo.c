/*
 * Servo.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */


#include "Huft_L.h"
#include "Huft_R.h"
#include "Knie_L.h"
#include "Knie_R.h"
#include "Knie_R.h"

#include "WAIT1.h"

#include "Application.h"
#include "FRTOS1.h"

static void ServoTask(void *pvParameters){
	for(;;){
		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	}
}


void Servo_Init(void){
  if (FRTOS1_xTaskCreate(ServoTask, "Servo", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}


void Servo_Deinit(void){
}

