/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			circularBuffer.c
 * Module:			Circular Buffer Implementation
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */
 
// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "circularBuffer.h"
#if __CIRCULAR_BUFFER_H != 130
	#error Error 101 - Version mismatch on header and source code files (circularBuffer).
#endif

/* -----------------------------------------------------------------------------
 * Initializes the circular buffer, alocating memory.
 * -------------------------------------------------------------------------- */

bool_t circularBufferInit(volatile circularBuffer_t * buffer, uint8 bufferSize/*, variable_type */)
{
	if(bufferSize == 0)
		return FALSE;

	// Memory allocation
	buffer->data = (uint8 *)realloc(buffer->data, bufferSize/* * sizeof(variable_type)*/);
	if(buffer->data == NULL)
		return FALSE;

	buffer->size = bufferSize;
	buffer->nextRead = 0;
	buffer->nextWrite = 0;
	buffer->size = 0;
	buffer->occupation = 0;

	return TRUE;
}

/* -----------------------------------------------------------------------------
 * Pushes data into circular buffer. The function returns FALSE if buffer is full.
 * -------------------------------------------------------------------------- */

bool_t circularBufferPushData(volatile circularBuffer_t * buffer, uint8 data)
{
	if(((buffer->nextWrite + 1) % buffer->size) != buffer->nextRead){
		buffer->data[buffer->nextWrite] = data;
		buffer->nextWrite = (buffer->nextWrite + 1) % buffer->size;
		buffer->occupation++;

		return TRUE;

	return FALSE;
}

/* -----------------------------------------------------------------------------
 * Pops data from the circular buffer. If the buffer is empty, the last
 * retrieved data will be returned and the pointer will not be changed. The
 * circularBufferIsEmpty() function must be called to check if there is data to
 * be read in the buffer.
 * -------------------------------------------------------------------------- */

uint8 circularBufferPopData(volatile circularBuffer_t * buffer)
{
	uint8 data = buffer->data[buffer->nextRead];
	if(buffer->occupation > 0){
		buffer->nextRead = (buffer->nextRead + 1) % buffer->size;
		buffer->occupation--;
	}

	return data;
}

/* -----------------------------------------------------------------------------
 * Verifies if there is data unread in the circular buffer. Must be called
 * before reading the buffer. Returns TRUE if there is unread data into buffer.
 * -------------------------------------------------------------------------- */

bool_t circularBufferIsEmpty(volatile circularBuffer_t * buffer)
{
	if(buffer->occupation == 0)
		return TRUE;

	return FALSE;
}
