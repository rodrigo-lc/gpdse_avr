/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			timer1.h
 * Module:			TIMER1 interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

#ifndef __TIMER1_H
#define __TIMER1_H 130

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H != 130
	#error Error 100 - globalDefines.h - wrong version (globalDefines must be version 13.0).
#endif

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum timer1Mode_t{
	TIMER1_MODE_NORMAL = 0,
	TIMER1_MODE_PWM_PHASE_CORRECTED_8_BITS = 1,
	TIMER1_MODE_PWM_PHASE_CORRECTED_9_BITS = 2,
	TIMER1_MODE_PWM_PHASE_CORRECTED_10_BITS = 3,
	TIMER1_MODE_CTC_OCRA = 4,
	TIMER1_MODE_FAST_PWM_8_BITS = 5,
	TIMER1_MODE_FAST_PWM_9_BITS = 6,
	TIMER1_MODE_FAST_PWM_10_BITS = 7,
	TIMER1_MODE_PWM_PHASE_FREQUENCY_CORRECTED_ICR = 8,
	TIMER1_MODE_PWM_PHASE_FREQUENCY_CORRECTED_OCRA = 9,
	TIMER1_MODE_PWM_PHASE_CORRECTED_ICR = 10,
	TIMER1_MODE_PWM_PHASE_CORRECTED_OCRA = 11,
	TIMER1_MODE_CTC_ICR = 12,
	TIMER1_MODE_FAST_PWM_ICR = 14,
	TIMER1_MODE_FAST_PWM_OCRA = 15,
	TIMER1_MODE_NO_CHANGE = 255
} timer1Mode_t;

typedef enum timer1PrescalerValue_t{
	TIMER1_CLOCK_DISABLE = 0,
	TIMER1_PRESCALER_OFF = 1,
	TIMER1_PRESCALER_8 = 2,
	TIMER1_PRESCALER_64 = 3,
	TIMER1_PRESCALER_256 = 4,
	TIMER1_PRESCALER_1024 = 5,
	TIMER1_PRESCALER_T1_FALLING_EDGE = 6,
	TIMER1_PRESCALER_T1_RISING_EDGE = 7,
	TIMER1_PRESCALER_NO_CHANGE = 255
} timer1PrescalerValue_t;

typedef enum timer1InputCaptureNoiseCanceler_t{
	TIMER1_NOISE_CANCELER_OFF = 0,
	TIMER1_NOISE_CANCELER_FALLING_EDGE = 1,
	TIMER1_NOISE_CANCELER_RISING_EDGE = 3,
	TIMER1_NOISE_CANCELER_NO_CHANGE = 255
} timer1InputCaptureNoiseCanceler_t;

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

resultValue_t	timer1Config(timer1Mode_t mode, timer1PrescalerValue_t prescaler);
resultValue_t	timer1OutputConfig(timerOutput_t compA, timerOutput_t compB);
resultValue_t	timer1InputCaptureNoiseCancelerConfig(timer1InputCaptureNoiseCanceler_t mode);
resultValue_t	timer1ActivateOverflowInterrupt(void);
resultValue_t	timer1DeactivateOverflowInterrupt(void);
resultValue_t	timer1ClearOverflowInterruptRequest(void);
resultValue_t	timer1ActivateCompareAInterrupt(void);
resultValue_t	timer1DeactivateCompareAInterrupt(void);
resultValue_t	timer1ClearCompareAInterruptRequest(void);
resultValue_t	timer1ActivateCompareBInterrupt(void);
resultValue_t	timer1DeactivateCompareBInterrupt(void);
resultValue_t	timer1ClearCompareBInterruptRequest(void);
resultValue_t	timer1ActivateInputCaptureInterrupt(void);
resultValue_t	timer1DeactivateInputCaptureInterrupt(void);
resultValue_t	timer1ClearInputCaptureInterruptRequest(void);
resultValue_t	timer1ForceCompareA(void);
resultValue_t	timer1ForceCompareB(void);
resultValue_t	timer1SetCounterValue(uint16 value);
uint16			timer1GetCounterValue(void);
resultValue_t	timer1SetCompareAValue(uint16 value);
uint16			timer1GetCompareAValue(void);
resultValue_t	timer1SetCompareBValue(uint16 value);
uint16			timer1GetCompareBValue(void);
resultValue_t	timer1SetInputCaptureValue(uint16 value);
uint16			timer1GetInputCaptureValue(void);

#endif
