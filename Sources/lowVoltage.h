/*
 * lowVoltage.h
 *
 *  Created on: 02.12.2016
 *      Author: Manuel
 */

#ifndef SOURCES_LOWVOLTAGE_H_
#define SOURCES_LOWVOLTAGE_H_

#include "ANALOG_IN.h"
#include "FRTOS1.h"
#include "LedControl.h"

void initLowVoltage(void);
static portTASK_FUNCTION(lowVoltage, pvParameters);


#endif /* SOURCES_LOWVOLTAGE_H_ */
