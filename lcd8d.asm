; ------------------------------------------------------------------------------
; Project:	16x2 Character Liquid Crystal Display Controller
; File:		lcd8d.asm
; Author:	Leandro Schwarz
; Created:	2015-11-02
; Modified:	2015-11-02
; Version:	1.0
; Notes:	LCD controller, 8 bits interface, delay driven (no busy flag)
; ------------------------------------------------------------------------------

; ------------------------------------------------------------------------------
; Include files
; ------------------------------------------------------------------------------
.include "m328pdef.inc"

; ------------------------------------------------------------------------------
; Register definitions
; ------------------------------------------------------------------------------
.def	bcd0				= R13		; BCD value digits 1 and 0
.def	bcd1				= R14		; BCD value digits 3 and 2
.def	bcd2				= R15		; BCD value digit 4
.def	binL				= R16		; binary value Low byte
.def	binH				= R17		; binary value High byte
.def	bin2BCDcounter		= R18		; loop counter
.def	bin2BCDtemp			= R19		; temporary value
.def	lcdTmp				= R20		; LCD temporary register

; ------------------------------------------------------------------------------
; Constant definitions
; ------------------------------------------------------------------------------
.equ	LCD_DATA_DDR		= DDRD			; LCD data lines
.equ	LCD_DATA_PORT		= PORTD
.equ	LCD_CONTROL_DDR		= DDRB			; LCD control lines
.equ	LCD_CONTROL_PORT	= PORTB
.equ	LCD_CONTROL_E		= PB0
.equ	LCD_CONTROL_RS		= PB1
.equ	LCD_FIRST_LINE		= 0x00			; LCD DDRAM address
.equ	LCD_SECOND_LINE		= 0x40
.equ	LCD_CLEAR_SCREEN	= 0x01			; LCD commands
.equ	LCD_CURSOR_HOME		= 0x02
.equ	LCD_ENTRY_MODE		= 0x06
.equ	LCD_DISPLAY_OFF		= 0x08
.equ	LCD_DISPLAY_ON		= 0x0C
.equ	LCD_RESET			= 0x30
.equ	LCD_FUNCTION_SET_8	= 0x38
.equ	LCD_CURSOR_MOVE		= 0x80
.equ	AtBCD0				= 13		; address of bcd0
.equ	AtBCD2				= 15		; address of bcd1

