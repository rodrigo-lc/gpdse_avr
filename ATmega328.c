/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			ATmega328.c
 * Module:			ATmega328 basic interface
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 * Build:			1
 * Last edition:	September 6, 2017
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "ATmega328.h"
#if __ATMEGA328_H != 1
	#error Error 101 - Build mismatch on header and source code files (ATmega328).
#endif

/* -----------------------------------------------------------------------------
 * Configures the system clock prescaler
 * -------------------------------------------------------------------------- */

resultValue_t systemClockSetPrescaler(systemPrescalerValue_t prescaler)
{
	uint8 aux8 = 0;

	switch(prescaler) {
	case SYSTEM_PRESCALER_OFF:
		aux8 = 0;
		break;
	case SYSTEM_PRESCALER_2:
		aux8 = 1;
		break;
	case SYSTEM_PRESCALER_4:
		aux8 = 2;
		break;
	case SYSTEM_PRESCALER_8:
		aux8 = 3;
		break;
	case SYSTEM_PRESCALER_16:
		aux8 = 4;
		break;
	case SYSTEM_PRESCALER_32:
		aux8 = 5;
		break;
	case SYSTEM_PRESCALER_64:
		aux8 = 6;
		break;
	case SYSTEM_PRESCALER_128:
		aux8 = 7;
		break;
	case SYSTEM_PRESCALER_256:
		aux8 = 8;
		break;
	default:
		return RESULT_UNSUPPORTED_SYSTEM_PRESCALER_VALUE;
		break;
	}
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		CLKPR = 0b10000000;
		CLKPR = aux8;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Globally enables the internal pull-ups
 * -------------------------------------------------------------------------- */

resultValue_t globalPullUpEnable(void)
{
	clrBit(MCUCR, PUD);

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Globally disables the internal pull-ups
 * -------------------------------------------------------------------------- */

resultValue_t pullUpDisable(void)
{
	setBit(MCUCR, PUD);

	return RESULT_OK;
}



//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE

/* -----------------------------------------------------------------------------
 * Configures the external interrupt int0
 * -------------------------------------------------------------------------- */

resultValue_t int0Config(portMode_t port, senseMode_t sense)
{
	uint8 aux8 = 0;

	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD2);
		setBit(DDRD, PD2);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD2);
		setBit(DDRD, PD2);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD2);
		clrBit(DDRD, PD2);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD2);
		clrBit(DDRD, PD2);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}

	if(sense != SENSE_NO_CHANGE) {
		aux8 = EICRA & ~(0x03 << ISC00);
		switch(sense) {
		case SENSE_LOW_LEVEL:
			break;
		case SENSE_ANY_EDGE:
			aux8 |= (0x01 << ISC00);
			break;
		case SENSE_FALLING_EDGE:
			aux8 |= (0x02 << ISC00);
			break;
		case SENSE_RISING_EDGE:
			aux8 |= (0x03 << ISC00);
			break;
		case SENSE_NO_CHANGE:
			break;
		default:
			return RESULT_INT_SENSE_VALUE_UNSUPPORTED;
			break;
		}
		EICRA = aux8;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt int0
 * -------------------------------------------------------------------------- */

void int0ActivateInterrupt(void)
{
	setBit(EIMSK, INT0);
	return;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt int0
 * -------------------------------------------------------------------------- */

void int0DeactivateInterrupt(void)
{
	clrBit(EIMSK, INT0);
	return;
}

/* -----------------------------------------------------------------------------
 * Clears the external interrupt int0 request
 * -------------------------------------------------------------------------- */

void int0ClearInterruptRequest(void)
{
	setBit(EIFR, INTF0);
	return;
}

/* -----------------------------------------------------------------------------
 * Configures the external interrupt int1
 * -------------------------------------------------------------------------- */

resultValue_t int1Config(portMode_t port, senseMode_t sense)
{
	uint8 aux8 = 0;

	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD3);
		setBit(DDRD, PD3);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD3);
		setBit(DDRD, PD3);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD3);
		clrBit(DDRD, PD3);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD3);
		clrBit(DDRD, PD3);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}

	if(sense != SENSE_NO_CHANGE) {
		aux8 = EICRA & ~(0x03 << ISC10);
		switch(sense) {
		case SENSE_LOW_LEVEL:
			break;
		case SENSE_ANY_EDGE:
			aux8 |= (0x01 << ISC10);
			break;
		case SENSE_FALLING_EDGE:
			aux8 |= (0x02 << ISC10);
			break;
		case SENSE_RISING_EDGE:
			aux8 |= (0x03 << ISC10);
			break;
		case SENSE_NO_CHANGE:
			break;
		default:
			return RESULT_INT_SENSE_VALUE_UNSUPPORTED;
			break;
		}
		EICRA = aux8;
	}

	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt int1
 * -------------------------------------------------------------------------- */

