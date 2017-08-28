/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			twiSlave.h
 * Module:			TWI Slave controller
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 * Version:			1.0
 * Last edition:	August 28, 2017
 * Purpose:			Interfaces a TWI Slave data bus
 * -------------------------------------------------------------------------- */

#ifndef __TWI_SLAVE_H
#define __TWI_SLAVE_H 10

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H < 123
#error Error 100 - The defintion file is outdated (globalDefines must be version 12.3 or greater).
#endif
#include <stdlib.h>

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef volatile uint8 twiBuffer_t;

typedef enum twiSlaveState_t {
    TWI_STX_ADR_ACK				= 0xA8,
    TWI_STX_DATA_ACK			= 0xB8,
    TWI_STX_DATA_NACK			= 0xC0,
    TWI_SRX_GEN_ACK				= 0x70,
    TWI_SRX_ADR_ACK				= 0x60,
    TWI_SRX_ADR_DATA_ACK		= 0x80,
    TWI_SRX_GEN_DATA_ACK		= 0x90,
    TWI_SRX_STOP_RESTART		= 0xA0,
    TWI_SRX_ADR_DATA_NACK		= 0x88,
    TWI_SRX_GEN_DATA_NACK		= 0x98,
    TWI_STX_DATA_ACK_LAST_BYTE	= 0xC8,
    TWI_BUS_ERROR				= 0x00
} twiSlaveState_t;

// -----------------------------------------------------------------------------
// Public functions declaration ------------------------------------------------

twiBuffer_t * twiSlaveInit(uint8 twiSlaveAddr, uint8 bufferSize, bool_t genCallAcceptance);

#endif