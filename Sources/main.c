/* ###################################################################
 **     Filename    : main.c
 **     Project     : Peng_Cheng_Exam_2018
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2019-11-08, 14:09, # CodeGen: 0
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
#include "Pins1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "Blue.h"
#include "PwmLdd3.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "TU2.h"
#include "Red.h"
#include "PwmLdd1.h"
#include "Green.h"
#include "PwmLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdlib.h>
#include <math.h>
extern volatile char c;
int monitorTime = 200;

uint16 value;
volatile float x_smooth = 20;
volatile float x_measured;



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
	Term1_Cls();
	AD1_Calibrate(TRUE);
	drawTheme();
	GUIStart();
	for (;;) {
		if (c == 'm') {
			cleanPromot();
			Red_SetRatio16(0);
			Green_SetRatio16(0);
			x_measured = calculateX_measured();
			x_smooth = calculateX_smooth(x_measured);
			

		} else if (c == 'g') {
			cleanPromot();
			c = ' ';
			Blue_SetRatio16(0);
			int gamingTime = 1000;
			int score = 0;
			do {
				int counter = 5;
				int r;
				int a;
				int b;
				int pwm;
				do {
					r = generateRandom(0, 9); // To generate a random number in the range 0 .. 9 inclusive:
					a = generateRandom(10, 19); //generate number a(10<= a <= 19);
					b = a - r
				} while (b < 10 && b >= 0);
				Term1_MoveTo(13, 5);
				Term1_EraseLine();
				Term1_SetColor(clWhite, clBlack);
				Term1_EraseLine();
				Term1_SendStr("Entering Gaming Mode");
				if (score > 5 && score <= 10) {
					Term1_MoveTo(3, 7);
					Term1_SendStr("Equation is: ");
					Term1_SendNum(e);
					Term1_SendStr(" + ");
					Term1_SendNum(d);
					Term1_SendStr(" - ");
					Term1_SendNum(b);
					Term1_SendStr(" = ");
				} else if (score > 10) {
					cleanPromot();
					GUIWin();
					break;
				} else {
					Term1_MoveTo(3, 7);
					Term1_SendStr("Equation is: ");
					Term1_SendNum(a);
					Term1_SendStr(" - ");
					Term1_SendNum(b);
					Term1_SendStr(" = ");
				}
				char m = r + '0'; //transfer int r to char 'm'
				Term1_MoveTo(3, 8);
				Term1_EraseLine();
				Term1_MoveTo(3, 8);
				Term1_SendStr("Your answer is: ");
				Term1_SendChar(c);
				for (int i = 0; i <= 4; i++) {
					counter--;
					delay(gamingTime);
					Term1_MoveTo(3, 11);
					Term1_SendStr("Time left: ");
					Term1_SendNum(counter);
					Term1_SendStr(" s");
				}
				if (c == m) {
					Term1_MoveTo(3, 10);
					Term1_EraseLine();
					Term1_SendStr("Your score is: ");
					Term1_EraseLine();
					Term1_SendNum(score);
				} else {
					score--;
					Term1_MoveTo(3, 10);
					
					Term1_SendStr("Your score is: ");
					Term1_EraseLine();
					Term1_SendNum(score);
				}
				pwm = calculatePWM(score);
				setPWM(score, pwm);
			} while (c != 'q');

		}
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for (;;) {
	}
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