void int1ActivateInterrupt(void)
{
	setBit(EIMSK, INT1);
	return;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt int1
 * -------------------------------------------------------------------------- */

void int1DeactivateInterrupt(void)
{
	clrBit(EIMSK, INT1);
	return;
}

/* -----------------------------------------------------------------------------
 * Clears the external interrupt int1 request
 * -------------------------------------------------------------------------- */

void int1ClearInterruptRequest(void)
{
	setBit(EIFR, INTF1);
	return;
}

/* -----------------------------------------------------------------------------
 * Enables the external interrupt pcint in port B
 * -------------------------------------------------------------------------- */

void pcint7_0Enable(void)
{
	setBit(PCICR, PCIE0);
	return;
}

/* -----------------------------------------------------------------------------
 * Disables the external interrupt pcint in port B
 * -------------------------------------------------------------------------- */

void pcint7_0Disable(void)
{
	clrBit(PCICR, PCIE0);
	return;
}

/* -----------------------------------------------------------------------------
 * Disables the external interrupt pcint in port B
 * -------------------------------------------------------------------------- */

void pcint7_0ClearInterruptRequest(void)
{
	setBit(PCIFR, PCIF0);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint0 and configures port mode in PB0
 * -------------------------------------------------------------------------- */

resultValue_t pcint0ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB0);
		setBit(DDRB, PB0);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB0);
		setBit(DDRB, PB0);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB0);
		clrBit(DDRB, PB0);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB0);
		clrBit(DDRB, PB0);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT0);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint0 in PB0
 * -------------------------------------------------------------------------- */

void pcint0DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT0);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint1 and configures port mode in PB1
 * -------------------------------------------------------------------------- */

resultValue_t pcint1ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB1);
		setBit(DDRB, PB1);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB1);
		setBit(DDRB, PB1);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB1);
		clrBit(DDRB, PB1);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB1);
		clrBit(DDRB, PB1);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT1);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint1 in PB1
 * -------------------------------------------------------------------------- */

void pcint1DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT1);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint2 and configures port mode in PB2
 * -------------------------------------------------------------------------- */

resultValue_t pcint2ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB2);
		setBit(DDRB, PB2);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB2);
		setBit(DDRB, PB2);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB2);
		clrBit(DDRB, PB2);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB2);
		clrBit(DDRB, PB2);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT2);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint2 in PB2
 * -------------------------------------------------------------------------- */

void pcint2DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT2);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint3 and configures port mode in PB3
 * -------------------------------------------------------------------------- */

resultValue_t pcint3ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB3);
		setBit(DDRB, PB3);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB3);
		setBit(DDRB, PB3);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB3);
		clrBit(DDRB, PB3);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB3);
		clrBit(DDRB, PB3);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT3);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint3 in PB3
 * -------------------------------------------------------------------------- */

void pcint3DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT3);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint4 and configures port mode in PB4
 * -------------------------------------------------------------------------- */

resultValue_t pcint4ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB4);
		setBit(DDRB, PB4);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB4);
		setBit(DDRB, PB4);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB4);
		clrBit(DDRB, PB4);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB4);
		clrBit(DDRB, PB4);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT4);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint4 in PB4
 * -------------------------------------------------------------------------- */

void pcint4DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT4);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint5 and configures port mode in PB5
 * -------------------------------------------------------------------------- */

resultValue_t pcint5ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB5);
		setBit(DDRB, PB5);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB5);
		setBit(DDRB, PB5);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB5);
		clrBit(DDRB, PB5);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB5);
		clrBit(DDRB, PB5);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT5);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint5 in PB5
 * -------------------------------------------------------------------------- */

void pcint5DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT5);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint6 and configures port mode in PB6
 * -------------------------------------------------------------------------- */

resultValue_t pcint6ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB6);
		setBit(DDRB, PB6);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB6);
		setBit(DDRB, PB6);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB6);
		clrBit(DDRB, PB6);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB6);
		clrBit(DDRB, PB6);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT6);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint6 in PB6
 * -------------------------------------------------------------------------- */

void pcint6DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT6);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint7 and configures port mode in PB7
 * -------------------------------------------------------------------------- */

