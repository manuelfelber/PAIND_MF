/*
 * accMonitoring.h
 *
 *  Created on: 28.11.2016
 *      Author: Manuel
 */
#ifndef __AccMonitoring_H
#define __AccMonitoring_H

#include "FRTOS1.h"

void initAccMonitoring(void);
static void AccMonitoringTask(void *pvParameters);
void AccMonClearAlarm(void);
void AccMonSetAlarm(void);

//static xTaskHandle AccMonTaskHandle;

/* task notification bits */
#define ACCMON_SET_ALARM (1<<0)
#define ACCMON_CLEAR_ALARM (1<<1)

#endif
/* ifndef __AccMonitoring_H*/
