/*
 * Ultrasonic.c
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */
#include "Ultrasonic.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "LedControl.h"

#define DEBUG 1

static US_DeviceType usDevice; /* device handle for the ultrasonic device */

static portTASK_FUNCTION(UltrasonicTask, pvParameters) {
	for(;;){
		xSemaphoreTake(semUltrasonic,portMAX_DELAY);
		uint16_t distanceMeasured = US_Measure();
		if(distanceMeasured < distance && distanceMeasured != 0){
			switch(option){ //option choosen in textfile
			case 0:
				LedSetEmotions(EM_NEUTAL);
			    (void)xSemaphoreGive(semLed);
				break;
			case 1:
				turn(7, 1200, 1); //turn away from objekt
				break;
			}
		}
		else{
			LedSetEmotions(EM_HAPPY);
			(void)xSemaphoreGive(semLed);
		}
	}
}

void US_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;
  
  ptr->state = ECHO_OVERFLOW;
}

void US_EventEchoCapture(LDD_TUserData *UserDataPtr) {
  US_DeviceType *ptr = (US_DeviceType*)UserDataPtr;

  if (ptr->state==ECHO_TRIGGERED) { /* 1st edge, this is the raising edge, start measurement */
    TU3_ResetCounter(ptr->echoDevice);
    ptr->state = ECHO_MEASURE;
  } else if (ptr->state==ECHO_MEASURE) { /* 2nd edge, this is the falling edge: use measurement */
    (void)TU3_GetCaptureValue(ptr->echoDevice, 0, &ptr->capture);
    ptr->state = ECHO_FINISHED;
  }
}

uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius) {
  return (microseconds*100UL)/calcAirspeed_dms(temperatureCelsius)/2; /* 2 because of two way */
}

static uint16_t calcAirspeed_dms(uint8_t temperatureCelsius) {
  /* Return the airspeed depending on the temperature, in deci-meter per second */
  unsigned int airspeed; /* decimeters per second */

  airspeed = 3313 + (6 * temperatureCelsius); /* dry air, 0% humidity, see http://en.wikipedia.org/wiki/Speed_of_sound */
  airspeed -= (airspeed/100)*15; /* factor in ~15% for a relative humidity of ~40% */
  return airspeed;
}


/* measure and return the microseconds */
uint16_t US_Measure_us(void) {
  uint16_t us;
  uint16_t cm;
  
  /* send 10us pulse on TRIG line. */
  TRIG_SetVal(usDevice.trigDevice);
  WAIT1_Waitus(10);
  usDevice.state = ECHO_TRIGGERED;
  TRIG_ClrVal(usDevice.trigDevice);
  while(usDevice.state!=ECHO_FINISHED) {
    /* measure echo pulse */
    if (usDevice.state==ECHO_OVERFLOW) { /* measurement took too long? */
      usDevice.state = ECHO_IDLE;
      return 0; /* no echo, error case */
    }
  }
  us = (usDevice.capture*1000UL)/(TU3_CNT_INP_FREQ_U_0/1000);
  return us;
}

uint16_t US_Measure(void) {
  uint16_t us, cm;
  uint8_t buf[8];

  us = US_Measure_us();
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);

  cm = US_usToCentimeters(us, 22);
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);

#if DEBUG
  CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
#endif
  return cm;
}

void US_Init(void) {
  usDevice.state = ECHO_IDLE;
  usDevice.capture = 0;
  usDevice.trigDevice = TRIG_Init(NULL);
  usDevice.echoDevice = TU3_Init(&usDevice);

	if (FRTOS1_xTaskCreate(UltrasonicTask, "Ultrasonic", configMINIMAL_STACK_SIZE-100, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
	    for(;;){} //error
	}
}