; ------------------------------------------------------------------------------
; Subroutine:	lcdInit
; Purpose:		initialize the LCD module using 8 data lines and delays
; Notes:		no register is changed
; ------------------------------------------------------------------------------
lcdInit:
	PUSH	lcdTmp							; Pushing registers
	LDI		lcdTmp, 0x00					; I/O configuration
	OUT		LCD_DATA_PORT, lcdTmp
	LDI		lcdTmp, 0xFF
	OUT		LCD_DATA_DDR, lcdTmp
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	SBI		LCD_CONTROL_DDR, LCD_CONTROL_E
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_RS
	SBI		LCD_CONTROL_DDR, LCD_CONTROL_RS
	LDI		lcdTmp, LCD_RESET				; Reset the LCD controller.
	CALL	lcdWriteCommand
	LDI		lcdTmp, 5
	CALL	lcdDelayXms
	LDI		lcdTmp, LCD_RESET
	CALL	lcdWriteCommand
	LDI		lcdTmp, 100
	CALL	lcdDelayXus
	LDI		lcdTmp, LCD_RESET
	CALL	lcdWriteCommand
	LDI		lcdTmp, 200
	CALL	lcdDelayXus
	LDI		lcdTmp, LCD_FUNCTION_SET_8		; LCD function mode set
	CALL	lcdWriteCommand
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	LDI		lcdTmp, LCD_DISPLAY_OFF			; Turns display off
	CALL	lcdWriteCommand
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	LDI		lcdTmp, LCD_CLEAR_SCREEN		; Clears LCD screen
	CALL	lcdWriteCommand
	LDI		lcdTmp, 2
	CALL	lcdDelayXms
	LDI		lcdTmp, LCD_ENTRY_MODE			; LCD entry mode set
	CALL	lcdWriteCommand
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	LDI		lcdTmp, LCD_DISPLAY_ON			; Turns display on
	CALL	lcdWriteCommand
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	POP		lcdTmp							; Popping registers back
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdWriteData
; Purpose:		writes a data byte at the LCD
; Notes:		the data byte must be written in lcdTmp before calling the
;				subroutine
; ------------------------------------------------------------------------------
lcdWriteData:
	SBI		LCD_CONTROL_PORT, LCD_CONTROL_RS
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	OUT		LCD_DATA_PORT, lcdTmp
	SBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	CALL	lcdDelay1us
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	CALL	lcdDelay1us
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdWriteCommand
; Purpose:		writes a command byte at the LCD
; Notes:		the command byte must be written in lcdTmp before calling the
;				subroutine
; ------------------------------------------------------------------------------
lcdWriteCommand:
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_RS
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	OUT		LCD_DATA_PORT, lcdTmp
	SBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	CALL	lcdDelay1us
	CBI		LCD_CONTROL_PORT, LCD_CONTROL_E
	CALL	lcdDelay1us
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdWriteString
; Purpose:		writes a string at the LCD
; Notes:		the string address must be loaded into the Z register and the 
;				DDRAM address must be loaded into lcdTmp register before calling
;				the subroutine. The string must end with a NULL character 0
; ------------------------------------------------------------------------------
lcdWriteString:
	PUSH	ZH								; Pushing registers
	PUSH	ZL
	LSL		ZL								; shift the pointer one bit left for the lpm instruction
	ROL		ZH
	ORI		lcdTmp, LCD_CURSOR_MOVE			; Configures the DDRAM address
	CALL	lcdWriteCommand
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
lcdWriteStringLoop:							; Write string
	LPM		lcdTmp, Z+
	CPI		lcdTmp, 0
	BREQ	lcdWriteStringEnd
	CALL	lcdWriteData
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	JMP		lcdWriteStringLoop
lcdWriteStringEnd:
	POP		ZL								; Popping registers back
	POP		ZH
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdWriteInt16
; Purpose:		writes a 16 bit integer at the LCD
; Notes:		the number must be loaded into lcdTemp register before calling
;				the subroutine
; ------------------------------------------------------------------------------
lcdWriteInt16:
	MOV		lcdTmp, bcd2					; BCD Digit 4
	ANDI	lcdTmp, 0x0F
	CALL	lcdWriteNumber
	MOV		lcdTmp, bcd1					; BCD Digit 3
	LSR lcdTmp
	LSR lcdTmp
	LSR lcdTmp
	LSR lcdTmp
	ANDI	lcdTmp, 0x0F
	CALL	lcdWriteNumber
	MOV		lcdTmp, bcd1					; BCD Digit 2
	ANDI	lcdTmp, 0x0F
	CALL	lcdWriteNumber
	MOV		lcdTmp, bcd0					; BCD Digit 1
	LSR lcdTmp
	LSR lcdTmp
	LSR lcdTmp
	LSR lcdTmp
	ANDI	lcdTmp, 0x0F
	CALL	lcdWriteNumber
	MOV		lcdTmp, bcd0					; BCD Digit 0
	ANDI	lcdTmp, 0x0F
	CALL	lcdWriteNumber
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdWriteNumber
; Purpose:		writes a number at the LCD
; Notes:		the number must be loaded into lcdTemp register before calling
;				the subroutine
; ------------------------------------------------------------------------------
lcdWriteNumber:
	PUSH	R19								; Pushing registers
	ANDI	lcdTmp, 0x0F
	LDI		R19, 0x30
	ADD		lcdTmp, R19
	CALL	lcdWriteData
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	POP		R19								; Popping registers back
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdSetDdramAddress
; Purpose:		sets the LCD DDRAM address
; Notes:		the address must be loaded into lcdTemp register before calling
;				the subroutine
; ------------------------------------------------------------------------------
lcdSetDdramAddress:
	ORI		lcdTmp, LCD_CURSOR_MOVE
	CALL	lcdWriteCommand
	LDI		lcdTmp, 40
	CALL	lcdDelayXus
	RET

	; ------------------------------------------------------------------------------
