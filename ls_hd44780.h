/* -----------------------------------------------------------------------------
 * File:			LS_HD44780.h
 * Module:			LCD HD44780 Controller Interface
 * Author:			Leandro Schwarz
 * Version:			3.0
 * Last edition:	09/08/2013
 * -------------------------------------------------------------------------- */

#ifndef __LS_HD44780_H
#define __LS_HD44780_H 30

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "LS_defines.h"
#if __LS_DEFINES_H < 110
	#error Error 100 - The defintion file is outdated (LS_defines must be version 11.0 or greater).
#endif
#include <stdio.h>

// -----------------------------------------------------------------------------
// New data type definition ----------------------------------------------------

typedef struct lcdConfiguration_t{
	uint8 line			: 2;	// 0 to 3
	uint8 column		: 6;	// 0 to 39
	uint8 displayOn		: 1;	// 0 off, 1 on
	uint8 cursorOn		: 1;	// 0 off, 1 on
	uint8 cursorBlink	: 1;	// 0 off, 1 on
	uint8 moveDirection	: 1;	// 0 left, 1 right
	uint8 insert		: 1;	// 0 off, 1 on
	uint8 dataBits		: 1;	// 0 4-bits, 1 8-bits
	uint8 fontSize		: 1;	// 0 5x8, 1 5x10
	uint8 unusedBits	: 1;
} lcdConfiguration_t;

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

extern lcdConfiguration_t lcdConfiguration;
extern FILE lcdStream;

// -----------------------------------------------------------------------------
// Constant definitions --------------------------------------------------------

#ifdef LCD_8X1
	#define LCD_LINES	1
	#define LCD_COLUMNS	8
#endif
#ifdef LCD_8X2
	#define LCD_LINES	2
	#define LCD_COLUMNS	8
#endif
#ifdef LCD_12X2
	#define LCD_LINES	2
	#define LCD_COLUMNS	12
#endif
#ifdef LCD_16X1
	#define LCD_LINES	1
	#define LCD_COLUMNS	16
#endif
#ifdef LCD_16X2
	#define LCD_LINES	2
	#define LCD_COLUMNS	16
#endif
#ifdef LCD_16X4
	#define LCD_LINES	4
	#define LCD_COLUMNS	16
#endif
#ifdef LCD_20X1
	#define LCD_LINES	1
	#define LCD_COLUMNS	20
#endif
#ifdef LCD_20X2
	#define LCD_LINES	2
	#define LCD_COLUMNS	20
#endif
#ifdef LCD_20X4
	#define LCD_LINES	4
	#define LCD_COLUMNS	20
#endif
#ifdef LCD_24X2
	#define LCD_LINES	2
	#define LCD_COLUMNS	24
#endif
#ifdef LCD_40X2
	#define LCD_LINES	2
	#define LCD_COLUMNS	40
#endif
#ifdef LCD_40X4
	#define LCD_LINES	4
	#define LCD_COLUMNS	40
#endif

// -----------------------------------------------------------------------------
// Macrofunction definitions ---------------------------------------------------

