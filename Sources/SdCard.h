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
void readFromFile(void);

void Err(void);

static uint8_t read_buf[90];

#endif /* SOURCES_SDCARD_H_ */
