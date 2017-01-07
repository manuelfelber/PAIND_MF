/*
 * Application.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */
#include "Application.h"				

xSemaphoreHandle semLed, semUltrasonic;

static portTASK_FUNCTION(mainApp, pvParameters) {
	(void)pvParameters; /* parameter not used */

	//wait for users mode decicion
	FRTOS1_vTaskDelay(3000/portTICK_RATE_MS);

	//parse file
	if(getMode() == MODE_SDCARD){
		SDCardParse();
	}

	if(getMode() == MODE_DEMO){
		//setDistance(40);
		//setTrigger();
		while(1){
			walk(3,PERIODE, 1);
			turn(4, PERIODE, 1);
		}
	}

	for(;;) {
	    Huft_L_SetPWMDutyUs(0);
	    Huft_R_SetPWMDutyUs(0);
		Fuss_R_SetPWMDutyUs(0);
		Fuss_L_SetPWMDutyUs(0);

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

	semUltrasonic = xSemaphoreCreateBinary();
	if (semUltrasonic==NULL) { /* semaphore creation failed */
		for(;;){} /* error */
	}
	vQueueAddToRegistry(semUltrasonic, "Semaphore Ultrasonic");

	changeMode(MODE_SDCARD);

	//Power6V_SetVal();
	SHELL_Init();
	LedInit();
	US_Init();
	initAccMonitoring();
	initLowVoltage();

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
