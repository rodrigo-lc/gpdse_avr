/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			adc.h
 * Module:			ADC interface
 * Author:			Leandro Schwarz
 * Version:			13.0
 * Last edition:	2017-06-17
 * -------------------------------------------------------------------------- */

#ifndef __ADC_H
#define __ADC_H 130

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H != 130
	#error Error 100 - globalDefines.h - wrong version (globalDefines must be version 13.0).
#endif

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

#define ADC_INTERNAL_REFERENCE_VALUE_V	1.1
#define ADC_INTERNAL_REFERENCE_VALUE_MV	1100

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef enum adcPrescaler_t{
	ADC_PRESCALER_OFF = 0,
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4 = 2,
	ADC_PRESCALER_8 = 3,
	ADC_PRESCALER_16 = 4,
	ADC_PRESCALER_32 = 5,
	ADC_PRESCALER_64 = 6,
	ADC_PRESCALER_128 = 7,
	ADC_PRESCALER_NO_CHANGE = 255
} adcPrescaler_t;

typedef enum adcReference_t{
	ADC_REFERENCE_EXTERNAL = 0,
	ADC_REFERENCE_POWER_SUPPLY = 1,
	ADC_REFERENCE_INTERNAL = 3,
	ADC_REFERENCE_NO_CHANGE = 255
} adcReference_t;

typedef enum adcChannel_t{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1 = 1,
	ADC_CHANNEL_2 = 2,
	ADC_CHANNEL_3 = 3,
	ADC_CHANNEL_4 = 4,
	ADC_CHANNEL_5 = 5,
	ADC_CHANNEL_6 = 6,
	ADC_CHANNEL_7 = 7,
	ADC_CHANNEL_TEMPERATURE = 8,
	ADC_CHANNEL_BAND_GAP = 14,
	ADC_CHANNEL_GND = 15,
	ADC_CHANNEL_NO_CHANGE = 255
} adcChannel_t;

typedef enum adcDigitalInputs_t{
	ADC_INPUT_0 = 0,
	ADC_INPUT_1 = 1,
	ADC_INPUT_2 = 2,
	ADC_INPUT_3 = 3,
	ADC_INPUT_4 = 4,
	ADC_INPUT_5 = 5,
	ADC_INPUT_6 = 6,
	ADC_INPUT_7 = 7
} adcDigitalInputs_t;

typedef enum adcMode_t{
	ADC_MODE_SINGLE_CONVERSION = 0,
	ADC_MODE_AUTO_CONTINUOUS,
	ADC_MODE_AUTO_ANALOG_COMP,
	ADC_MODE_AUTO_INT0,
	ADC_MODE_AUTO_TIMER0_COMPA,
	ADC_MODE_AUTO_TIMER0_OVERFLOW,
	ADC_MODE_AUTO_TIMER1_COMPB,
	ADC_MODE_AUTO_TIMER1_OVERFLOW,
	ADC_MODE_AUTO_TIMER1_CAPTURE,
	ADC_MODE_NO_CHANGE = 255
} adcMode_t;

typedef enum adcDataPresentation_t{
	ADC_ADJUST_RESULT_LEFT = 0,
	ADC_ADJUST_RESULT_RIGHT,
	ADC_ADJUST_RESULT_NO_CHANGE = 255	
} adcDataPresentation_t;

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

resultValue_t	adcConfig(adcMode_t mode, adcReference_t reference, adcPrescaler_t  prescaler);
resultValue_t	adcSelectChannel(adcChannel_t channel);
resultValue_t	adcEnableDigitalInput(adcDigitalInputs_t flagInputs);
resultValue_t	adcDisableDigitalInput(adcDigitalInputs_t flagInputs);
resultValue_t	adcDataPresentation(adcDataPresentation_t presentation);
resultValue_t	adcEnable(void);
resultValue_t	adcDisable(void);
resultValue_t	adcClearInterruptRequest(void);
resultValue_t	adcActivateInterrupt(void);
resultValue_t	adcDeactivateInterrupt(void);
resultValue_t	adcStartConversion(void);
bool_t			adcIsBusy(void);
resultValue_t	adcWaitUntilConversionFinish(void);

#endif
