/*
 * oscillator.c
 *
 *  Created on: 06.11.2016
 *      Author: Manuel
 */

#include "PE_Types.h"
#include "TmDt1.h"
#include "oscillator.h"
#include "Events.h"
#include "Huft_L.h"
#include "Huft_R.h"
#include "Fuss_L.h"
#include "Fuss_R.h"
#include <math.h>
#include "FreeRTOS.h"

struct Servos servo[4];

//setter and getter methodes
void SetA( int A, int ServoNum){
	servo[ServoNum]._A=A;
}
void SetO(int O, int ServoNum){
	servo[ServoNum]._O=O;
}
void SetPh(double Ph, int ServoNum){
	servo[ServoNum]._phase0=Ph;
}

//void SetTrim(int trim){_trim=trim;};
//int getTrim() {return _trim;};
//void Stop() {_stop=true;};
//void Play() {_stop=false;};
//void Reset() {_phase=0;};

//-- Attach an oscillator to a servo
//-- Input: pin is the arduino pin were the servo
//-- is connected
void attach(bool rev, int ServoNum){
	//-- Attach the servo and move it to the home position
	//_servo.write(90); //todo set servos to home pos

	//-- Initialization of oscilator parameters
	servo[ServoNum]._TS = 30;
	servo[ServoNum]._T = 2000;
	servo[ServoNum]._N = servo[ServoNum]._T/servo[ServoNum]._TS;
	servo[ServoNum]._inc = 2*M_PI/servo[ServoNum]._N;

	servo[ServoNum]._previousMillis=0;

	//-- Default parameters
	servo[ServoNum]._A=45;
	servo[ServoNum]._phase=0;
	servo[ServoNum]._phase0=0;
	servo[ServoNum]._O=0;
	servo[ServoNum]._stop=false;

	//-- Reverse mode
	servo[ServoNum]._rev = rev;
}

//-- Detach an oscillator from his servo
void detach()
{
   //-- If the oscillator is attached, detach it.

}

/*************************************/
/* Set the oscillator period, in ms  */
/*************************************/
void SetT(unsigned int T, int ServoNum){
	//-- Assign the new period
	servo[ServoNum]._T=T;

	//-- Recalculate the parameters
	servo[ServoNum]._N = servo[ServoNum]._T/servo[ServoNum]._TS;
	servo[ServoNum]._inc = 2*M_PI/servo[ServoNum]._N;
}


//-- This function returns true if another sample
//-- should be taken (i.e. the TS time has passed since
//-- the last sample was taken
bool next_sample(int ServoNum){
	FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	/*//-- Read current time
	 servo[ServoNum]._currentMillis = cntr;

	//-- Check if the timeout has passed
	if(servo[ServoNum]._currentMillis - servo[ServoNum]._previousMillis > servo[ServoNum]._TS) {
		servo[ServoNum]._previousMillis = servo[ServoNum]._currentMillis;
		return true;
	}

	return false;*/
	return true;
}

/*******************************/
/* Manual set of the position  */
/******************************/

void SetPosition(int position, int servoNumb)
{
	float pos = (float)position*1.4166666;

	switch(servoNumb){
	case 0: Huft_R_SetPos((byte)pos);
			break;
	case 1: Huft_L_SetPos((byte)pos);
			break;
	case 2: Fuss_R_SetPos((byte)pos);
			break;
	case 3: Fuss_L_SetPos((byte)pos);
			break;
	}
}


/*******************************************************************/
/* This function should be periodically called                     */
/* in order to maintain the oscillations. It calculates            */
/* if another sample should be taken and position the servo if so  */
/*******************************************************************/
void refresh(int servoNum){
	//-- Only When TS milliseconds have passed, the new sample is obtained
	FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	//if (next_sample(servoNum)) {

		//-- If the oscillator is not stopped, calculate the servo position
		if (!servo[servoNum]._stop) {
			//-- Sample the sine function and set the servo pos
			servo[servoNum]._pos = round(servo[servoNum]._A *
				  sin(servo[servoNum]._phase + servo[servoNum]._phase0) + servo[servoNum]._O);

			if (servo[servoNum]._rev){
			   servo[servoNum]._pos=-servo[servoNum]._pos;
			}

			//calculate range from 0 to 180 into 0 to 255
			float pos = (float)(servo[servoNum]._pos+90+servo[servoNum]._trim)*1.4166666;
			switch(servoNum){
				case 0: Huft_R_SetPos((byte)pos);
						break;
				case 1: Huft_L_SetPos((byte)pos);
						break;
				case 2: Fuss_R_SetPos((byte)pos);
						break;
				case 3: Fuss_L_SetPos((byte)pos);
						break;
				default: //something went wrong!
						break;
			}
		}

		//-- Increment the phase
		//-- It is always increased, even when the oscillator is stop
		//-- so that the coordination is always kept
		servo[servoNum]._phase = servo[servoNum]._phase + servo[servoNum]._inc;
	//}
}

