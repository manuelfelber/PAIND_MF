/*
 * accMonotoring.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */

#include "accMonitoring.h"
#include "MMA1.h"
#include "CLS1.h"
#include "Buzzer.h"

//static xTaskHandle AccMonTaskHandle;
//static xSemaphoreHandle AccMonSem = NULL;

typedef enum {
  STATE_INIT,
  STATE_UPRIGHT,
  STATE_FALL,
} AkkMonStateType;

static volatile AkkMonStateType akkMonState = STATE_INIT; /* state machine state */

void initAccMonitoring(void){
	if (FRTOS1_xTaskCreate(AccMonitoringTask, "AccMonitoring", configMINIMAL_STACK_SIZE-60, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
		for(;;){} //error
	}
}

void AccMonSetAlarm(){
	//(void)xTaskNotify(AccMonTaskHandle, ACCMON_SET_ALARM, eSetBits);
	akkMonState = STATE_FALL;
}

void AccMonClearAlarm(){
	//(void)xTaskNotify(AccMonTaskHandle, ACCMON_CLEAR_ALARM, eSetBits);
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
}

static void AccMonitoringTask(void *pvParameters){
	//uint32_t notifcationValue;
	//bool alarm = FALSE;
	uint16_t zVal = 0xFFFF;
	int res = ERR_FAILED;

	for(;;){
		switch(akkMonState)
		{
		case STATE_INIT:
			/*//init binary Semaphore
			FRTOS1_vSemaphoreCreateBinary(AccMonSem);
			if (AccMonSem==NULL) {
				for(;;){}
			}
			(void)FRTOS1_xSemaphoreTake(AccMonSem, 0);
			FRTOS1_vQueueAddToRegistry(AccMonSem, "AccMonSem");*/

			//init Acc Senor
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
			if(zVal < 500){
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
	}
}
