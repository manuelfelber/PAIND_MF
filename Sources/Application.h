/*
 * Application.h
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

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

void APP_Run(void);
extern xSemaphoreHandle semLed;
extern xSemaphoreHandle semUltrasonic;
extern xSemaphoreHandle mutRoboGuard;

#endif /* SOURCES_APPLICATION_H_ */
