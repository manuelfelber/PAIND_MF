/*
 * accMonotoring.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */

#include "accMonitoring.h"
#include "Power6V.h"
#include "oscillator.h"


static AkkMonStateType akkMonState; /* state machine state */

void initAccMonitoring(void){
	akkMonState = STATE_INIT;
	if (FRTOS1_xTaskCreate(AccMonitoringTask, "AccMonitoring", configMINIMAL_STACK_SIZE-60, NULL, tskIDLE_PRIORITY+3, NULL) != pdPASS) {
		for(;;){} //error
	}
}

void AccMonSetAlarm(){
	CS1_CriticalVariable();
	CS1_EnterCritical();
	akkMonState = STATE_FALL;
	CS1_ExitCritical();
	Power6V_ClrVal();
	enableGuard();
}

void AccMonClearAlarm(){
	CS1_CriticalVariable();
	CS1_EnterCritical();
	akkMonState = STATE_UPRIGHT;
	CS1_ExitCritical();
	Power6V_SetVal();
	disableGuard();
}

uint16_t AccMonMeasure(){
	int16_t xVal = 0;
	int16_t yVal = 0;
	int16_t zVal = 0;
	//uint8_t buf[6];
	//xVal =  MMA1_GetX();
	//yVal =  MMA1_GetY();
	zVal =  MMA1_GetZ();
	//FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
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
	int16_t zVal = 4000;
	int res = ERR_FAILED;

	for(;;){
		switch(akkMonState){
		case STATE_INIT:
			//init Acc Sensor
			res = MMA1_Init();
			if(res != ERR_OK){
				for(;;){} //Error
			}
			MMA1_CalibrateZ1g();
			akkMonState = STATE_UPRIGHT;
			break;
		case STATE_UPRIGHT:
			Buzzer_ClrVal();
			zVal = AccMonMeasure();
			if(zVal < 2000){
				AccMonSetAlarm();
			}
			break;
		case STATE_FALL:
			Power6V_ClrVal();
			enableGuard();
			Buzzer_SetVal();
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			Buzzer_ClrVal();
			FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			break;

		}
		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	}
}
