/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			timer0.c
 * Module:			TIMER0 interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "timer0.h"
#if __TIMER0_H != 130
	#error Error 101 - Version mismatch on header and source code files (timer0).
#endif

/* -----------------------------------------------------------------------------
 * Configures the timer0 mode and prescaler
 * -------------------------------------------------------------------------- */

resultValue_t timer0Config(timer0Mode_t mode, timer0PrescalerValue_t prescaler)
{
	uint8 regA = TCCR0A;
	uint8 regB = TCCR0B;

	if(prescaler != TIMER0_PRESCALER_NO_CHANGE){
		clrMask(regB, 0x07, CS00);
		switch(prescaler){
			case TIMER0_CLOCK_DISABLE:										break;
			case TIMER0_PRESCALER_OFF:				setMask(regB, 1, CS00);	break;
			case TIMER0_PRESCALER_8:				setMask(regB, 2, CS00);	break;
			case TIMER0_PRESCALER_64:				setMask(regB, 3, CS00);	break;
			case TIMER0_PRESCALER_256:				setMask(regB, 4, CS00);	break;
			case TIMER0_PRESCALER_1024:				setMask(regB, 5, CS00);	break;
			case TIMER0_PRESCALER_T0_FALLING_EDGE:	setMask(regB, 6, CS00);	break;
			case TIMER0_PRESCALER_T0_RISING_EDGE:	setMask(regB, 7, CS00);	break;
			default:								return RESULT_UNSUPPORTED_TIMER0_PRESCALER_VALUE;
		}
	}

	if(mode != TIMER0_MODE_NO_CHANGE){
		clrMask(regA, 0x03, WGM00);
		clrBit(regB, WGM02);
		switch(mode){
			case TIMER0_MODE_NORMAL:																		break;
			case TIMER0_MODE_PWM_PHASE_CORRECTED_MAX:							setMask(regA, 1, WGM00);	break;
			case TIMER0_MODE_CTC:												setMask(regA, 2, WGM00);	break;
			case TIMER0_MODE_FAST_PWM_MAX:										setMask(regA, 3, WGM00);	break;
			case TIMER0_MODE_PWM_PHASE_CORRECTED_OCRA:	setBit(regB, WGM02);	setMask(regA, 1, WGM00);	break;
			case TIMER0_MODE_FAST_PWM_OCRA:				setBit(regB, WGM02);	setMask(regA, 3, WGM00);	break;
			default:									return RESULT_UNSUPPORTED_TIMER0_MODE;
		}
	}

	TCCR0A = regA;
	TCCR0B = regB;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Configures the timer0 compare outputs
 * -------------------------------------------------------------------------- */

resultValue_t timer0OutputConfig(timerOutput_t compA, timerOutput_t compB)
{
	uint8 reg = TCCR0A;

	if(compA != TIMER_PORT_NO_CHANGE){
		clrMask(reg, 0x03, COM0A0);
		switch(compA){
			case TIMER_PORT_NORMAL:											break;
			case TIMER_PORT_TOGGLE_ON_COMPARE:	setMask(reg, 1, COM0A0);	break;
			case TIMER_PORT_CLEAR_ON_COMPARE:	setMask(reg, 2, COM0A0);	break;
			case TIMER_PORT_SET_ON_COMPARE:		setMask(reg, 3, COM0A0);	break;
			default:							return RESULT_UNSUPPORTED_TIMER_PORT_CONFIG;
		}
	}

	if(compB != TIMER_PORT_NO_CHANGE){
		clrMask(reg, 0x03, COM0B0);
		switch(compA){
			case TIMER_PORT_NORMAL:											break;
			case TIMER_PORT_TOGGLE_ON_COMPARE:	setMask(reg, 1, COM0B0);	break;
			case TIMER_PORT_CLEAR_ON_COMPARE:	setMask(reg, 2, COM0B0);	break;
			case TIMER_PORT_SET_ON_COMPARE:		setMask(reg, 3, COM0B0);	break;
			default:							return RESULT_UNSUPPORTED_TIMER_PORT_CONFIG;
		}
	}

	TCCR0A = reg;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer0 overflow interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer0ActivateOverflowInterrupt(void)
{
	setBit(TIMSK0, TOIE0);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer0 overflow interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer0DeactivateOverflowInterrupt(void)
{
	clrBit(TIMSK0, TOIE0);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer0 overflow interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer0ClearOverflowInterruptRequest(void)
{
	setBit(TIFR0, TOV0);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer0 compare A interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer0ActivateCompareAInterrupt(void)
{
	setBit(TIMSK0, OCIE0A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer0 compare A interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer0DeactivateCompareAInterrupt(void)
{
	clrBit(TIMSK0, OCIE0A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer0 compare A interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer0ClearCompareAInterruptRequest(void)
{
	setBit(TIFR0, OCF0A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer0 compare B interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer0ActivateCompareBInterrupt(void)
{
	setBit(TIMSK0, OCIE0B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer0 compare B interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer0DeactivateCompareBInterrupt(void)
{
	clrBit(TIMSK0, OCIE0B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer0 compare B interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer0ClearCompareBInterruptRequest(void)
{
	setBit(TIFR0, OCF0B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Forces a comparison on the output compare A of the timer0
 * -------------------------------------------------------------------------- */

resultValue_t timer0ForceCompareA(void)
{
	setBit(TCCR0B, FOC0A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Forces a comparison on the output compare B of the timer0
 * -------------------------------------------------------------------------- */

resultValue_t timer0ForceCompareB(void)
{
	setBit(TCCR0B, FOC0B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Sets the timer0 counter value
 * -------------------------------------------------------------------------- */

resultValue_t timer0SetCounterValue(uint8 value)
{
	TCNT0 = value;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer0 counter value
 * -------------------------------------------------------------------------- */

uint8 timer0GetCounterValue(void)
{
	return TCNT0;
}

/* -----------------------------------------------------------------------------
 * Sets the timer0 compare A value
 * -------------------------------------------------------------------------- */

resultValue_t timer0SetCompareAValue(uint8 value)
{
	OCR0A = value;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer0 compare A value
 * -------------------------------------------------------------------------- */

uint8 timer0GetCompareAValue(void)
{
	return OCR0A;
}

/* -----------------------------------------------------------------------------
 * Sets the timer0 compare B value
 * -------------------------------------------------------------------------- */

resultValue_t timer0SetCompareBValue(uint8 value)
{
	OCR0B = value;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer0 compare B value
 * -------------------------------------------------------------------------- */

uint8 timer0GetCompareBValue(void)
{
	return OCR0B;
}
