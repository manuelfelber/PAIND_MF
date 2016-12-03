/*
 * accMonotoring.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */

#include "accMonitoring.h"



static volatile AkkMonStateType akkMonState; /* state machine state */

void initAccMonitoring(void){
	akkMonState = STATE_INIT;
	if (FRTOS1_xTaskCreate(AccMonitoringTask, "AccMonitoring", configMINIMAL_STACK_SIZE-60, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
		for(;;){} //error
	}
}

void AccMonSetAlarm(){
	akkMonState = STATE_FALL;
}

void AccMonClearAlarm(){
	akkMonState = STATE_UPRIGHT;
}

uint16_t AccMonMeasure(){
	uint16_t xVal = 0;
	uint16_t yVal = 0;
	uint16_t zVal = 0;
	uint8_t buf[6];
	xVal =  MMA1_GetX();
	yVal =  MMA1_GetY();
	zVal =  MMA1_GetZ();
	FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
	/*CLS1_SendStr("X:", CLS1_GetStdio()->stdOut);
	UTIL1_Num16uToStrFormatted(buf, sizeof(buf), xVal, ' ', 5);
	CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
	CLS1_SendStr("\tY:", CLS1_GetStdio()->stdOut);
	UTIL1_Num16uToStrFormatted(buf, sizeof(buf), yVal, ' ', 5);
	CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
	CLS1_SendStr("\tZ:", CLS1_GetStdio()->stdOut);
	UTIL1_Num16uToStrFormatted(buf, sizeof(buf), zVal, ' ', 5);
	CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
	CLS1_SendStr("\n", CLS1_GetStdio()->stdOut);*/
	return zVal;
}

static void AccMonitoringTask(void *pvParameters){
	uint16_t zVal = 0xFFFF;
	int res = ERR_FAILED;

	for(;;){
		switch(akkMonState){
		case STATE_INIT:
			//init Acc Sensor
			res = MMA1_Init();
			if(res != ERR_OK){
				for(;;){}
			}
			MMA1_CalibrateZ1g();
			akkMonState = STATE_UPRIGHT;
			break;
		case STATE_UPRIGHT:
			Buzzer_ClrVal();
			zVal = AccMonMeasure();
			if(zVal < 500 || zVal > 64000){
				AccMonSetAlarm();
			}
			break;
		case STATE_FALL:
			Buzzer_SetVal();
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			Buzzer_ClrVal();
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			break;

		}
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
	}
}
