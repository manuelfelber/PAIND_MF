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
#include "SdCard.h"
#include "Buzzer.h"
#include "accMonitoring.h"
#include "lowVoltage.h"
#include "Power6V.h"

xSemaphoreHandle semLed;

static portTASK_FUNCTION(mainApp, pvParameters) {
	(void)pvParameters; /* parameter not used */

	//parse file
	SDCardParse();

	for(;;) {
	    /*Huft_L_SetPWMDutyUs(0);
	    Huft_R_SetPWMDutyUs(0);
		Fuss_R_SetPWMDutyUs(0);
		Fuss_L_SetPWMDutyUs(0);*/

		//switch off 6V
		//Power6V_ClrVal();
		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void APP_Run(void){
	semLed = xSemaphoreCreateBinary();
	if (semLed==NULL) { /* semaphore creation failed */
		for(;;){} /* error */
	}
	vQueueAddToRegistry(semLed, "Semaphore DotMatrix");

	//Power6V_SetVal();
	SHELL_Init();
	LedInit();
	//US_Init();
	//initAccMonitoring();
	//initLowVoltage();

	Buzzer_ClrVal();
	ROT_Off();
	GRUN_Off();
	BLAU_Off();

	if (FRTOS1_xTaskCreate(
		mainApp,  /* pointer to the task */
		"MainAPP", /* task name for kernel awareness debugging */
		configMINIMAL_STACK_SIZE+50, /* task stack size */
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
