/*
 * LedControl.c
 *
 *  Created on: 22.10.2016
 *      Author: Manuel Felber
 */
 

#include "LedControl.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "stdbool.h"
#include "SM1.h"
#include "SPI_CS.h"
#include "FRTOS1.h"

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define SM1_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_SM1_ID))

const int numDevices = 1;      // number of MAX7219s used

const static char eye[8][2] = {
	{0b00000000, 0b00000000 },
	{0b00011000, 0b00011000},
	{0b00111100, 0b00111100},
	{0b01100110, 0b01001110},
	{0b01100110, 0b01001110},
	{0b00111100, 0b00111100},
	{0b00011000, 0b00011000},
	{0b00000000, 0b00000000}
};

const static char sechs[8] = {
	0b00110000,	//6
	0b01000000,
	0b10000000,
	0b11110000,
	0b10001000,
	0b10001000,
	0b01110000,
	0b00000000};


static portTASK_FUNCTION(DotMatrixTask, pvParameters) {
	LedControl(1);
	for (int x=0; x<numDevices; x++){
		shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
		setIntensity(x,8);       // Set the brightness to default value
		clearDisplay(x);         // and clear the display
	}
	//FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	for(;;){
		for(int i = 0; i < 2;i++) {
			FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
			LedShowEye(i);
		}
	}
}

void LedInit(){
	if (FRTOS1_xTaskCreate(DotMatrixTask, "DotMatrix", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
	    for(;;){} //error
	}
	/*LedControl(1);
	for (int x=0; x<numDevices; x++){
		shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
		setIntensity(x,8);       // Set the brightness to default value
		clearDisplay(x);         // and clear the display
	}*/
}

uint8_t LedShowEye(int view){
	int digit = 0;
	for(int i = 0; i <= 7; i++){
		spiTransfer(0, digit+1,eye[i][view]);
		digit++;
	}
	return ERR_OK;
}

uint8_t LedShowSix(void){
	int digit = 0;
	for(int i = 0; i <= 7; i++){
		spiTransfer(0, digit+1,sechs[i]);
		digit++;
	}
	return ERR_OK;
}

uint8_t Led_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
{
  if (UTIL1_strcmp((char*)cmd, DOT_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "DOTMatrix help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, "DOTMatrix eye")==0) {
    CS1_CriticalVariable();
    *handled = TRUE;

    CS1_EnterCritical();
    uint8_t val = LedShowEye(1);
    CS1_ExitCritical();
    return val;
  } else if (UTIL1_strcmp((char*)cmd, "DOTMatrix six")==0) {
    *handled = TRUE;
    return LedShowSix();
  }
  return ERR_OK;
}

uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"DOTMatrix", (unsigned char*)"Commands to test Dotmatrix functions\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  eye", (unsigned char*)"Show Robot eye\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  six", (unsigned char*)"show number six\r\n", io->stdOut);
  return ERR_OK;
}

void LedControl(int numDevices) {
    if(numDevices<=0 || numDevices>8 ){
    	numDevices=8;
    }
	maxDevices=numDevices;

	SPI_CS_SetVal();
	for(int i=0;i<64;i++){
		status[i]=0x00;
	}
	for(int i=0;i<maxDevices;i++) {
		spiTransfer(i,OP_DISPLAYTEST,0);
		//scanlimit is set to max on startup
		setScanLimit(i,7);
		//decode is done in source
		spiTransfer(i,OP_DECODEMODE,0);
		clearDisplay(i);
		//we go into shutdown-mode on startup
		shutdown(i,true);
    }
}

int getDeviceCount() {
    return maxDevices;
}

void shutdown(int addr, bool b) {
    if(addr<0 || addr>=maxDevices)
	return;
    if(b)
	spiTransfer(addr, OP_SHUTDOWN,0);
    else
	spiTransfer(addr, OP_SHUTDOWN,1);
}
	
void setScanLimit(int addr, int limit) {
    if(addr<0 || addr>=maxDevices)
    	return;
    if(limit>=0 || limit<8)
    	spiTransfer(addr, OP_SCANLIMIT,limit);
}

void setIntensity(int addr, int intensity) {
    if(addr<0 || addr>=maxDevices)
    	return;
    if(intensity>=0 || intensity<16)	
    	spiTransfer(addr, OP_INTENSITY,intensity);
    
}

void clearDisplay(int addr) {
    int offset;

    if(addr<0 || addr>=maxDevices)
    	return;
    offset=addr*8;
    for(int i=0;i<8;i++) {
		status[offset+i]=0;
		spiTransfer(addr, i+1,status[offset+i]);
    }
}

void setLed(int addr, int row, int column, bool state) {
    int offset;
    char val=0x00;

    if(addr<0 || addr>=maxDevices)
    	return;
    if(row<0 || row>7 || column<0 || column>7)
    	return;
    offset=addr*8;
    val=0b10000000 >> column;
    if(state)
    	status[offset+row]=status[offset+row]|val;
    else {
		val=~val;
		status[offset+row]=status[offset+row]&val;
    }
    spiTransfer(addr, row+1,status[offset+row]);
}
	
void setRow(int addr, int row, char value) {
    int offset;

    if(addr<0 || addr>=maxDevices)
    	return;
    if(row<0 || row>7)
    	return;
    offset=addr*8;
    status[offset+row]=value;
    spiTransfer(addr, row+1,status[offset+row]);
}
    
void setColumn(int addr, int col, char value) {
    char val;

    if(addr<0 || addr>=maxDevices)
    	return;
    if(col<0 || col>7) 
    	return;
    for(int row=0;row<8;row++) {
		val=value >> (7-row);
		val=val & 0x01;
		setLed(addr,row,col,val);
    }
}

/*void setDigit(int addr, int digit, char value, bool dp) {
    int offset;
    char v;

    if(addr<0 || addr>=maxDevices)
    	return;
    if(digit<0 || digit>7 || value>15)
    	return;
    offset=addr*8;
    v=charTable[value];
    if(dp)
    	v|=0b10000000;
    status[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
    
}/*

/*void setChar(int addr, int digit, char value, bool dp) {
    int offset;
    char index,v;

    if(addr<0 || addr>=maxDevices)
    	return;
    if(digit<0 || digit>7)
    	return;
    offset=addr*8;
    index=(char)value;
    if(index >127) {
		//nothing define we use the space char
		value=32;
    }
    v=charTable[index];
    if(dp)
    	v|=0b10000000;
    status[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}*/

void spiTransfer(int addr, volatile char opcode, volatile char data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=maxDevices*2;

    for(int i=0;i<maxbytes;i++)
    	spidata[i]=(char)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line 
    SPI_CS_ClrVal();
    //Now shift out the data 
    for(int i=maxbytes;i>0;i--){
    	//shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    	SM1_SendBlock(SM1_DeviceData, &spidata[i-1], sizeof(char));
    }
    //latch the data onto the display
    SPI_CS_SetVal();
}    


