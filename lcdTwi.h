/* -----------------------------------------------------------------------------
 * Project:			GPDSE AVR8 Library
 * File:			lcdTwi.h
 * Module:			Character LCD controller Using PCF8594 over TWI
 * Author:			Leandro Schwarz
 *					Hazael dos Santos Batista
 * Build:			1
 * Last edition:	September 15, 2017
 * Purpose:			Character LCD controller over Two Wires Interface without
 *					support to busy flag (delay-driven)
 * ---------------------------------------------------------------------------*/

#ifndef __LCD_TWI_H_
#define __LCD_TWI_H_ 1

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "globalDefines.h"
#if __GLOBALDEFINES_H < 1
	#error Error 100 - The defintion file is outdated (globalDefines must be build 1).
#endif
#include <stdio.h>

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

#define LCD_CLEAR_SCREEN		0x01
#define LCD_CURSOR_HOME			0x02
#define LCD_ENTRY_SET			0x04
#define LCD_ENTRY_INCREMENT		0x02
#define LCD_ENTRY_DECREMENT		0x00
#define LCD_ENTRY_SHIFT			0x01
#define LCD_ENTRY_OVERWRITE		0x00
#define LCD_DISPLAY_OFF			0x08
#define LCD_DISPLAY_ON			0x0C
#define LCD_FUNCTION_RESET		0x30
#define LCD_FUNCTION_SET		0x20
#define LCD_FUNCTION_8_BITS		0x10
#define LCD_FUNCTION_4_BITS		0x00
#define LCD_FUNCTION_2_LINES	0x08
#define LCD_FUNCTION_1_LINE		0x00
#define LCD_FUNCTION_5x10_FONT	0x04
#define LCD_FUNCTION_5x8_FONT	0x00
#define LCD_CGRAM_ADRESS		0x40
#define LCD_DDRAM_ADRESS		0x80

// -----------------------------------------------------------------------------
// New data types --------------------------------------------------------------

typedef volatile struct lcdTwiConfiguration_t {
	// I/O ports
	uint8		pinE				: 3;
	uint8		pinRs				: 3;
	uint8		pinRw				: 3;
	uint8		pinBl				: 3;
	uint8		pinD4				: 3;
	uint8		pinD5				: 3;
	uint8		pinD6				: 3;
	uint8		pinD7				: 3;
	// Display hardware
	uint8		columns				: 6;
	uint8		lines				: 2;
	// Entry mode set
	uint8		entryIncDec			: 1;
	uint8		entryShiftDisplay	: 1;
	// Display and cursor configuration
	bool_t		cursorBlink			: 1;	// 0 off, 1 on
	uint8		cursorColumn		: 6;	// 0 to 39
	uint8		cursorLine			: 2;	// 0 to 3
	bool_t		cursorOn			: 1;	// 0 off, 1 on
	bool_t		displayOn			: 1;	// 0 off, 1 on
	// Unused bits
	uint8		unusedBits			: 3;
} lcdTwiConfiguration_t;

typedef enum lcdTwiSize_t {
	LCD_SIZE_UNDEFINED = 0,
	LCD_8X1		= 108,
	LCD_8X2		= 208,
	LCD_10x2	= 210,
	LCD_12X2	= 212,
	LCD_12X4	= 412,
	LCD_16X1	= 116,
	LCD_16X2	= 216,
	LCD_16X4	= 416,
	LCD_20X1	= 120,
	LCD_20X2	= 220,
	LCD_20X4	= 420,
	LCD_24X1	= 124,
	LCD_24X2	= 224,
	LCD_30X2	= 230,
	LCD_32X2	= 232,
	LCD_40X1	= 140,
	LCD_40X2	= 240
} lcdTwiSize_t;

typedef enum lcdTwiFont_t {
	LCD_FONT_5X8 = 0,
	LCD_FONT_5X10 = 1
} lcdTwiFont_t;

typedef enum lcdTwiShiftOverwrite_t {
	LCD_DISPLAY_OVERWRITE = 0,
	LCD_DISPLAY_SHIFT = 1,
	LCD_DISPLAY_NO_CHANGE = 0xFF
} lcdTwiShiftOverwrite_t;

typedef enum lcdTwiIncrementDecrement_t {
	LCD_DECREMENT = 0,
	LCD_INCREMENT = 1,
	LCD_INCDEC_NO_CHANGE = 0xFF
} lcdTwiIncrementDecrement_t;

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

extern FILE lcdTwiStream;
extern lcdTwiConfiguration_t * defaultDisplay;

// -----------------------------------------------------------------------------
// Macrofunctions --------------------------------------------------------------

#define createLcdTwi() (lcdTwiConfiguration_t){.pinE = 2, .pinRs = 0, .pinRw = 1, .pinBl = 3, .pinD4 = 4, .pinD5 = 5, .pinD6 = 6, .pinD7 = 7, .columns = 0, .lines = 0, .entryIncDec = LCD_INCREMENT, .entryShiftDisplay = LCD_DISPLAY_OVERWRITE, .cursorBlink = FALSE, .cursorColumn = 0, .cursorLine = 0, .cursorOn = FALSE, .displayOn = FALSE, .unusedBits = 0}

// -----------------------------------------------------------------------------
// Public functions declaration ------------------------------------------------

void lcdClearScreen(lcdTwiConfiguration_t * lcd);
void lcdCursor(lcdTwiConfiguration_t * lcd, logic_t state);
void lcdCursorBlink(lcdTwiConfiguration_t * lcd, logic_t state);
void lcdCursorGoTo(lcdTwiConfiguration_t * lcd, uint8 line, uint8 column);
void lcdCursorHome(lcdTwiConfiguration_t * lcd);
void lcdCursorMove(lcdTwiConfiguration_t * lcd, direction_t dir);
void lcdCursorMoveFirstLine(lcdTwiConfiguration_t * lcd);
void lcdCursorMoveNextLine(lcdTwiConfiguration_t * lcd);
void lcdDisplay(lcdTwiConfiguration_t * lcd, logic_t state);
void lcdDisplayShift(lcdTwiConfiguration_t * lcd, direction_t dir);
void lcdInit(lcdTwiConfiguration_t * lcd, lcdTwiSize_t size, lcdTwiFont_t font);
void lcdSetControlPort(lcdTwiConfiguration_t * lcd, vuint8 * controlDDR, vuint8 * controlPORT, uint8 controlE, uint8 controlRS);
void lcdSetDataPort(lcdTwiConfiguration_t * lcd, vuint8 * dataDDR, vuint8 * dataPORT, uint8 dataFirst);
void lcdSetEntryMode(lcdTwiConfiguration_t * lcd, lcdTwiIncrementDecrement_t dir, lcdTwiShiftOverwrite_t mode);
void lcdStdio(lcdTwiConfiguration_t * lcd);

// -----------------------------------------------------------------------------
// Functions for debug purposes ------------------------------------------------

uint8 lcdGetLine(lcdTwiConfiguration_t * lcd);
uint8 lcdGetColumn(lcdTwiConfiguration_t * lcd);

#endif
