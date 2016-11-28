/*
 * Servo.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */


#include "Robo.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Huft_L.h"
#include "Huft_R.h"
#include "Fuss_L.h"
#include "Fuss_R.h"

static void ServoTask(void *pvParameters){
	/*Fuss_L_SetPos(125);
	Fuss_R_SetPos(125);
	Huft_L_SetPos(125);
	Huft_R_SetPos(125);*/
	for(;;){
		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		walk(10,1200,FORWARD);
		//FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
		//turn(4,1200,FORWARD);
	}
}


void Servo_Init(void){
  /*if (FRTOS1_xTaskCreate(ServoTask, "Servo", configMINIMAL_STACK_SIZE-100, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} //error
  }*/
}


void Servo_Deinit(void){
}