resultValue_t pcint7ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTB, PB7);
		setBit(DDRB, PB7);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTB, PB7);
		setBit(DDRB, PB7);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTB, PB7);
		clrBit(DDRB, PB7);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTB, PB7);
		clrBit(DDRB, PB7);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK0, PCINT7);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint7 in PB7
 * -------------------------------------------------------------------------- */

void pcint7DeactivateInterrupt(void)
{
	clrBit(PCMSK0, PCINT7);
	return;
}

/* -----------------------------------------------------------------------------
 * Enables the external interrupt pcint in port C
 * -------------------------------------------------------------------------- */

void pcint14_8Enable(void)
{
	setBit(PCICR, PCIE1);
	return;
}

/* -----------------------------------------------------------------------------
 * Disables the external interrupt pcint in port C
 * -------------------------------------------------------------------------- */

void pcint14_8Disable(void)
{
	clrBit(PCICR, PCIE1);
	return;
}

/* -----------------------------------------------------------------------------
 * Disables the external interrupt pcint in port C
 * -------------------------------------------------------------------------- */

void pcint14_8ClearInterruptRequest(void)
{
	setBit(PCIFR, PCIF1);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint8 and configures port mode in PC0
 * -------------------------------------------------------------------------- */

resultValue_t pcint8ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC0);
		setBit(DDRC, PC0);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC0);
		setBit(DDRC, PC0);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC0);
		clrBit(DDRC, PC0);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC0);
		clrBit(DDRC, PC0);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT8);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint8 in PC0
 * -------------------------------------------------------------------------- */

void pcint8DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT8);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint9 and configures port mode in PC1
 * -------------------------------------------------------------------------- */

resultValue_t pcint9ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC1);
		setBit(DDRC, PC1);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC1);
		setBit(DDRC, PC1);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC1);
		clrBit(DDRC, PC1);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC1);
		clrBit(DDRC, PC1);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT9);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint9 in PC1
 * -------------------------------------------------------------------------- */

void pcint9DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT9);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint10 and configures port mode in PC2
 * -------------------------------------------------------------------------- */

resultValue_t pcint10ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC2);
		setBit(DDRC, PC2);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC2);
		setBit(DDRC, PC2);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC2);
		clrBit(DDRC, PC2);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC2);
		clrBit(DDRC, PC2);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT10);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint10 in PC2
 * -------------------------------------------------------------------------- */

void pcint10DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT10);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint11 and configures port mode in PC3
 * -------------------------------------------------------------------------- */

resultValue_t pcint11ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC3);
		setBit(DDRC, PC3);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC3);
		setBit(DDRC, PC3);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC3);
		clrBit(DDRC, PC3);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC3);
		clrBit(DDRC, PC3);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT11);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint11 in PC3
 * -------------------------------------------------------------------------- */

void pcint11DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT11);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint12 and configures port mode in PC4
 * -------------------------------------------------------------------------- */

resultValue_t pcint12ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC4);
		setBit(DDRC, PC4);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC4);
		setBit(DDRC, PC4);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC4);
		clrBit(DDRC, PC4);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC4);
		clrBit(DDRC, PC4);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT12);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint12 in PC4
 * -------------------------------------------------------------------------- */

void pcint12DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT12);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint13 and configures port mode in PC5
 * -------------------------------------------------------------------------- */

resultValue_t pcint13ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC5);
		setBit(DDRC, PC5);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC5);
		setBit(DDRC, PC5);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC5);
		clrBit(DDRC, PC5);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC5);
		clrBit(DDRC, PC5);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT13);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint13 in PC5
 * -------------------------------------------------------------------------- */

void pcint13DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT13);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint14 and configures port mode in PC6
 * -------------------------------------------------------------------------- */

resultValue_t pcint14ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTC, PC6);
		setBit(DDRC, PC6);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTC, PC6);
		setBit(DDRC, PC6);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTC, PC6);
		clrBit(DDRC, PC6);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTC, PC6);
		clrBit(DDRC, PC6);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK1, PCINT14);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint14 in PC6
 * -------------------------------------------------------------------------- */

void pcint14DeactivateInterrupt(void)
{
	clrBit(PCMSK1, PCINT14);
	return;
}

/* -----------------------------------------------------------------------------
 * Enables the external interrupt pcint in port D
 * -------------------------------------------------------------------------- */

void pcint23_16Enable(void)
{
	setBit(PCICR, PCIE2);
	return;
}

/* -----------------------------------------------------------------------------
 * Disables the external interrupt pcint in port D
 * -------------------------------------------------------------------------- */