#define lcdStdio()					stdin = stdout = stderr = &lcdStream
#define lcdClearScreen()			do{lcdConfiguration.line = 0;lcdConfiguration.column = 0;lcdCommand(0x01);}while(0)
#define lcdCursorHome()				do{lcdConfiguration.column = 0;lcdCommand(0x02);}while(0)
#define lcdLeftRight()				do{lcdConfiguration.moveDirection = 0;lcdCommand(0x04 | (lcdConfiguration.insert));}while(0)
#define lcdRightLeft()				do{lcdConfiguration.moveDirection = 1;lcdCommand(0x06 | (lcdConfiguration.insert));}while(0)
#define lcdCursorOverwrite()		do{lcdConfiguration.insert = 0;lcdCommand(0x04 | (lcdConfiguration.moveDirection << 1));}while(0)
#define lcdCursorInsert()			do{lcdConfiguration.insert = 1;lcdCommand(0x05 | (lcdConfiguration.moveDirection << 1));}while(0)
#define lcdDisplayOn()				do{lcdConfiguration.displayOn = 1;lcdCommand(0x0C | (lcdConfiguration.cursorOn << 1) | lcdConfiguration.cursorBlink);}while(0)
#define lcdDisplayOff()				do{lcdConfiguration.displayOn = 0;lcdCommand(0x08 | (lcdConfiguration.cursorOn << 1) | lcdConfiguration.cursorBlink);}while(0)
#define lcdCursonOn()				do{lcdConfiguration.cursorOn = 1;lcdCommand(0x0A | (lcdConfiguration.displayOn << 2) | lcdConfiguration.cursorBlink);}while(0)
#define lcdCursorOff()				do{lcdConfiguration.cursorOn = 0;lcdCommand(0x08 | (lcdConfiguration.displayOn << 2) | lcdConfiguration.cursorBlink);}while(0)
#define lcdCursorBlinkOn()			do{lcdConfiguration.cursorBlink = 1;lcdCommand(0x09 | (lcdConfiguration.displayOn << 2) | (lcdConfiguration.cursorOn << 1));}while(0)
#define lcdCursorBlinkOff()			do{lcdConfiguration.cursorBlink = 0;lcdCommand(0x08 | (lcdConfiguration.displayOn << 2) | (lcdConfiguration.cursorOn << 1));}while(0)
#define lcdDisplayShiftLeft()		lcdCommand(0x18)
#define lcdDisplayShiftRight()		lcdCommand(0x1C)
#define lcdCursorMoveLeft()			lcdCommand(0x10)
#define lcdCursorMoveRight()		lcdCommand(0x14)
#define lcdDDRAMSet(address)		lcdCommand(0x80 | address)
#define lcdCursorMoveFirstLine()	do{lcdConfiguration.line = 0;lcdConfiguration.column = 1;lcdCommand(0x80);}while(0)
#if LCD_LINES == 1
	#define lcdCursorMoveNextLine()	do{lcdCommand(0x80);lcdConfiguration.column = 0;while(0)
#elif LCD_LINES == 2
	#define lcdCursorMoveNextLine()	do{if(lcdConfiguration.line == 0){lcdConfiguration.line = 1;lcdCommand(0xC0);}else{lcdConfiguration.line = 0;lcdCommand(0x80);}lcdConfiguration.column = 0;}while(0)
#else
	#define lcdCursorMoveNextLine()	do{switch(lcdConfiguration.line){case 0:lcdConfiguration.line = 1;lcdCommand(0xC0);break;case 1:lcdConfiguration.line = 2;lcdCommand(0x94);break;case 2:lcdConfiguration.line = 3;lcdCommand(0xD4);break;case 3:lcdConfiguration.line = 0;lcdCommand(0x80);break;}lcdConfiguration.column = 0;}while(0)
#endif
#ifdef LCD_4BITS_MODE
	#if LCD_LINES == 1
		#ifdef LCD_5x8_FONT
			#define lcdConfigureModule()	lcdCommand(0x20)
		#else
			#define lcdConfigureModule()	lcdCommand(0x24)
		#endif
	#else
		#ifdef LCD_5x8_FONT
			#define lcdConfigureModule()	lcdCommand(0x28)
		#else
			#define lcdConfigureModule()	lcdCommand(0x2C)
		#endif
	#endif
#else
	#if LCD_LINES == 1
		#ifdef LCD_5x8_FONT
			#define lcdConfigureModule()	lcdCommand(0x30)
		#else
			#define lcdConfigureModule()	lcdCommand(0x34)
		#endif
	#else
		#ifdef LCD_5x8_FONT
			#define lcdConfigureModule()	lcdCommand(0x38)
		#else
			#define lcdConfigureModule()	lcdCommand(0x3C)
		#endif
	#endif
#endif


#ifdef LCD_4_BITS_MODE
	#define lcdIOConfigure()	do{LCD_DATA_PORT &= ~(0x0F << LCD_DATA_D4);LCD_DATA_DDR |= (0x0F << LCD_DATA_D4);LCD_CONTROL_PORT &= ~((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));LCD_CONTROL_DDR |= ((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));}while(0)
#endif
#ifdef LCD_8_BITS_MODE
	#define lcdIOConfigure()	do{LCD_DATA_PORT = 0x00;LCD_DATA_DDR = 0xFF;LCD_CONTROL_PORT &= ~((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));LCD_CONTROL_DDR |= ((1 << LCD_CONTROL_RS) | (1 << LCD_CONTROL_RW) | (1 << LCD_CONTROL_E));}while(0)
#endif

// -----------------------------------------------------------------------------
// Function declarations -------------------------------------------------------

void	lcdInit(void);
int16	lcdWriteStd(int8 c, FILE * stream);
void	lcdWrite(int8 character);
void	lcdCommand(int8 command);


#endif