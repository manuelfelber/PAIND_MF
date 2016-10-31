/*
 * SdCard.c
 *
 *  Created on: 28.10.2016
 *      Author: Manuel
 */

#include "SdCard.h"
#include "Hash.h"

static FIL fp;
static uint8_t read_buf[90];
static int stack[3];
static int stackPointer;
static struct Functions parcedFunction[numberOfFunctionsAllowed];


void initSdCard(){
	int number = 0, stackPointer = 0;
	/* open file */
	if (FAT1_open(&fp, "./demoFile.txt", FA_READ) !=FR_OK) {
		Err();
	}

	while(1){
		int tmp = readLine();
		if(UTIL1_strncmp(read_buf, "function", strlen("function"))==0){
			parcedFunction[number].pointer = tmp;
			parcedFunction[number].hash = getHash(read_buf+9);
			number++;
		}
		else if(UTIL1_strncmp(read_buf, "main", strlen("main"))==0){
			 tmp = readLine();
			 if(UTIL1_strncmp(read_buf, "Servo1", strlen("Servo1"))==0){

			 }
			 else if(UTIL1_strncmp(read_buf, "Servo2", strlen("Servo2"))==0){

			 }
			 else if(UTIL1_strncmp(read_buf, "Ultrasonic", strlen("Ultrasonic"))==0){

			 }
			 else{
				 for(int a=0; a<number;a++){
					 if(parcedFunction[a].hash == getHash(&read_buf)){
						 stack[stackPointer] = tmp;
						 stackPointer++;
						 //go to function on file
						 readLineOffset(parcedFunction[a].pointer); //Problem pointer shows on begin of function line
					 }
					 else{
						 //nothing to Parse
					 }
				 }
			 }
		}
		else{
			//nothing to Parse
		}
		for(int n=0; n<sizeof(read_buf); n++){
			read_buf[n]=0;
		}
	}
}

int readLineOffset(int pointer){
	UINT bw;
	int ptOfLine = fp.fptr;

	char symbol = "";
	int n = 0;

	FAT1_lseek(&fp, pointer);

	while(symbol != '\n') {
		if(FAT1_read(&fp, &symbol, sizeof(symbol), &bw)!=FR_OK){
			FAT1_close(&fp);
			return 0;
		}
		read_buf[n] = symbol;
		n++;
	}
	read_buf[n-1]= '\0';
	return ptOfLine;
}

int readLine(void){
	UINT bw;
	int ptOfLine = fp.fptr;

	char symbol = "";
	int n = 0;
	while(symbol != '\n') {
		if(FAT1_read(&fp, &symbol, sizeof(symbol), &bw)!=FR_OK){
			FAT1_close(&fp);
			return 0;
		}
		read_buf[n] = symbol;
		n++;
	}
	read_buf[n-1]= '\0';
	return ptOfLine;
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

void Err(void) {
  for(;;){}
}
