/*
 * Application.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */
#include "Application.h"				
#include "Huft_L.h"
#include "Huft_R.h"
#include "Knie_L.h"
#include "Knie_R.h"

#include "WAIT1.h"
#include "ROT.h"
#include "GRUN.h"
#include "BLAU.h"

#include "FRTOS1.h"
#include "Shell.h"
#include "Ultrasonic.h"
#include "LedControl.h"
#include "GPIO.h"
#include "Servo.h"
#include "SdCard.h"


static portTASK_FUNCTION(mainApp, pvParameters) {
  (void)pvParameters; /* parameter not used */

  //parse file
  initSdCard();

  for(;;) {
	//ultrasonic mesure distance
	//Measure();

	//show moving eye
	/*for(int i = 0; i < 2;i++) {
		FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
		LedShowEye(i);
	}*/
	//FRTOS1_taskYIELD();
	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void APP_Run(void){
	SHELL_Init();
	LedInit();
	US_Init();
	GPIO_Init();
	Servo_Init();

	ROT_Off();
	GRUN_Off();
	BLAU_Off();

	if (FRTOS1_xTaskCreate(
		mainApp,  /* pointer to the task */
		"MainAPP", /* task name for kernel awareness debugging */
		configMINIMAL_STACK_SIZE, /* task stack size */
		(void*)NULL, /* optional task startup argument */
		tskIDLE_PRIORITY+1,  /* initial priority */
		(xTaskHandle*)NULL /* optional task handle to create */
	  ) != pdPASS) {
	/*lint -e527 */
	for(;;){}; /* error! probably out of memory */
	/*lint +e527 */
	}
	FRTOS1_vTaskStartScheduler();

	for(;;) {}
}
