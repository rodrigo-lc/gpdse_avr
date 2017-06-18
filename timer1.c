/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			timer1.c
 * Module:			TIMER1 interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "timer1.h"
#if __TIMER1_H != 130
	#error Error 101 - Version mismatch on header and source code files (timer1).
#endif

/* -----------------------------------------------------------------------------
 * Configures the timer1 mode and prescaler
 * -------------------------------------------------------------------------- */

resultValue_t timer1Config(timer1Mode_t mode, timer1PrescalerValue_t prescaler)
{
	uint8 regA = TCCR1A;
	uint8 regB = TCCR1B;

	if(prescaler != TIMER1_PRESCALER_NO_CHANGE){
		clrMask(regB, 0x07, CS10);
		switch(prescaler){
			case TIMER1_CLOCK_DISABLE:										break;
			case TIMER1_PRESCALER_OFF:				setMask(regB, 1, CS00);	break;
			case TIMER1_PRESCALER_8:				setMask(regB, 2, CS00);	break;
			case TIMER1_PRESCALER_64:				setMask(regB, 3, CS00);	break;
			case TIMER1_PRESCALER_256:				setMask(regB, 4, CS00);	break;
			case TIMER1_PRESCALER_1024:				setMask(regB, 5, CS00);	break;
			case TIMER1_PRESCALER_T1_FALLING_EDGE:	setMask(regB, 6, CS00);	break;
			case TIMER1_PRESCALER_T1_RISING_EDGE:	setMask(regB, 7, CS00);	break;
			default:								return RESULT_UNSUPPORTED_TIMER1_PRESCALER_VALUE;
		}
	}

	if(mode != TIMER1_MODE_NO_CHANGE){
		clrMask(regA, 0x03, WGM10);
		clrMask(regB, 0x03, WGM12);
		switch(mode){
			case TIMER1_MODE_NORMAL:																						break;
			case TIMER1_MODE_PWM_PHASE_CORRECTED_8_BITS:										setMask(regA, 1, WGM10);	break;
			case TIMER1_MODE_PWM_PHASE_CORRECTED_9_BITS:										setMask(regA, 2, WGM10);	break;
			case TIMER1_MODE_PWM_PHASE_CORRECTED_10_BITS:										setMask(regA, 3, WGM10);	break;
			case TIMER1_MODE_CTC_OCRA:								setMask(regB, 1, WGM12);								break;
			case TIMER1_MODE_FAST_PWM_8_BITS:						setMask(regB, 1, WGM12);	setMask(regA, 1, WGM10);	break;
			case TIMER1_MODE_FAST_PWM_9_BITS:						setMask(regB, 1, WGM12);	setMask(regA, 2, WGM10);	break;
			case TIMER1_MODE_FAST_PWM_10_BITS:						setMask(regB, 1, WGM12);	setMask(regA, 3, WGM10);	break;
			case TIMER1_MODE_PWM_PHASE_FREQUENCY_CORRECTED_ICR:		setMask(regB, 2, WGM12);								break;
			case TIMER1_MODE_PWM_PHASE_FREQUENCY_CORRECTED_OCRA:	setMask(regB, 2, WGM12);	setMask(regA, 1, WGM10);	break;
			case TIMER1_MODE_PWM_PHASE_CORRECTED_ICR:				setMask(regB, 2, WGM12);	setMask(regA, 2, WGM10);	break;
			case TIMER1_MODE_PWM_PHASE_CORRECTED_OCRA:				setMask(regB, 2, WGM12);	setMask(regA, 3, WGM10);	break;
			case TIMER1_MODE_CTC_ICR:								setMask(regB, 3, WGM12);								break;
			case TIMER1_MODE_FAST_PWM_ICR:							setMask(regB, 3, WGM12);	setMask(regA, 2, WGM10);	break;
			case TIMER1_MODE_FAST_PWM_OCRA:							setMask(regB, 3, WGM12);	setMask(regA, 3, WGM10);	break;
			default:												return RESULT_UNSUPPORTED_TIMER1_MODE;
		}
	}

	TCCR1A = regA;
	TCCR1B = regB;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Configures the timer1 compare outputs
 * -------------------------------------------------------------------------- */

resultValue_t timer1OutputConfig(timerOutput_t compA, timerOutput_t compB)
{
	uint8 reg = TCCR1A;

	if(compA != TIMER_PORT_NO_CHANGE){
		clrMask(reg, 0x03, COM1A0);
		switch(compA){
			case TIMER_PORT_NORMAL:											break;
			case TIMER_PORT_TOGGLE_ON_COMPARE:	setMask(reg, 1, COM1A0);	break;
			case TIMER_PORT_CLEAR_ON_COMPARE:	setMask(reg, 2, COM1A0);	break;
			case TIMER_PORT_SET_ON_COMPARE:		setMask(reg, 3, COM1A0);	break;
			default:							return RESULT_UNSUPPORTED_TIMER_PORT_CONFIG;
		}
	}

	if(compB != TIMER_PORT_NO_CHANGE){
		clrMask(reg, 0x03, COM1B0);
		switch(compB){
			case TIMER_PORT_NORMAL:											break;
			case TIMER_PORT_TOGGLE_ON_COMPARE:	setMask(reg, 1, COM1B0);	break;
			case TIMER_PORT_CLEAR_ON_COMPARE:	setMask(reg, 2, COM1B0);	break;
			case TIMER_PORT_SET_ON_COMPARE:		setMask(reg, 3, COM1B0);	break;
			default:							return RESULT_UNSUPPORTED_TIMER_PORT_CONFIG;
		}
	}

	TCCR1A = reg;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Configures the noise canceler of input capture of timer1
 * -------------------------------------------------------------------------- */

resultValue_t	timer1InputCaptureNoiseCancelerConfig(timer1InputCaptureNoiseCanceler_t mode)
{
	uint8 reg = TCCR1B;

	if(mode != TIMER1_NOISE_CANCELER_NO_CHANGE){
		clrMask(reg, 0x03, ICES1);
		switch(mode){
			case TIMER1_NOISE_CANCELER_OFF:										break;
			case TIMER1_NOISE_CANCELER_FALLING_EDGE:	setMask(reg, 1, ICES1);	break;
			case TIMER1_NOISE_CANCELER_RISING_EDGE:		setMask(reg, 3, ICES1);	break;
			default:									return RESULT_UNSUPPORTED_TIMER1_INPUT_CAPTURE_MODE;
		}
	}

	TCCR1B = reg;

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer1 overflow interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1ActivateOverflowInterrupt(void)
{
	setBit(TIMSK1, TOIE1);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer1 overflow interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1DeactivateOverflowInterrupt(void)
{
	clrBit(TIMSK1, TOIE1);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer1 overflow interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer1ClearOverflowInterruptRequest(void)
{
	setBit(TIFR1, TOV1);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer1 compare A interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1ActivateCompareAInterrupt(void)
{
	setBit(TIMSK1, OCIE1A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer1 compare A interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1DeactivateCompareAInterrupt(void)
{
	clrBit(TIMSK1, OCIE1A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer1 compare A interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer1ClearCompareAInterruptRequest(void)
{
	setBit(TIFR1, OCF1A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer1 compare B interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1ActivateCompareBInterrupt(void)
{
	setBit(TIMSK1, OCIE1B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer1 compare B interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1DeactivateCompareBInterrupt(void)
{
	clrBit(TIMSK1, OCIE1B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer1 compare B interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer1ClearCompareBInterruptRequest(void)
{
	setBit(TIFR1, OCF1B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the timer1 input capture interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1ActivateInputCaptureInterrupt(void)
{
	setBit(TIMSK1, ICIE1);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the timer1 input capture interrupt
 * -------------------------------------------------------------------------- */

resultValue_t timer1DeactivateInputCaptureInterrupt(void)
{
	clrBit(TIMSK1, ICIE1);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Clears the timer1 input capture interrupt request
 * -------------------------------------------------------------------------- */

resultValue_t timer1ClearInputCaptureInterruptRequest(void)
{
	setBit(TIFR1, ICF1);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Forces a comparison on the output compare A of the timer1
 * -------------------------------------------------------------------------- */

resultValue_t timer1ForceCompareA(void)
{
	setBit(TCCR1C, FOC1A);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Forces a comparison on the output compare B of the timer1
 * -------------------------------------------------------------------------- */

resultValue_t timer1ForceCompareB(void)
{
	setBit(TCCR1C, FOC1B);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Sets the timer1 counter value
 * -------------------------------------------------------------------------- */

resultValue_t timer1SetCounterValue(uint16 value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		TCNT1 = value;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer1 counter value
 * -------------------------------------------------------------------------- */

uint16 timer1GetCounterValue(void)
{
	uint16 value;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		value = TCNT1;
	}

	return value;
}

/* -----------------------------------------------------------------------------
 * Sets the timer1 compare A value
 * -------------------------------------------------------------------------- */

resultValue_t timer1SetCompareAValue(uint16 value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR1A = value;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer1 compare A value
 * -------------------------------------------------------------------------- */

uint16 timer1GetCompareAValue(void)
{
	uint16 value;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		value = OCR1A;
	}

	return value;
}

/* -----------------------------------------------------------------------------
 * Sets the timer1 compare B value
 * -------------------------------------------------------------------------- */

resultValue_t timer1SetCompareBValue(uint16 value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR1B = value;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer1 compare B value
 * -------------------------------------------------------------------------- */

uint16 timer1GetCompareBValue(void)
{
	uint16 value;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		value = OCR1B;
	}

	return value;
}

/* -----------------------------------------------------------------------------
 * Sets the timer1 input capture value
 * -------------------------------------------------------------------------- */

resultValue_t timer1SetInputCaptureValue(uint16 value)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		ICR1 = value;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Gets the timer1 input capture value
 * -------------------------------------------------------------------------- */

uint16 timer1GetInputCaptureValue(void)
{
	uint16 value;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		value = ICR1;
	}

	return value;
}
