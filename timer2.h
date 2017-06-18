/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			timer2.h
 * Module:			TIMER2 interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

#ifndef __TIMER2_H
#define __TIMER2_H 130

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H != 130
	#error Error 100 - globalDefines.h - wrong version (globalDefines must be version 13.0).
#endif

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum timer2Mode_t{
	TIMER2_MODE_NORMAL= 0,
	TIMER2_MODE_PWM_PHASE_CORRECTED_MAX = 1,
	TIMER2_MODE_CTC = 2,
	TIMER2_MODE_FAST_PWM_MAX = 3,
	TIMER2_MODE_PWM_PHASE_CORRECTED_OCRA = 5,
	TIMER2_MODE_FAST_PWM_OCRA = 7,
	TIMER2_MODE_NO_CHANGE = 255
} timer2Mode_t;

typedef enum timer2PrescalerValue_t{
	TIMER2_CLOCK_DISABLE = 0,
	TIMER2_PRESCALER_OFF = 1,
	TIMER2_PRESCALER_8 = 2,
	TIMER2_PRESCALER_32 = 3,
	TIMER2_PRESCALER_64 = 4,
	TIMER2_PRESCALER_128 = 5,
	TIMER2_PRESCALER_256 = 6,
	TIMER2_PRESCALER_1024 = 7,
	TIMER2_PRESCALER_NO_CHANGE = 255
} timer2PrescalerValue_t;

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

resultValue_t	timer2Config(timer2Mode_t mode, timer2PrescalerValue_t prescaler);
resultValue_t	timer2OutputConfig(timerOutput_t compA, timerOutput_t compB);
resultValue_t	timer2ActivateOverflowInterrupt(void);
resultValue_t	timer2DeactivateOverflowInterrupt(void);
resultValue_t	timer2ClearOverflowInterruptRequest(void);
resultValue_t	timer2ActivateCompareAInterrupt(void);
resultValue_t	timer2DeactivateCompareAInterrupt(void);
resultValue_t	timer2ClearCompareAInterruptRequest(void);
resultValue_t	timer2ActivateCompareBInterrupt(void);
resultValue_t	timer2DeactivateCompareBInterrupt(void);
resultValue_t	timer2ClearCompareBInterruptRequest(void);
resultValue_t	timer2ForceCompareA(void);
resultValue_t	timer2ForceCompareB(void);
resultValue_t	timer2SetCounterValue(uint8 value);
uint8			timer2GetCounterValue(void);
resultValue_t	timer2SetCompareAValue(uint8 value);
uint8			timer2GetCompareAValue(void);
resultValue_t	timer2SetCompareBValue(uint8 value);
uint8			timer2GetCompareBValue(void);

#endif