void pcint23_16Disable(void)
{
	clrBit(PCICR, PCIE2);
	return;
}

/* -----------------------------------------------------------------------------
 * Disables the external interrupt pcint in port D
 * -------------------------------------------------------------------------- */

void pcint23_16ClearInterruptRequest(void)
{
	setBit(PCIFR, PCIF2);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint16 and configures port mode in PD0
 * -------------------------------------------------------------------------- */

resultValue_t pcint16ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD0);
		setBit(DDRD, PD0);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD0);
		setBit(DDRD, PD0);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD0);
		clrBit(DDRD, PD0);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD0);
		clrBit(DDRD, PD0);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT16);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint16 in PD0
 * -------------------------------------------------------------------------- */

void pcint16DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT16);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint17 and configures port mode in PD1
 * -------------------------------------------------------------------------- */

resultValue_t pcint17ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD1);
		setBit(DDRD, PD1);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD1);
		setBit(DDRD, PD1);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD1);
		clrBit(DDRD, PD1);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD1);
		clrBit(DDRD, PD1);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT17);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint17 in PD1
 * -------------------------------------------------------------------------- */

void pcint17DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT17);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint18 and configures port mode in PD2
 * -------------------------------------------------------------------------- */

resultValue_t pcint18ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD2);
		setBit(DDRD, PD2);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD2);
		setBit(DDRD, PD2);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD2);
		clrBit(DDRD, PD2);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD2);
		clrBit(DDRD, PD2);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT18);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint18 in PD2
 * -------------------------------------------------------------------------- */

void pcint18DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT18);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint19 and configures port mode in PD3
 * -------------------------------------------------------------------------- */

resultValue_t pcint19ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD3);
		setBit(DDRD, PD3);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD3);
		setBit(DDRD, PD3);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD3);
		clrBit(DDRD, PD3);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD3);
		clrBit(DDRD, PD3);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT19);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint19 in PD3
 * -------------------------------------------------------------------------- */

void pcint19DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT19);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint20 and configures port mode in PD4
 * -------------------------------------------------------------------------- */

resultValue_t pcint20ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD4);
		setBit(DDRD, PD4);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD4);
		setBit(DDRD, PD4);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD4);
		clrBit(DDRD, PD4);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD4);
		clrBit(DDRD, PD4);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT20);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint20 in PD4
 * -------------------------------------------------------------------------- */

void pcint20DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT20);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint21 and configures port mode in PD5
 * -------------------------------------------------------------------------- */

resultValue_t pcint21ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD5);
		setBit(DDRD, PD5);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD5);
		setBit(DDRD, PD5);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD5);
		clrBit(DDRD, PD5);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD5);
		clrBit(DDRD, PD5);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT21);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint21 in PD5
 * -------------------------------------------------------------------------- */

void pcint21DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT21);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint22 and configures port mode in PD6
 * -------------------------------------------------------------------------- */

resultValue_t pcint22ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD6);
		setBit(DDRD, PD6);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD6);
		setBit(DDRD, PD6);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD6);
		clrBit(DDRD, PD6);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD6);
		clrBit(DDRD, PD6);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT22);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint22 in PD6
 * -------------------------------------------------------------------------- */

void pcint22DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT22);
	return;
}

/* -----------------------------------------------------------------------------
 * Activates the external interrupt pcint23 and configures port mode in PD7
 * -------------------------------------------------------------------------- */

resultValue_t pcint23ActivateInterrupt(portMode_t port)
{
	switch(port) {
	case PORT_OUTPUT_LOW:
		clrBit(PORTD, PD7);
		setBit(DDRD, PD7);
		break;
	case PORT_OUTPUT_HIGH:
		setBit(PORTD, PD7);
		setBit(DDRD, PD7);
		break;
	case PORT_INPUT_TRISTATE:
		clrBit(PORTD, PD7);
		clrBit(DDRD, PD7);
		break;
	case PORT_INPUT_PULL_UP:
		setBit(PORTD, PD7);
		clrBit(DDRD, PD7);
		break;
	case PORT_NO_CHANGE:
		break;
	default:
		return RESULT_PORT_VALUE_UNSUPPORTED;
		break;
	}
	setBit(PCMSK2, PCINT23);
	return RESULT_OK;
}

/* -----------------------------------------------------------------------------
 * Deactivates the external interrupt pcint23 in PD7
 * -------------------------------------------------------------------------- */

void pcint23DeactivateInterrupt(void)
{
	clrBit(PCMSK2, PCINT23);
	return;
}
