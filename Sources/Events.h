/* ###################################################################
**     Filename    : Events.h
**     Project     : PAIND
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-29, 09:43, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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
#include "Fuss_L.h"
#include "Pwm5.h"
#include "PwmLdd5.h"
#include "Fuss_R.h"
#include "Pwm6.h"
#include "PwmLdd6.h"
#include "FRTOS1.h"
#include "RTOSCNTRLDD1.h"
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
#include "PTD.h"
#include "SwitchB.h"
#include "keyPin1.h"
#include "KeyISRpin1.h"
#include "ExtIntLdd4.h"
#include "TRG1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "Power6V.h"
#include "BitIoLdd5.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "I2C2.h"
#include "SwitchA.h"
#include "keyPin2.h"
#include "KeyISRpin2.h"
#include "ExtIntLdd5.h"
#include "TRIG.h"
#include "TU2.h"
#include "TMOUT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "SM2.h"
#include "TU3.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "accMonitoring.h"
#include "SdCard.h"

#ifdef __cplusplus
extern "C" {
#endif 

extern uint32_t cntr;

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pxTask          - Task handle
**       * pcTaskName      - Pointer to task name
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationTickHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationMallocFailedHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void ANALOG_IN_OnEnd(void);
/*
** ===================================================================
**     Event       :  ANALOG_IN_OnEnd (module Events)
**
**     Component   :  ANALOG_IN [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void ANALOG_IN_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  ANALOG_IN_OnCalibrationEnd (module Events)
**
**     Component   :  ANALOG_IN [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  TU1_OnChannel0 (module Events)
**
**     Component   :  TU1 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU1_OnChannel0(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  TU3_OnCounterRestart (module Events)
**
**     Component   :  TU3 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU3_OnCounterRestart(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  TU3_OnChannel0 (module Events)
**
**     Component   :  TU3 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU3_OnChannel0(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  SM1_OnBlockReceived (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer. This method is available only if
**         the ReceiveBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr);

void SwitchB_OnKeyPressed(byte keys);
/*
** ===================================================================
**     Event       :  SwitchB_OnKeyPressed (module Events)
**
**     Component   :  SwitchB [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void SwitchB_OnKeyReleased(byte keys);
/*
** ===================================================================
**     Event       :  SwitchB_OnKeyReleased (module Events)
**
**     Component   :  SwitchB [Key]
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void);

void SwitchA_OnKeyPressed(byte keys);
/*
** ===================================================================
**     Event       :  SwitchA_OnKeyPressed (module Events)
**
**     Component   :  SwitchA [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void SwitchA_OnKeyReleased(byte keys);
/*
** ===================================================================
**     Event       :  SwitchA_OnKeyReleased (module Events)
**
**     Component   :  SwitchA [Key]
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void ACCMON_EVNT_AppHandleEvent(uint8_t event);
/*
** ===================================================================
**     Event       :  ACCMON_EVNT_AppHandleEvent (module Events)
**
**     Component   :  ACCMON_EVNT [SimpleEvents]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - Event (event number) to be processed.
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
