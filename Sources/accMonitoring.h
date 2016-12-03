/*
 * accMonitoring.h
 *
 *  Created on: 28.11.2016
 *      Author: Manuel
 */
#ifndef __AccMonitoring_H
#define __AccMonitoring_H

#include "FRTOS1.h"
#include "MMA1.h"
#include "CLS1.h"
#include "Buzzer.h"

typedef enum {
  STATE_INIT,
  STATE_UPRIGHT,
  STATE_FALL,
} AkkMonStateType;

void initAccMonitoring(void);
static void AccMonitoringTask(void *pvParameters);
void AccMonClearAlarm(void);
void AccMonSetAlarm(void);

#endif
/* ifndef __AccMonitoring_H*/
