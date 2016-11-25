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
#include "ANALOG_IN.h"
#include "Buzzer.h"


static portTASK_FUNCTION(mainApp, pvParameters) {
	(void)pvParameters; /* parameter not used */

	//parse file
	//initSdCard();

	for(;;) {
		//ultrasonic mesure distance
		//Measure();

		//mesure Battery Level
		/*uint16_t value = 0;
		ANALOG_IN_Measure(TRUE);
		ANALOG_IN_GetValue16(&value);
		float voltage = (float)value * 3.3 / 65536;*/

		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void APP_Run(void){
	SHELL_Init();
	LedInit();
	US_Init();
	Servo_Init();

	Buzzer_ClrVal();
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
