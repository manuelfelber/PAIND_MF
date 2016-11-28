/*
 * accMonotoring.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */

#include "accMonitoring.h"
#include "MMA1.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "Buzzer.h"


void initAccMonitoring(void){
	if (FRTOS1_xTaskCreate(AccMonitoringTask, "AccMonitoring", configMINIMAL_STACK_SIZE-60, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
		for(;;){} //error
	}
}

static void AccMonitoringTask(void *pvParameters){
	int res = MMA1_Init();
	if(res != ERR_OK){
		for(;;){}
	}
	MMA1_CalibrateZ1g();
	for(;;){
		uint16_t xVal = 0;
		uint16_t yVal = 0;
		uint16_t zVal = 0;
		uint8_t buf[6];
		xVal =  MMA1_GetX();
		yVal =  MMA1_GetY();
		zVal =  MMA1_GetZ();
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
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

		if(zVal < 500){
			//Alarm
			while(1){
				Buzzer_SetVal();
				FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
				Buzzer_ClrVal();
				FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
			}

		}
	}
}
