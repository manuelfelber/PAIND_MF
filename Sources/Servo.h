/*
 * Servo.h
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */

#ifndef SOURCES_SERVO_H_
#define SOURCES_SERVO_H_

static void ServoTask(void *pvParameters);
void Servo_Init(void);
void Servo_Deinit(void);

#define SERVO_PARSE_COMMAND_ENABLED 1


#endif /* SOURCES_SERVO_H_ */
