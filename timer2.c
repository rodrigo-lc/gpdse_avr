/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			timer2.c
 * Module:			TIMER2 interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "timer2.h"
#if __TIMER2_H != 130
	#error Error 101 - Version mismatch on header and source code files (timer2).
#endif

/* -----------------------------------------------------------------------------
 * Configures the timer2 mode and prescaler
 * -------------------------------------------------------------------------- */

resultValue_t timer2Config(timer2Mode_t mode, timer2PrescalerValue_t prescaler)
{
	uint8 regA = TCCR2A;
	uint8 regB = TCCR2B;

	if(prescaler != TIMER2_PRESCALER_NO_CHANGE){
		clrMask(regB, 0x07, CS20);
		switch(prescaler){
			case TIMER2_CLOCK_DISABLE:							break;
			case TIMER2_PRESCALER_OFF:	setMask(regB, 1, CS20);	break;
			case TIMER2_PRESCALER_8:	setMask(regB, 2, CS20);	break;
			case TIMER2_PRESCALER_32:	setMask(regB, 3, CS20);	break;
			case TIMER2_PRESCALER_64:	setMask(regB, 4, CS20);	break;
			case TIMER2_PRESCALER_128:	setMask(regB, 5, CS20);	break;
			case TIMER2_PRESCALER_256:	setMask(regB, 6, CS20);	break;
			case TIMER2_PRESCALER_1024:	setMask(regB, 7, CS20);	break;
			default:					return RESULT_UNSUPPORTED_TIMER2_PRESCALER_VALUE;
		}
	}

	if(mode != TIMER2_MODE_NO_CHANGE){
		clrMask(regA, 0x03, WGM20);
		clrBit(regB, WGM22);
		switch(mode){
			case TIMER2_MODE_NORMAL:																		break;
			case TIMER2_MODE_PWM_PHASE_CORRECTED_MAX:							setMask(regA, 1, WGM20);	break;
			case TIMER2_MODE_CTC:												setMask(regA, 2, WGM20);	break;
			case TIMER2_MODE_FAST_PWM_MAX:										setMask(regA, 3, WGM20);	break;
			case TIMER2_MODE_PWM_PHASE_CORRECTED_OCRA:	setBit(regB, WGM22);	setMask(regA, 1, WGM20);	break;
			case TIMER2_MODE_FAST_PWM_OCRA:				setBit(regB, WGM22);	setMask(regA, 3, WGM20);	break;
			default:									return RESULT_UNSUPPORTED_TIMER2_MODE;
		}
	}

	TCCR2A = regA;
	TCCR2B = regB;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Configures the timer2 compare outputs
 * -------------------------------------------------------------------------- */

resultValue_t timer2OutputConfig(timerOutput_t compA, timerOutput_t compB)
{
	uint8 reg = TCCR2A;

	if(compA != TIMER_PORT_NO_CHANGE){
		clrMask(reg, 0x03, COM2A0);
		switch(compA){
			case TIMER_PORT_NORMAL:											break;
			case TIMER_PORT_TOGGLE_ON_COMPARE:	setMask(reg, 1, COM2A0);	break;
			case TIMER_PORT_CLEAR_ON_COMPARE:	setMask(reg, 2, COM2A0);	break;
			case TIMER_PORT_SET_ON_COMPARE:		setMask(reg, 3, COM2A0);	break;
			default:							return RESULT_UNSUPPORTED_TIMER_PORT_CONFIG;
		}
	}

	if(compB != TIMER_PORT_NO_CHANGE){
		clrMask(reg, 0x03, COM2B0);
		switch(compA){
			case TIMER_PORT_NORMAL:											break;
			case TIMER_PORT_TOGGLE_ON_COMPARE:	setMask(reg, 1, COM2B0);	break;
			case TIMER_PORT_CLEAR_ON_COMPARE:	setMask(reg, 2, COM2B0);	break;
			case TIMER_PORT_SET_ON_COMPARE:		setMask(reg, 3, COM2B0);	break;
			default:							return RESULT_UNSUPPORTED_TIMER_PORT_CONFIG;
		}
	}

	TCCR2A = reg;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer2 overflow interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer2ActivateOverflowInterrupt(void)
{
	setBit(TIMSK2, TOIE2);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer2 overflow interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer2DeactivateOverflowInterrupt(void)
{
	clrBit(TIMSK2, TOIE2);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer2 overflow interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer2ClearOverflowInterruptRequest(void)
{
	setBit(TIFR2, TOV2);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer2 compare A interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer2ActivateCompareAInterrupt(void)
{
	setBit(TIMSK2, OCIE2A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer2 compare A interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer2DeactivateCompareAInterrupt(void)
{
	clrBit(TIMSK2, OCIE2A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer2 compare A interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer2ClearCompareAInterruptRequest(void)
{
	setBit(TIFR2, OCF2A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer2 compare B interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer2ActivateCompareBInterrupt(void)
{
	setBit(TIMSK2, OCIE2B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer2 compare B interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer2DeactivateCompareBInterrupt(void)
{
	clrBit(TIMSK2, OCIE2B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer2 compare B interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer2ClearCompareBInterruptRequest(void)
{
	setBit(TIFR2, OCF2B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Forces a comparison on the output compare A of the timer2
 * -------------------------------------------------------------------------- */

resultValue_t timer2ForceCompareA(void)
{
	setBit(TCCR2B, FOC2A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Forces a comparison on the output compare B of the timer2
 * -------------------------------------------------------------------------- */

resultValue_t timer2ForceCompareB(void)
{
	setBit(TCCR2B, FOC2B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Sets the timer2 counter value
 * -------------------------------------------------------------------------- */

resultValue_t timer2SetCounterValue(uint8 value)
{
	TCNT2 = value;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer2 counter value
 * -------------------------------------------------------------------------- */

uint8 timer2GetCounterValue(void)
{
	return TCNT2;
}

/* -----------------------------------------------------------------------------
 * Sets the timer2 compare A value
 * -------------------------------------------------------------------------- */

resultValue_t timer2SetCompareAValue(uint8 value)
{
	OCR2A = value;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer2 compare A value
 * -------------------------------------------------------------------------- */

uint8 timer2GetCompareAValue(void)
{
	return OCR2A;
}

/* -----------------------------------------------------------------------------
 * Sets the timer2 compare B value
 * -------------------------------------------------------------------------- */

resultValue_t timer2SetCompareBValue(uint8 value)
{
	OCR2B = value;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer2 compare B value
 * -------------------------------------------------------------------------- */

uint8 timer2GetCompareBValue(void)
{
	return OCR2B;
}
