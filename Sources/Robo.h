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
#define BIG         30
#define PERIODE		1800//1800//2500

#define ROBO_PARSE_COMMAND_ENABLED         1
/* predefined commands */
#define DOT_CMD_HELP   "help"
#define DOT_CMD_STATUS "status"

void Robo_StepForward(int );

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
uint8_t Robo_ParseCommand(const unsigned char *, bool *, const CLS1_StdIOType *);
static uint8_t PrintHelp(const CLS1_StdIOType *);

#endif /* SOURCES_ROBO_H_ */
