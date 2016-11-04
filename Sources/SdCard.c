/*
 * SdCard.c
 *
 *  Created on: 28.10.2016
 *      Author: Manuel
 */

#include "SdCard.h"
#include "Hash.h"
#include "Huft_L.h"

static FIL fp;
static uint8_t read_buf[90];
static int stack[3];
static int stackPointer;
static struct Functions parcedFunction[numberOfFunctionsAllowed];


void initSdCard(){
	int number = 0, stackPointer = 0;
	/* open file */
	if (FAT1_open(&fp, "./prog2.txt", FA_READ) !=FR_OK) {
		Err();
	}

	while(1){
		int tmp = readLine();
		if(UTIL1_strncmp(read_buf, "function", strlen("function"))==0){
			parcedFunction[number].pointer = tmp;
			parcedFunction[number].hash = getHash(read_buf+sizeof("function ")-1);
			number++;
		}
		else if(UTIL1_strncmp(read_buf, "main", strlen("main"))==0){
			bool functionCall = false;
			while(1){
				 if(functionCall){
					 functionCall = false;
				 }
				 else{
					tmp = readLine();
				 }
				 if(UTIL1_strncmp(read_buf, "servo1", strlen("servo1"))==0){
					 uint32_t pos = 0, time = 0;
					 const unsigned char *p = read_buf + sizeof("servo1 ")-1;
					 if(UTIL1_xatoi(&p, &pos)!=ERR_OK) {
						 Err(); //error
					 }
					 if(UTIL1_xatoi(&p, &time)!=ERR_OK) {
						 Err(); //error
					 }
					 if(pos > 255 && time < 0){ //check parameter range
						 Err();
					 }
					 Huft_L_SetPos(pos);
				 }
				 else if(UTIL1_strncmp(read_buf, "ultrasonic", strlen("ultrasonic"))==0){
					 //to test
				 }
				 else if(UTIL1_strncmp(read_buf, "wait", strlen("wait"))==0){
					 //to test
				 }
				 else if(UTIL1_strncmp(read_buf, "end", strlen("end"))==0){
					 if(stackPointer > 0){
						 stackPointer--;
						 tmp = readLineOffset(stack[stackPointer]);
						 functionCall = true;
						 continue;
					 }
					 else{
						 break; //finish parsing
					 }
				 }
				 else{
					 for(int a=0; a<number;a++){
						 if(parcedFunction[a].hash == getHash(&read_buf)){
							 stack[stackPointer] = tmp;
							 stackPointer++;
							 //go to function on file
							 tmp = readLineOffset(parcedFunction[a].pointer);
							 functionCall = true;
							 break;
						 }
					 }
				 }
			}
			for(;;){} //finish parsing
		}
		else{
			//unknown header!
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
	for(int n=0; n<sizeof(read_buf); n++){
		read_buf[n]=0;
	}

	FAT1_lseek(&fp, pointer);

	while(symbol != '\n') {
		if(FAT1_read(&fp, &symbol, sizeof(symbol), &bw)!=FR_OK){
			FAT1_close(&fp);
			return 0;
		}
		read_buf[n] = symbol;
		n++;
	}
	ptOfLine = fp.fptr;
	read_buf[n-1]= '\0';
	return ptOfLine;
}

int readLine(void){
	UINT bw;
	int ptOfLine = fp.fptr;

	char symbol = "";
	int n = 0;
	for(int n=0; n<sizeof(read_buf); n++){
		read_buf[n]=0;
	}

	while(symbol != '\n') {
		if(FAT1_read(&fp, &symbol, sizeof(symbol), &bw)!=FR_OK){
			FAT1_close(&fp);
			return 0;
		}
		read_buf[n] = symbol;
		n++;
	}
	ptOfLine = fp.fptr;
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
