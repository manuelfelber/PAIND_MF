/*
 * SdCard.h
 *
 *  Created on: 28.10.2016
 *      Author: Manuel
 */

#ifndef SOURCES_SDCARD_H_
#define SOURCES_SDCARD_H_

#include "FAT1.h"
#include "UTIL1.h"
#include "Hash.h"
#include "Huft_L.h"
#include "CLS1.h"
#include "Robo.h"
#include "Huft_L.h"
#include "Huft_R.h"
#include "Fuss_L.h"
#include "Fuss_R.h"
#include "TRG1.h"
#include "Ultrasonic.h"
#include "LedControl.h"
#include "Application.h"

void SDCardParse(void);
void writeToFile(int16_t );
int readLine(void);
int readLineOffset(int);
static void TrgCallback(void);

void Err(int);

struct Functions{
	int pointer;
	unsigned long hash;
};

#define numberOfFunctionsAllowed 100
#define errorOpenFile 1
#define errorSeekFile 2
#define errorGetTime 3
#define errorCloseFile 4
#define errorCheckRange 5
#define errorAtoi 6



#endif /* SOURCES_SDCARD_H_ */
