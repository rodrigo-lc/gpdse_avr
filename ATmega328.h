/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			ATmega328.h
 * Module:			ATmega328 basic interface
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 * Build:			1
 * Last edition:	September 6, 2017
 * -------------------------------------------------------------------------- */

#ifndef __ATMEGA328_H
#define __ATMEGA328_H 1

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H != 1
	#error Error 100 - globalDefines.h - wrong build (globalDefines must be build 1).
#endif

#include <avr/io.h>
#include <util/atomic.h>

// -----------------------------------------------------------------------------
// System clock prescaler ------------------------------------------------------

resultValue_t	systemClockSetPrescaler(systemPrescalerValue_t prescaler);

// -----------------------------------------------------------------------------
// Internal pull-ups -----------------------------------------------------------

resultValue_t pullUpDisable(void);
resultValue_t pullUpEnable(void);


//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE
//////////////////////////// OLD FILE, MUST BE REMOVED BEFORE RELEASE

// -----------------------------------------------------------------------------
// Microcontroller constant identifier -----------------------------------------

#define MCU	_ATMEGA328_

// -----------------------------------------------------------------------------
// Some definitions that seemed to be forgotten in avr/io.h ---------------------

#ifndef SPMEN
	#define SPMEN	0
#endif

// -----------------------------------------------------------------------------
// External interrupts ---------------------------------------------------------

// INT0
resultValue_t	int0Config(portMode_t port, senseMode_t sense);
void			int0ActivateInterrupt(void);
void			int0DeactivateInterrupt(void);
void			int0ClearInterruptRequest(void);

// INT1
resultValue_t	int1Config(portMode_t port, senseMode_t sense);
void			int1ActivateInterrupt(void);
void			int1DeactivateInterrupt(void);
void			int1ClearInterruptRequest(void);

// PCINT7-0
void			pcint7_0Enable(void);
void			pcint7_0Disable(void);
void			pcint7_0ClearInterruptRequest(void);
resultValue_t	pcint0ActivateInterrupt(portMode_t port);
void			pcint0DeactivateInterrupt(void);
resultValue_t	pcint1ActivateInterrupt(portMode_t port);
void			pcint1DeactivateInterrupt(void);
resultValue_t	pcint2ActivateInterrupt(portMode_t port);
void			pcint2DeactivateInterrupt(void);
resultValue_t	pcint3ActivateInterrupt(portMode_t port);
void			pcint3DeactivateInterrupt(void);
resultValue_t	pcint4ActivateInterrupt(portMode_t port);
void			pcint4DeactivateInterrupt(void);
resultValue_t	pcint5ActivateInterrupt(portMode_t port);
void			pcint5DeactivateInterrupt(void);
resultValue_t	pcint6ActivateInterrupt(portMode_t port);
void			pcint6DeactivateInterrupt(void);
resultValue_t	pcint7ActivateInterrupt(portMode_t port);
void			pcint7DeactivateInterrupt(void);

// PCINT14-8
void			pcint14_8Enable(void);
void			pcint14_8Disable(void);
void			pcint14_8ClearInterruptRequest(void);
resultValue_t	pcint8ActivateInterrupt(portMode_t port);
void			pcint8DeactivateInterrupt(void);
resultValue_t	pcint9ActivateInterrupt(portMode_t port);
void			pcint9DeactivateInterrupt(void);
resultValue_t	pcint10ActivateInterrupt(portMode_t port);
void			pcint10DeactivateInterrupt(void);
resultValue_t	pcint11ActivateInterrupt(portMode_t port);
void			pcint11DeactivateInterrupt(void);
resultValue_t	pcint12ActivateInterrupt(portMode_t port);
void			pcint12DeactivateInterrupt(void);
resultValue_t	pcint13ActivateInterrupt(portMode_t port);
void			pcint13DeactivateInterrupt(void);
resultValue_t	pcint14ActivateInterrupt(portMode_t port);
void			pcint14DeactivateInterrupt(void);

// PCINT23-16
void			pcint23_16Enable(void);
void			pcint23_16Disable(void);
void			pcint23_16ClearInterruptRequest(void);
resultValue_t	pcint16ActivateInterrupt(portMode_t port);
void			pcint16DeactivateInterrupt(void);
resultValue_t	pcint17ActivateInterrupt(portMode_t port);
void			pcint17DeactivateInterrupt(void);
resultValue_t	pcint18ActivateInterrupt(portMode_t port);
void			pcint18DeactivateInterrupt(void);
resultValue_t	pcint19ActivateInterrupt(portMode_t port);
void			pcint19DeactivateInterrupt(void);
resultValue_t	pcint20ActivateInterrupt(portMode_t port);
void			pcint20DeactivateInterrupt(void);
resultValue_t	pcint21ActivateInterrupt(portMode_t port);
void			pcint21DeactivateInterrupt(void);
resultValue_t	pcint22ActivateInterrupt(portMode_t port);
void			pcint22DeactivateInterrupt(void);
resultValue_t	pcint23ActivateInterrupt(portMode_t port);
void			pcint23DeactivateInterrupt(void);


// -----------------------------------------------------------------------------
// Timer/counter 1 -------------------------------------------------------------

#endif
