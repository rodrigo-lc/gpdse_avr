/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			spiMaster.c
 * Module:			Serial Peripheral Interface module in master mode
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 * Build:			1
 * Last edition:	September 6, 2017
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "spiMaster.h"
#if __SPIMASTER_H != 1
	#error Error 101 - Build mismatch on header and source code files (spiMaster).
#endif

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------



resultValue_t spiMasterDeviceSetPort(spiMasterDevice_t * device, vuint8 * ssDdr, vuint8 * ssPort, vuint8 ssBit)
{
	device->ssDdr = ssDdr;
	device->ssPort = ssPort;
	device->ssBit = ssBit;

	setBit(*(device->ssPort), device->ssBit);
	setBit(*(device->ssDdr), device->ssBit);

	return RESULT_OK;
}

resultValue_t spiMasterDeviceSetMode(spiMasterDevice_t * device, spiModes_t mode)
{
	device->mode = mode;

	return RESULT_OK;
}

resultValue_t spiMasterDeviceSetPrescaler(spiMasterDevice_t * device, spiClockPrescaler_t prescaler)
{
	device->prescaler = prescaler;

	return RESULT_OK;
}

resultValue_t spiMasterDeviceSetDataOrder(spiMasterDevice_t * device, spiDataOrder_t dataOrder)
{
	device->dataOrder = dataOrder;

	return RESULT_OK;
}

resultValue_t spiMasterInterruptEnable()
{
	setBit(SPCR, SPIE);

	return RESULT_OK;
}

resultValue_t spiMasterInterruptDisable()
{
	clrBit(SPCR, SPIE);

	return RESULT_OK;
}

resultValue_t spiMasterInit(void)
{
	__attribute__((unused)) vuint8 aux8;

	// Port configuration
	setBit(SPI_DDR, SPI_MOSI);
	clrBit(SPI_DDR, SPI_MISO);
	setBit(SPI_DDR, SPI_SCLK);
	// Master mode
	setBit(SPCR, MSTR);
	// Clock prescaler 128
	clrBit(SPSR, SPI2X);
	setMask(SPCR, 0x03, SPR0);
	// SPI mode
	clrBit(SPCR, CPOL);
	clrBit(SPCR, CPHA);
	// SPI enable
	setBit(SPCR, SPE);
	// Clears Interrupt flags
	aux8 = SPSR;
	aux8 = SPDR;

	return RESULT_OK;
}

resultValue_t spiMasterActivateDevice(spiMasterDevice_t * device)
{
	clrBit(SPCR, MSTR);
	// Clock prescaler 128
	if(isBitSet(device->prescaler, 2)) {
		setBit(SPSR, SPI2X);
	} else {
		clrBit(SPSR, SPI2X);
	}
	clrMask(SPCR, 0x03, SPR0);
	setMask(SPCR, (device->prescaler & 0x03), SPR0);
	// SPI mode
	switch(device->mode) {
	case 0:
		clrBit(SPCR, CPOL);
		clrBit(SPCR, CPHA);
		break;
	case 1:
		clrBit(SPCR, CPOL);
		setBit(SPCR, CPHA);
		break;
	case 2:
		setBit(SPCR, CPOL);
		clrBit(SPCR, CPHA);
		break;
	case 3:
		setBit(SPCR, CPOL);
		setBit(SPCR, CPHA);
		break;
	}
	// Data order
	if(device->dataOrder) {
		setBit(SPCR, DORD);
	} else {
		clrBit(SPCR, DORD);
	}
	setBit(SPCR, MSTR);

	clrBit(*(device->ssPort), device->ssBit);

	return RESULT_OK;
}

uint8 spiMasterSendReceiveData(uint8 data)
{
	SPDR = data;
	waitUntilBitIsSet(SPSR, SPIF);
	data = SPDR;

	return data;
}

resultValue_t spiMasterDeactivateDevice(spiMasterDevice_t * device)
{
	setBit(*(device->ssPort), device->ssBit);

	return RESULT_OK;
}