; Subroutine:	lcdClearScreen
; Purpose:		clears the LCD screen
; Notes:		no register is changed
; ------------------------------------------------------------------------------
lcdClearScreen:
	PUSH	lcdTmp
	LDI		lcdTmp, LCD_CLEAR_SCREEN		; Clears LCD screen
	CALL	lcdWriteCommand
	LDI		lcdTmp, 2
	CALL	lcdDelayXms
	POP		lcdTmp
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdDelayXms
; Purpose:		generate a variable delay duration loop in milliseconds
; Notes:		makes successive calls of function lcdDelay1ms using lcdTmp as
;				counter variable
; ------------------------------------------------------------------------------
lcdDelayXms:
	CALL	lcdDelay1ms
	DEC		lcdTmp
	BRNE	lcdDelayXms
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdDelayXus
; Purpose:		generate a variable delay duration loop in microseconds
; Notes:		makes successive calls of function lcdDelay1us using lcdTmp as
;				counter variable
; ------------------------------------------------------------------------------
lcdDelayXus:
	CALL	lcdDelay1us
	DEC		lcdTmp
	BRNE	lcdDelayXus
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdDelay1ms
; Purpose:		1ms delay in 16MHz
; Notes:		no register is changed
; ------------------------------------------------------------------------------
lcdDelay1ms:
	PUSH	R18
	PUSH	R19
	LDI		R18, 21
	LDI		R19, 193
lcdDelay1msLoop:
	DEC		R19
	BRNE	lcdDelay1msLoop
	DEC		R18
	BRNE	lcdDelay1msLoop
	POP		R19
	POP		R18
	NOP
	NOP
	RET

; ------------------------------------------------------------------------------
; Subroutine:	lcdDelay1us
; Purpose:		1us delay in 16MHz
; Notes:		no register is changed
; ------------------------------------------------------------------------------
lcdDelay1us:
	PUSH	lcdTmp
	POP		lcdTmp
	PUSH	lcdTmp
	POP		lcdTmp
	RET

; ------------------------------------------------------------------------------
; Subroutine:	bin2BCD16
; Purpose:		converts a 16-bit Binary to 3 bytes BCD (6 nibbles)
; Notes:		the binary number must be loaded into (binH:binL) and the result
;				is stored into (bcd2:bcd1:bcd0), with the MSD of the BCD code in
;				the lowermost nibble of bcd2.
; ------------------------------------------------------------------------------
bin2BCD16:
	PUSH	bin2BCDcounter
	PUSH	bin2BCDtemp
	PUSH	ZH
	PUSH	ZL
	LDI		bin2BCDcounter, 16				; Initializes loop counter
	CLR		bcd2							; Clear result registers
	CLR		bcd1
	CLR		bcd0
	CLR		ZH
bBCDx_1:
	LSL		binL							; shift input value
	ROL		binH							; through all bytes
	ROL		bcd0							;
	ROL		bcd1
	ROL		bcd2
	DEC		bin2BCDcounter					; decrement loop counter
	BRNE	bBCDx_2							; if counter not zero
	POP		ZL
	POP		ZH
	POP		bin2BCDtemp
	POP		bin2BCDcounter
	RET										; return
bBCDx_2:
	LDI		R30, AtBCD2+1					; Z points to result MSB + 1
bBCDx_3:
	LD		bin2BCDtemp, -Z					; get (Z) with pre-decrement
	SUBI	bin2BCDtemp, -$03				; add 0x03
	SBRC	bin2BCDtemp, 3					; if bit 3 not clear
	ST		Z, bin2BCDtemp					; store back
	LD		bin2BCDtemp, Z					; get (Z)
	SUBI	bin2BCDtemp, -$30				; add 0x30
	SBRC	bin2BCDtemp, 7					; if bit 7 not clear
	ST		Z, bin2BCDtemp					; store back
	CPI		ZL, AtBCD0						; done all three?
	BRNE	bBCDx_3							; loop again if not
	RJMP	bBCDx_1