/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			timer0.h
 * Module:			TIMER0 interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

#ifndef __TIMER0_H
#define __TIMER0_H 130

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H != 130
	#error Error 100 - globalDefines.h - wrong version (globalDefines must be version 13.0).
#endif

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum timer0Mode_t{
	TIMER0_MODE_NORMAL= 0,
	TIMER0_MODE_PWM_PHASE_CORRECTED_MAX = 1,
	TIMER0_MODE_CTC = 2,
	TIMER0_MODE_FAST_PWM_MAX = 3,
	TIMER0_MODE_PWM_PHASE_CORRECTED_OCRA = 5,
	TIMER0_MODE_FAST_PWM_OCRA = 7,
	TIMER0_MODE_NO_CHANGE = 255
} timer0Mode_t;

typedef enum timer0PrescalerValue_t{
	TIMER0_CLOCK_DISABLE = 0,
	TIMER0_PRESCALER_OFF = 1,
	TIMER0_PRESCALER_8 = 2,
	TIMER0_PRESCALER_64 = 3,
	TIMER0_PRESCALER_256 = 4,
	TIMER0_PRESCALER_1024 = 5,
	TIMER0_PRESCALER_T0_FALLING_EDGE = 6,
	TIMER0_PRESCALER_T0_RISING_EDGE = 7,
	TIMER0_PRESCALER_NO_CHANGE = 255
} timer0PrescalerValue_t;

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

resultValue_t	timer0Config(timer0Mode_t mode, timer0PrescalerValue_t prescaler);
resultValue_t	timer0OutputConfig(timerOutput_t compA, timerOutput_t compB);
resultValue_t	timer0ActivateOverflowInterrupt(void);
resultValue_t	timer0DeactivateOverflowInterrupt(void);
resultValue_t	timer0ClearOverflowInterruptRequest(void);
resultValue_t	timer0ActivateCompareAInterrupt(void);
resultValue_t	timer0DeactivateCompareAInterrupt(void);
resultValue_t	timer0ClearCompareAInterruptRequest(void);
resultValue_t	timer0ActivateCompareBInterrupt(void);
resultValue_t	timer0DeactivateCompareBInterrupt(void);
resultValue_t	timer0ClearCompareBInterruptRequest(void);
resultValue_t	timer0ForceCompareA(void);
resultValue_t	timer0ForceCompareB(void);
resultValue_t	timer0SetCounterValue(uint8 value);
uint8			timer0GetCounterValue(void);
resultValue_t	timer0SetCompareAValue(uint8 value);
uint8			timer0GetCompareAValue(void);
resultValue_t	timer0SetCompareBValue(uint8 value);
uint8			timer0GetCompareBValue(void);

#endif
