/*
 * Robo_Moves.h
 *
 *  Created on: 25.10.2016
 *      Author: Manuel
 */

#ifndef SOURCES_ROBO_H_
#define SOURCES_ROBO_H_

#include "Huft_L.h"
#include "Huft_R.h"
#include "Fuss_L.h"
#include "Fuss_R.h"
#include "oscillator.h"
#include "TmDt1.h"
#include "Events.h"
#include "math.h"
#include "PE_Types.h"
#include "WAIT1.h"
#include "SdCard.h"

//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         35
#define PERIODE		1800



void initRobo(void);
void Robo_StepForward(int );
void Robo_StepBack(int );
void Robo_StepTime(int );
void Robo_initPos(void);

//-- Macro for converting from degrees to radians
#define M_PI 3.14159

#ifndef DEG2RAD
  #define DEG2RAD(g) ((g)*M_PI)/180
#endif

void walk(float , int , int );
void turn(float , int , int );
void shakeLeg (int ,int ,int );
void updown(float , int , int );
void swing(float , int , int );
void tiptoeSwing(float , int , int );
void jitter(float , int , int );
void ascendingTurn(float , int , int );
void moonwalker(float , int , int, int );
void crusaito(float , int , int , int );
void flapping(float , int , int , int );
void moveServos(int , int [] );
void execute(int[4] , int[4] , int , double[4] , float );
void oscillateServos(int[4] , int[4] , int , double [4], float );

#endif /* SOURCES_ROBO_H_ */
