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

struct Servos _servo[4];

//setter and getter methodes
void SetA( int A, int ServoNum){
	_servo[ServoNum]._A=A;
}
void SetO(int O, int ServoNum){
	_servo[ServoNum]._O=O;
}
void SetPh(double Ph, int ServoNum){
	_servo[ServoNum]._phase0=Ph;
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
	_servo[ServoNum]._TS = 30;
	_servo[ServoNum]._T = 2000;
	_servo[ServoNum]._N = _servo[ServoNum]._T/_servo[ServoNum]._TS;
	_servo[ServoNum]._inc = 2*M_PI/_servo[ServoNum]._N;

	_servo[ServoNum]._previousMillis=0;

	//-- Default parameters
	_servo[ServoNum]._A=45;
	_servo[ServoNum]._phase=0;
	_servo[ServoNum]._phase0=0;
	_servo[ServoNum]._O=0;
	_servo[ServoNum]._stop=false;

	//-- Reverse mode
	_servo[ServoNum]._rev = rev;
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
	_servo[ServoNum]._T=T;

	//-- Recalculate the parameters
	_servo[ServoNum]._N = _servo[ServoNum]._T/_servo[ServoNum]._TS;
	_servo[ServoNum]._inc = 2*M_PI/_servo[ServoNum]._N;
}


//-- This function returns true if another sample
//-- should be taken (i.e. the TS time has passed since
//-- the last sample was taken
bool next_sample(int ServoNum){
	FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
	/*//-- Read current time
	 _servo[ServoNum]._currentMillis = cntr;

	//-- Check if the timeout has passed
	if(_servo[ServoNum]._currentMillis - _servo[ServoNum]._previousMillis > _servo[ServoNum]._TS) {
		_servo[ServoNum]._previousMillis = _servo[ServoNum]._currentMillis;
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
	//_servo.write(position+_trim); //no used
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
  if (next_sample(servoNum)) {

      //-- If the oscillator is not stopped, calculate the servo position
      if (!_servo[servoNum]._stop) {
		//-- Sample the sine function and set the servo pos
		_servo[servoNum]._pos = round(_servo[servoNum]._A *
			  sin(_servo[servoNum]._phase + _servo[servoNum]._phase0) + _servo[servoNum]._O);
		if (_servo[servoNum]._rev){
		   _servo[servoNum]._pos=-_servo[servoNum]._pos;
		}

		//_servo.write(_pos+90+_trim);
		//calculate range from 0 to 180 into 0 to 255
		float pos = (float)(_servo[servoNum]._pos+90+_servo[servoNum]._trim)*1.4166666;
		switch(servoNum){
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

      //-- Increment the phase
      //-- It is always increased, even when the oscillator is stop
      //-- so that the coordination is always kept
      _servo[servoNum]._phase = _servo[servoNum]._phase + _servo[servoNum]._inc;

  }
}

