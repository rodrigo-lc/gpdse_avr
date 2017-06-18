/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			circularBuffer.h
 * Module:			Circular Buffer Implementation
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H 130

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H != 130
	#error Error 100 - globalDefines.h - wrong version (globalDefines must be version 13.0).
#endif
#include <stdlib.h>

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef struct circularBuffer_t{
	uint8 nextRead;
	uint8 nextWrite;
	uint8 size;
	uint8 occupation;
	uint8 * data;
} circularBuffer_t;

// -----------------------------------------------------------------------------
// Macrofunctions --------------------------------------------------------------

#define createCircularBuffer(object) volatile circularBuffer_t object = {.nextRead = 0, .nextWrite = 0, .size = 0, .occupation = 0, .data = NULL}

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

bool_t	circularBufferInit(volatile circularBuffer_t * buffer, uint8 bufferSize/*, variable_type */);
bool_t	circularBufferPushData(volatile circularBuffer_t * buffer, uint8 data);
uint8	circularBufferPopData(volatile circularBuffer_t * buffer);
bool_t	circularBufferIsEmpty(volatile circularBuffer_t * buffer);
