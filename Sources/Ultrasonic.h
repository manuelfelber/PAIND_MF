/*
 * Ultrasonic.h
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "PE_LDD.h"
#include "TU3.h"
#include "WAIT1.h"
#include "CLS1.h"

typedef enum {
  ECHO_IDLE, /* device not used */
  ECHO_TRIGGERED, /* started trigger pulse */
  ECHO_MEASURE, /* measuring echo pulse */
  ECHO_OVERFLOW, /* measurement took too long */
  ECHO_FINISHED /* measurement finished */
} US_EchoState;

typedef struct {
  LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
  LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
  volatile US_EchoState state; /* state */
  TU3_TValueType capture; /* input capture value */
} US_DeviceType;

/* 
 * \brief Called in case of an overflow during input capture. This function is called from an interrupt!
 * \param UserDataPtr Pointer to user structure
 */
void US_EventEchoOverflow(LDD_TUserData *UserDataPtr);

/*
 * \brief Called by the input capture interrupt for a raising or falling edge of the Echo pin
 * \param UserDataPtr Pointer to user structure
 */
void US_EventEchoCapture(LDD_TUserData *UserDataPtr);

/* 
 * \brief Convert measured microseconds to centimeters.
 * \param[in] temperatureCelsius Air temperature in degree Celsius
 */
uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius);

static uint16_t calcAirspeed_dms(uint8_t temperatureCelsius);

uint16_t US_Measure_us(void);

uint16_t US_Measure(void);

/*
 * \brief Driver initialization routine.
 */
void US_Init(void);
static void USTrgCallback(void);


#endif /* ULTRASONIC_H_ */
