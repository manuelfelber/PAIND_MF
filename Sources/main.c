/* ###################################################################
**     Filename    : main.c
**     Project     : PAIND
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-29, 09:43, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Huft_L.h"
#include "Pwm1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "Huft_R.h"
#include "Pwm2.h"
#include "PwmLdd2.h"
#include "Knie_L.h"
#include "Pwm3.h"
#include "PwmLdd3.h"
#include "Knie_R.h"
#include "Pwm4.h"
#include "PwmLdd4.h"
#include "WAIT1.h"
#include "Bein_L.h"
#include "Pwm5.h"
#include "PwmLdd5.h"
#include "Bein_R.h"
#include "Pwm6.h"
#include "PwmLdd6.h"
#include "FRTOS1.h"
#include "SPI_CS.h"
#include "BitIoLdd9.h"
#include "SM1.h"
#include "CS1.h"
#include "HF1.h"
#include "KSDK1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "UTIL1.h"
#include "SYS1.h"
#include "RTT1.h"
#include "CLS1.h"
#include "Buzzer.h"
#include "BitIoLdd1.h"
#include "Switch_A.h"
#include "ExtIntLdd2.h"
#include "ROT.h"
#include "LEDpin1.h"
#include "BitIoLdd2.h"
#include "GRUN.h"
#include "LEDpin2.h"
#include "BitIoLdd3.h"
#include "BitIoLdd4.h"
#include "BLAU.h"
#include "LEDpin3.h"
#include "ANALOG_IN.h"
#include "AdcLdd1.h"
#include "Switch_B.h"
#include "ExtIntLdd3.h"
#include "PTD.h"
#include "TRIG.h"
#include "TMOUT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "SM2.h"
#include "TU3.h"
#include "FAT1.h"
#include "TmDt1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  APP_Run();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
