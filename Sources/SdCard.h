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

void initSdCard(void);
void writeToFile(int16_t );
int readLine(void);
int readLineOffset(int);

void Err(void);

struct Functions{
	int pointer;
	unsigned long hash;
};

#define numberOfFunctionsAllowed 10

#endif /* SOURCES_SDCARD_H_ */
