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
volatile uint16 x_smooth = 20;
volatile uint16 x_measured;

void delay(int time_expect) {
	word time;
	int counter = time_expect / 1000;
	FC321_Reset();
	do {
		FC321_GetTimeMS(&time);
	} while (time < time_expect);
}
void drawTheme() {
	Term1_MoveTo(3, 3);
	Term1_SetColor(clYellow, clBlack);
	Term1_SendStr("CC2511 Exam 2018");
	Term1_MoveTo(3, 4);
	Term1_SendStr("_____________________   Cheng Peng");
	Term1_MoveTo(3, 5);
	Term1_SetColor(clCyan, clBlack);
	Term1_SendStr("Prompt: ");
	Term1_MoveTo(13, 5);
}
void GUIStart() {
	Term1_MoveTo(3, 13);
	Term1_SendStr("Press 'm' for Monitoring mode");
	Term1_MoveTo(3, 14);
	Term1_SendStr("Press 'g' for Gaming mode");
	Term1_MoveTo(3, 15);
	Term1_SendStr("Press 'q' to quit");
}

void GUIMonitorMode(int x_measured, int x_smooth) {
	Term1_MoveTo(13, 5);
	Term1_EraseLine();
	Term1_SetColor(clWhite, clBlack);
	Term1_EraseLine();
	Term1_SendStr("Monitoring mode ");
	Term1_MoveTo(3, 9);
	Term1_SendStr("X smooth is :");
	Term1_SendNum(x_smooth);
	Term1_MoveTo(3, 8);
	Term1_SendStr("X measured is :");
	Term1_SendNum(x_measured);
	if (x_measured < x_smooth) {
		Green_SetRatio16(0);
		Blue_SetRatio16(0);
	} else if (x_measured >= x_smooth) {
		Green_SetRatio16(0);
		Blue_SetRatio16(65535 / 10);
	}
}
float calculateX_measured() {
	AD1_Measure(TRUE);
	AD1_GetValue16(&value);
	x_measured = (3.3 * value * 1000) / 65535.0;
	delay(monitorTime);
	return x_measured;
}
float calculateX_smooth( x_measured) {
	float a = 0.9;
	x_smooth = a * x_smooth + (1 - a) * x_measured;
	return x_smooth;
}
void GUIGamingMode(int a, int b, int r) {
	Term1_MoveTo(3, 6);
	Term1_SetColor(clWhite, clBlack);
	Term1_EraseLine();
	Term1_SendStr("Entering Gaming Mode");
	Term1_MoveTo(3, 8);
	Term1_SendStr("Equation is :");
	Term1_SendNum(a);
	Term1_SendStr(" - ");
	Term1_SendNum(r);
	Term1_SendStr(" = ");
	Term1_MoveTo(3, 9);
	Term1_SendStr("Please Enter Your Answer: ");
	delay(monitorTime);
}

int rand(void);
void srand(unsigned int seed);
int generateRandom(int min, int max) {
	int num;
	num = rand() % (max + 1 - min) + min;
	return num;
}

void cleanPromot() {
	Term1_MoveTo(13, 5);
	Term1_EraseLine();
	Term1_MoveTo(3, 6);
	Term1_EraseLine();
	Term1_MoveTo(3, 7);
	Term1_EraseLine();
	Term1_MoveTo(3, 8);
	Term1_EraseLine();
	Term1_MoveTo(3, 9);
	Term1_EraseLine();
	Term1_MoveTo(3, 10);
	Term1_EraseLine();
	Term1_MoveTo(3, 11);
	Term1_EraseLine();
	Term1_MoveTo(3, 6);
}

int calculatePWM(int score) {
	int pwm;
	if (score >= -5 && score <= 5) {
		pwm = sqrt(score * score) * 65535 / 5;
	} else {
		pwm = 65535;
	}
}
void setPWM(int score, int pwm) {
	if (score == 0) {
		Red_SetRatio16(0);
		Red_SetRatio16(0);
	} else if (score > 0) {
		Red_SetRatio16(0);
		Green_SetRatio16(pwm);
	} else if (score < 0) {
		Red_SetRatio16(pwm);
		Green_SetRatio16(0);
	}
}
void GUIWin() {
	Term1_MoveTo(3, 7);
	Term1_SendStr("You are winner!");
	Term1_MoveTo(3, 8);
	Term1_SendStr("Game finished!");
}

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
			do {
				x_measured = calculateX_measured();
				x_smooth = calculateX_smooth(x_measured);
				GUIMonitorMode(x_measured, x_smooth);
			} while (c != 'q');

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
				int d;
				int e;
				int pwm;
				do {
					r = generateRandom(0, 9); // To generate a random number in the range 0 .. 9 inclusive:
					a = generateRandom(10, 19); //generate number a(10<= a <= 19);
					b = a - r;
					d = generateRandom(0, 9);
					e = a - d; //e + d - b
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
					Term1_MoveTo(3, 9);
					Term1_EraseLine();
					Term1_MoveTo(3, 9);
					Term1_SendStr("The answer is correct");
					score++;
					Term1_MoveTo(3, 10);
					Term1_EraseLine();
					Term1_SendStr("Your score is: ");
					Term1_EraseLine();
					Term1_SendNum(score);
				} else {
					Term1_MoveTo(3, 9);
					Term1_EraseLine();
					Term1_MoveTo(3, 9);
					Term1_SendStr("The answer is wrong");
					score--;
					Term1_MoveTo(3, 10);
					Term1_EraseLine();
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
