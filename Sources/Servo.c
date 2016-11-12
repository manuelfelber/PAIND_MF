/*
 * Servo.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */


#include "Robo.h"
#include "Application.h"
#include "FRTOS1.h"

static void ServoTask(void *pvParameters){
	for(;;){
		//FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
		walk(2,1200,FORWARD);
		//FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
		turn(4,1200,FORWARD);
	}
}


void Servo_Init(void){
  if (FRTOS1_xTaskCreate(ServoTask, "Servo", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} //error
  }
}


void Servo_Deinit(void){
}

