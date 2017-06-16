/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Integrated Library
 * File:			globalDefines.h
 * Module:			Global definitions file for the GPDSE Project
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-16
 * ---------------------------------------------------------------------------*/

#ifndef __GLOBALDEFINES_H
	#define __GLOBALDEFINES_H 130

// -----------------------------------------------------------------------------
// Define Clock Frequency ------------------------------------------------------

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

// -----------------------------------------------------------------------------
// Bit handling macro functions ------------------------------------------------

#ifndef setBit
	#define setBit(reg, bit)					((reg) |= (1 << (bit)))
#endif
#ifndef clrBit
	#define clrBit(reg, bit)					((reg) &= ~(1 << (bit)))
#endif
#ifndef cplBit
	#define cplBit(reg, bit)					((reg) ^= (1 << (bit)))
#endif
#ifndef isBitSet
	#define isBitSet(reg, bit)					(((reg) >> (bit)) & 1)
#endif
#ifndef isBitClr
	#define isBitClr(reg, bit)					(!(((reg) >> (bit)) & 1))
#endif
#ifndef waitUntilBitIsSet
	#define waitUntilBitIsSet(reg, bit)			do{}while(isBitClr((reg), (bit)))
#endif
#ifndef waitUntilBitIsClear
	#define waitUntilBitIsClear(reg, bit)		do{}while(isBitSet((reg), (bit)))
#endif
#ifndef setMask
	#define setMask(reg, mask, offset)			((reg) |= ((mask) << (offset)))
#endif
#ifndef clrMask
	#define clrMask(reg, mask, offset)			((reg) &= ~((mask) << (offset)))
#endif
#ifndef cplMask
	#define cplMask(reg, mask, offset)			((reg) ^= ((mask) << (offset)))
#endif

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef signed char			int8;
typedef signed int			int16;
typedef signed long int		int32;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned int		uint16;
typedef unsigned long int	uint32;
typedef unsigned long long	uint64;

typedef enum bool_t{
	FALSE = 0,
	TRUE = 1
} bool_t;

typedef enum logic_t{
	LOW = 0,
	HIGH = 1,
	OFF = 0,
	ON = 1
} logic_t;

typedef enum direction_t{
	LEFT = 0,
	RIGHT = 1,
	UP = 0,
	DOWN = 1,
	CLOCKWISE = 0,
	COUNTERCLOCKWISE = 1
} direction_t;

#endif