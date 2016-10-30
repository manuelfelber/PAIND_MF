/*
 * SdCard.c
 *
 *  Created on: 28.10.2016
 *      Author: Manuel
 */

#include "SdCard.h"

static FAT1_FATFS fileSystemObject;
static FIL fp;

void initSdCard(){

}

void writeToFile(int16_t number) {
	uint8_t write_buf[48];
	UINT bw;
	TIMEREC time;
	dword fsize;

	/* open file */
	if (FAT1_open(&fp, "./test2.txt", FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
		Err();
	}

	fsize = FAT1_f_size(&fp);

	/* move to the end of the file */
	if (FAT1_lseek(&fp, fsize) != FR_OK || fp.fptr != fsize) {
		Err();
	}
	/* get time */
	if (TmDt1_GetTime(&time)!=ERR_OK) {
		Err();
	}
	/* write data */
	write_buf[0] = '\0';
	UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Hour);
	UTIL1_chcat(write_buf, sizeof(write_buf), ':');
	UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Min);
	UTIL1_chcat(write_buf, sizeof(write_buf), ':');
	UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Sec);
	UTIL1_chcat(write_buf, sizeof(write_buf), '\t');

	UTIL1_strcatNum16s(write_buf, sizeof(write_buf), number);
	UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
	UTIL1_strcat(write_buf, sizeof(write_buf), (unsigned char*)"\r\n");
	if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
	(void)FAT1_close(&fp);
		Err();
	}
	/* closing file */
	(void)FAT1_close(&fp);
}

void readFromFile(void){
	UINT bw;

	/* open file */
	if (FAT1_open(&fp, "./demoFile.txt", FA_READ) !=FR_OK) {
		Err();
	}

	char symbol = "";
	int n = 0;
	while(symbol != '\r') {
		if(FAT1_read(&fp, &symbol, sizeof(symbol), &bw)!=FR_OK){
			FAT1_close(&fp);
			Err();
		}
		read_buf[n] = symbol;
		n++;
	}
	read_buf[n-1]= '\0';
}


void Err(void) {
  for(;;){}
}
