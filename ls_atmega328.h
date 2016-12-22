/* -----------------------------------------------------------------------------
 * File:			LS_ATmega328.h
 * Module:			ATmega328 basic interface
 * Author:			Leandro Schwarz
 * Version:			7.3
 * Last edition:	15/09/2014
 * -------------------------------------------------------------------------- */

#ifndef __LS_ATMEGA328_H
#define __LS_ATMEGA328_H 73

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include <avr/io.h>
#include <stdio.h>
#include "LS_defines.h"
#if __LS_DEFINES_H < 110
	#error Error 100 - The defintion file is outdated (LS_defines must be version 11.0 or greater).
#endif

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

extern adcConfiguration_t	adcConfiguration;
extern spiConfiguration_t	spiConfiguration;
extern usartConfiguration_t	usartConfiguration;
extern FILE usartStream;
extern uint8 usartReceiverBuffer[USART_RECEIVER_BUFFER_SIZE];
extern uint8 usartReceiverBufferNextRead;
extern uint8 usartReceiverBufferNextWrite;
extern uint8 usartReceiverBufferLength;

// -----------------------------------------------------------------------------
// Status Register -------------------------------------------------------------

#define globalInterruptEnable()			setBit(SREG, I)
#define globalInterruptDisable()		clrBit(SREG, I)

// -----------------------------------------------------------------------------
// System clock prescaler ------------------------------------------------------

#define systemClockEnableChange()	setBit(CLKPR, CLKPCE)
#define systemClockPrescalerOff()	do{clrBit(CLKPR, CLKPS3);clrBit(CLKPR, CLKPS2);clrBit(CLKPR, CLKPS1);clrBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler2()		do{clrBit(CLKPR, CLKPS3);clrBit(CLKPR, CLKPS2);clrBit(CLKPR, CLKPS1);setBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler4()		do{clrBit(CLKPR, CLKPS3);clrBit(CLKPR, CLKPS2);setBit(CLKPR, CLKPS1);clrBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler8()		do{clrBit(CLKPR, CLKPS3);clrBit(CLKPR, CLKPS2);setBit(CLKPR, CLKPS1);setBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler16()	do{clrBit(CLKPR, CLKPS3);setBit(CLKPR, CLKPS2);clrBit(CLKPR, CLKPS1);clrBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler32()	do{clrBit(CLKPR, CLKPS3);setBit(CLKPR, CLKPS2);clrBit(CLKPR, CLKPS1);setBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler64()	do{clrBit(CLKPR, CLKPS3);setBit(CLKPR, CLKPS2);setBit(CLKPR, CLKPS1);clrBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler128()	do{clrBit(CLKPR, CLKPS3);setBit(CLKPR, CLKPS2);setBit(CLKPR, CLKPS1);setBit(CLKPR, CLKPS0);}while(0)
#define systemClockPrescaler256()	do{setBit(CLKPR, CLKPS3);clrBit(CLKPR, CLKPS2);clrBit(CLKPR, CLKPS1);clrBit(CLKPR, CLKPS0);}while(0)

// -----------------------------------------------------------------------------
// EEPROM memory ---------------------------------------------------------------

// Operation mode
#define eepromEraseWriteOperationMode()		do{clrBit(EECR, EEPM1);clrBit(EECR, EEPM0);}while(0)
#define eepromEraseOnlyOperationMode()		do{clrBit(EECR, EEPM1);setBit(EECR, EEPM0);}while(0)
#define eepromWriteOnlyOperationMode()		do{setBit(EECR, EEPM1);clrBit(EECR, EEPM0);}while(0)
// Interrupt requests
#define eepromActivateInterrupt()			setBit(EECR, EERIE)
#define eepromDeactivateInterrupt()			clrBit(EECR, EERIE)
// Operation cycles
#define eepromActivateProgrammingCycle()	setBit(EECR, EEMPE)
#define eepromStartProgrammingCycle()		setBit(EECR, EEPE)
#define eepromStartReadingCycle()			setBit(EECR, EERE)

uint8	eepromRead(uint16 address);
void	eepromWrite(uint8 data, uint16 address);

// -----------------------------------------------------------------------------
// General purpose registers ---------------------------------------------------

#define generalPurposeRegister0Read(data)	data = GPIOR0
#define generalPurposeRegister0Write(data)	GPIOR0 = data
#define generalPurposeRegister1Read(data)	data = GPIOR1
#define generalPurposeRegister1Write(data)	GPIOR1 = data
#define generalPurposeRegister2Read(data)	data = GPIOR2
#define generalPurposeRegister2Write(data)	GPIOR2 = data

// -----------------------------------------------------------------------------
// X register ------------------------------------------------------------------
// Y register ------------------------------------------------------------------
// Z register ------------------------------------------------------------------
// Stack pointer ---------------------------------------------------------------
// OSCCAL register -------------------------------------------------------------
// CLKPR register --------------------------------------------------------------
// SMCR register ---------------------------------------------------------------
// MCUCR register --------------------------------------------------------------
// PRR register ----------------------------------------------------------------
// MCUSC register --------------------------------------------------------------
// WDTCSR register -------------------------------------------------------------
// GTCCR register --------------------------------------------------------------



// RAMPZ register --------------------------------------------------------------
// XMCRA register --------------------------------------------------------------
// XMCRB register --------------------------------------------------------------
// PLLCSR register -------------------------------------------------------------
// SMCR register ---------------------------------------------------------------
// PRR0 register ---------------------------------------------------------------
// PRR1 register ---------------------------------------------------------------
// ADCSRB ACME
// OCDR
// SPMCSR

// -----------------------------------------------------------------------------
// I/O ports -------------------------------------------------------------------

#define pullUpDisable()		setBit(MCUCR, PUD)
#define pullUpEnable()		clrBit(MCUCR, PUD)

// -----------------------------------------------------------------------------
// External interrupts ---------------------------------------------------------

// INT0
#define int0ActivateInterrupt()			setBit(EIMSK, INT0)
#define int0ClearInterruptRequest()		setBit(EIFR, INTF0)
#define int0DDRConfigure()				clrBit(DDRD, PD2)
#define int0DeactivateInterrupt()		clrBit(EIMSK, INT0)
#define int0PullUpDisable()				clrBit(PORTD, PD2)
#define int0PullUpEnable()				setBit(PORTD, PD2)
#define int0SenseLowLevel()				do{clrBit(EICRA, ISC01);clrBit(EICRA, ISC00);}while(0)
#define int0SenseAnyEdge()				do{clrBit(EICRA, ISC01);setBit(EICRA, ISC00);}while(0)
#define int0SenseFallingEdge()			do{setBit(EICRA, ISC01);clrBit(EICRA, ISC00);}while(0)
#define int0SenseRisingEdge()			do{setBit(EICRA, ISC01);setBit(EICRA, ISC00);}while(0)

// INT1
#define int1ActivateInterrupt()			setBit(EIMSK, INT1)
#define int1ClearInterruptRequest()		setBit(EIFR, INTF1)
#define int1DDRConfigure()				clrBit(DDRD, PD3)
#define int1DeactivateInterrupt()		clrBit(EIMSK, INT1)
#define int1PullUpDisable()				clrBit(PORTD, PD3)
#define int1PullUpEnable()				setBit(PORTD, PD3)
#define int1SenseLowLevel()				do{clrBit(EICRA, ISC11);clrBit(EICRA, ISC10);}while(0)
#define int1SenseAnyEdge()				do{clrBit(EICRA, ISC11);setBit(EICRA, ISC10);}while(0)
#define int1SenseFallingEdge()			do{setBit(EICRA, ISC11);clrBit(EICRA, ISC10);}while(0)
#define int1SenseRisingEdge()			do{setBit(EICRA, ISC11);setBit(EICRA, ISC10);}while(0)

// PCINT7-0
#define pcint7_0Disable()					clrBit(PCICR, PCIE0)
#define pcint7_0Enable()					setBit(PCICR, PCIE0)
#define pcint7_0ClearInterruptRequest()		setBit(PCIFR, PCIF0)
// PCINT0
#define pcint0ActivateInterrupt()			setBit(PCMSK0, PCINT0)
#define pcint0DeactivateInterrupt()			clrBit(PCMSK0, PCINT0)
#define pcint0DDRConfigure()				clrBit(DDRB, PB0)
#define pcint0PullUpDisable()				clrBit(PORTB, PB0)
#define pcint0PullUpEnable()				setBit(PORTB, PB0)
// PCINT1
#define pcint1ActivateInterrupt()			setBit(PCMSK0, PCINT1)
#define pcint1DeactivateInterrupt()			clrBit(PCMSK0, PCINT1)
#define pcint1DDRConfigure()				clrBit(DDRB, PB1)
#define pcint1PullUpDisable()				clrBit(PORTB, PB1)
#define pcint1PullUpEnable()				setBit(PORTB, PB1)
// PCINT2
#define pcint2ActivateInterrupt()			setBit(PCMSK0, PCINT2)
#define pcint2DeactivateInterrupt()			clrBit(PCMSK0, PCINT2)
#define pcint2DDRConfigure()				clrBit(DDRB, PB2)
#define pcint2PullUpDisable()				clrBit(PORTB, PB2)
#define pcint2PullUpEnable()				setBit(PORTB, PB2)
// PCINT3
#define pcint3ActivateInterrupt()			setBit(PCMSK0, PCINT3)
#define pcint3DeactivateInterrupt()			clrBit(PCMSK0, PCINT3)
#define pcint3DDRConfigure()				clrBit(DDRB, PB3)
#define pcint3PullUpDisable()				clrBit(PORTB, PB3)
#define pcint3PullUpEnable()				setBit(PORTB, PB3)
// PCINT4
#define pcint4ActivateInterrupt()			setBit(PCMSK0, PCINT4)
#define pcint4DeactivateInterrupt()			clrBit(PCMSK0, PCINT4)
#define pcint4DDRConfigure()				clrBit(DDRB, PB4)
#define pcint4PullUpDisable()				clrBit(PORTB, PB4)
#define pcint4PullUpEnable()				setBit(PORTB, PB4)
// PCINT5
#define pcint5ActivateInterrupt()			setBit(PCMSK0, PCINT5)
#define pcint5DeactivateInterrupt()			clrBit(PCMSK0, PCINT5)
#define pcint5DDRConfigure()				clrBit(DDRB, PB5)
#define pcint5PullUpDisable()				clrBit(PORTB, PB5)
#define pcint5PullUpEnable()				setBit(PORTB, PB5)
// PCINT6
#define pcint6ActivateInterrupt()			setBit(PCMSK0, PCINT6)
#define pcint6DeactivateInterrupt()			clrBit(PCMSK0, PCINT6)
#define pcint6DDRConfigure()				clrBit(DDRB, PB6)
#define pcint6PullUpDisable()				clrBit(PORTB, PB6)
#define pcint6PullUpEnable()				setBit(PORTB, PB6)
// PCINT7
#define pcint7ActivateInterrupt()			setBit(PCMSK0, PCINT7)
#define pcint7DeactivateInterrupt()			clrBit(PCMSK0, PCINT7)
#define pcint7DDRConfigure()				clrBit(DDRB, PB7)
#define pcint7PullUpDisable()				clrBit(PORTB, PB7)
#define pcint7PullUpEnable()				setBit(PORTB, PB7)

// PCINT15-8
#define pcint14_8Disable()					clrBit(PCICR, PCIE1)
#define pcint14_8Enable()					setBit(PCICR, PCIE1)
#define pcint14_8ClearInterruptRequest()	setBit(PCIFR, PCIF1)
// PCINT8
#define pcint8ActivateInterrupt()			setBit(PCMSK1, PCINT8)
#define pcint8DeactivateInterrupt()			clrBit(PCMSK1, PCINT8)
#define pcint8DDRConfigure()				clrBit(DDRC, PC0)
#define pcint8PullUpDisable()				clrBit(PORTC, PC0)
#define pcint8PullUpEnable()				setBit(PORTC, PC0)
// PCINT9
#define pcint9ActivateInterrupt()			setBit(PCMSK1, PCINT9)
#define pcint9DeactivateInterrupt()			clrBit(PCMSK1, PCINT9)
#define pcint9DDRConfigure()				clrBit(DDRC, PC1)
#define pcint9PullUpDisable()				clrBit(PORTC, PC1)
#define pcint9PullUpEnable()				setBit(PORTC, PC1)
// PCINT10
#define pcint10ActivateInterrupt()			setBit(PCMSK1, PCINT10)
#define pcint10DeactivateInterrupt()		clrBit(PCMSK1, PCINT10)
#define pcint10DDRConfigure()				clrBit(DDRC, PC2)
#define pcint10PullUpDisable()				clrBit(PORTC, PC2)
#define pcint10PullUpEnable()				setBit(PORTC, PC2)
// PCINT11
#define pcint11ActivateInterrupt()			setBit(PCMSK1, PCINT11)
#define pcint11DeactivateInterrupt()		clrBit(PCMSK1, PCINT11)
#define pcint11DDRConfigure()				clrBit(DDRC, PC3)
#define pcint11PullUpDisable()				clrBit(PORTC, PC3)
#define pcint11PullUpEnable()				setBit(PORTC, PC3)
// PCINT12
#define pcint12ActivateInterrupt()			setBit(PCMSK1, PCINT12)
#define pcint12DeactivateInterrupt()		clrBit(PCMSK1, PCINT12)
#define pcint12DDRConfigure()				clrBit(DDRC, PC4)
#define pcint12PullUpDisable()				clrBit(PORTC, PC4)
#define pcint12PullUpEnable()				setBit(PORTC, PC4)
// PCINT13
#define pcint13ActivateInterrupt()			setBit(PCMSK1, PCINT13)
#define pcint13DeactivateInterrupt()		clrBit(PCMSK1, PCINT13)
#define pcint13DDRConfigure()				clrBit(DDRC, PC5)
#define pcint13PullUpDisable()				clrBit(PORTC, PC5)
#define pcint13PullUpEnable()				setBit(PORTC, PC5)
// PCINT14
#define pcint14ActivateInterrupt()			setBit(PCMSK1, PCINT14)
#define pcint14DeactivateInterrupt()		clrBit(PCMSK1, PCINT14)
#define pcint14DDRConfigure()				clrBit(DDRC, PC6)
#define pcint14PullUpDisable()				clrBit(PORTC, PC6)
#define pcint14PullUpEnable()				setBit(PORTC, PC6)
// PCINT23-16
#define pcint23_16Disable()					clrBit(PCICR, PCIE2)
#define pcint23_16Enable()					setBit(PCICR, PCIE2)
#define pcint23_16ClearInterruptRequest()	setBit(PCIFR, PCIF2)
// PCINT16
#define pcint16ActivateInterrupt()			setBit(PCMSK2, PCINT16)
#define pcint16DeactivateInterrupt()		clrBit(PCMSK2, PCINT16)
#define pcint16DDRConfigure()				clrBit(DDRD, PD0)
#define pcint16PullUpDisable()				clrBit(PORTD, PD0)
#define pcint16PullUpEnable()				setBit(PORTD, PD0)
// PCINT17
#define pcint17ActivateInterrupt()			setBit(PCMSK2, PCINT17)
#define pcint17DeactivateInterrupt()		clrBit(PCMSK2, PCINT17)
#define pcint17DDRConfigure()				clrBit(DDRD, PD1)
#define pcint17PullUpDisable()				clrBit(PORTD, PD1)
#define pcint17PullUpEnable()				setBit(PORTD, PD1)
// PCINT18
#define pcint18ActivateInterrupt()			setBit(PCMSK2, PCINT18)
#define pcint18DeactivateInterrupt()		clrBit(PCMSK2, PCINT18)
#define pcint18DDRConfigure()				clrBit(DDRD, PD2)
#define pcint18PullUpDisable()				clrBit(PORTD, PD2)
#define pcint18PullUpEnable()				setBit(PORTD, PD2)
// PCINT19
#define pcint19ActivateInterrupt()			setBit(PCMSK2, PCINT19)
#define pcint19DeactivateInterrupt()		clrBit(PCMSK2, PCINT19)
#define pcint19DDRConfigure()				clrBit(DDRD, PD3)
#define pcint19PullUpDisable()				clrBit(PORTD, PD3)
#define pcint19PullUpEnable()				setBit(PORTD, PD3)
// PCINT20
#define pcint20ActivateInterrupt()			setBit(PCMSK2, PCINT20)
#define pcint20DeactivateInterrupt()		clrBit(PCMSK2, PCINT20)
#define pcint20DDRConfigure()				clrBit(DDRD, PD4)
#define pcint20PullUpDisable()				clrBit(PORTD, PD4)
#define pcint20PullUpEnable()				setBit(PORTD, PD4)
// PCINT21
#define pcint21ActivateInterrupt()			setBit(PCMSK2, PCINT21)
#define pcint21DeactivateInterrupt()		clrBit(PCMSK2, PCINT21)
#define pcint21DDRConfigure()				clrBit(DDRD, PD5)
#define pcint21PullUpDisable()				clrBit(PORTD, PD5)
#define pcint21PullUpEnable()				setBit(PORTD, PD5)
// PCINT22
#define pcint22ActivateInterrupt()			setBit(PCMSK2, PCINT22)
#define pcint22DeactivateInterrupt()		clrBit(PCMSK2, PCINT22)
#define pcint22DDRConfigure()				clrBit(DDRD, PD6)
#define pcint22PullUpDisable()				clrBit(PORTD, PD6)
#define pcint22PullUpEnable()				setBit(PORTD, PD6)
// PCINT23
#define pcint23ActivateInterrupt()			setBit(PCMSK2, PCINT23)
#define pcint23DeactivateInterrupt()		clrBit(PCMSK2, PCINT23)
#define pcint23DDRConfigure()				clrBit(DDRD, PD7)
#define pcint23PullUpDisable()				clrBit(PORTD, PD7)
#define pcint23PullUpEnable()				setBit(PORTD, PD7)

// -----------------------------------------------------------------------------
// Timer/counter 0 -------------------------------------------------------------

// Clock prescaler
#define timer0ClockDisable()						do{clrBit(TCCR0B, CS02);clrBit(TCCR0B, CS01);clrBit(TCCR0B, CS00);}while(0)
#define timer0ClockPrescallerOff()					do{clrBit(TCCR0B, CS02);clrBit(TCCR0B, CS01);setBit(TCCR0B, CS00);}while(0)
#define timer0ClockPrescaller8()					do{clrBit(TCCR0B, CS02);setBit(TCCR0B, CS01);clrBit(TCCR0B, CS00);}while(0)
#define timer0ClockPrescaller64()					do{clrBit(TCCR0B, CS02);setBit(TCCR0B, CS01);setBit(TCCR0B, CS00);}while(0)
#define timer0ClockPrescaller256()					do{setBit(TCCR0B, CS02);clrBit(TCCR0B, CS01);clrBit(TCCR0B, CS00);}while(0)
#define timer0ClockPrescaller1024()					do{setBit(TCCR0B, CS02);clrBit(TCCR0B, CS01);setBit(TCCR0B, CS00);}while(0)
#define timer0ClockT0FallingEdge()					do{setBit(TCCR0B, CS02);setBit(TCCR0B, CS01);clrBit(TCCR0B, CS00);}while(0)
#define timer0ClockT0RisingEdge()					do{setBit(TCCR0B, CS02);setBit(TCCR0B, CS01);setBit(TCCR0B, CS00);}while(0)
// Operation mode selection
#define timer0NormalMode()							do{clrBit(TCCR0B, WGM02);clrBit(TCCR0A, WGM01);clrBit(TCCR0A, WGM00);}while(0)
#define timer0CTCMode()								do{clrBit(TCCR0B, WGM02);setBit(TCCR0A, WGM01);clrBit(TCCR0A, WGM00);}while(0)
#define timer0FastPWMMaxMode()						do{clrBit(TCCR0B, WGM02);setBit(TCCR0A, WGM01);setBit(TCCR0A, WGM00);}while(0)
#define timer0FastPWMOCR0AMode()					do{setBit(TCCR0B, WGM02);setBit(TCCR0A, WGM01);setBit(TCCR0A, WGM00);}while(0)
#define timer0PhaseCorrectPWMMaxMode()				do{clrBit(TCCR0B, WGM02);clrBit(TCCR0A, WGM01);setBit(TCCR0A, WGM00);}while(0)
#define timer0PhaseCorrectPWMOCR0AMode()			do{setBit(TCCR0B, WGM02);clrBit(TCCR0A, WGM01);setBit(TCCR0A, WGM00);}while(0)
// Output compare A behavior
#define timer0OC0AOff()								do{clrBit(TCCR0A, COM0A1);clrBit(TCCR0A, COM0A0);}while(0)
#define timer0OC0AToggleOnCompare()					do{clrBit(TCCR0A, COM0A1);setBit(TCCR0A, COM0A0);}while(0)
#define timer0OC0AClearOnCompare()					do{setBit(TCCR0A, COM0A1);clrBit(TCCR0A, COM0A0);}while(0)
#define timer0OC0ASetOnCompare()					do{setBit(TCCR0A, COM0A1);setBit(TCCR0A, COM0A0);}while(0)
#define timer0OC0ANonInvertedMode()					do{setBit(TCCR0A, COM0A1);clrBit(TCCR0A, COM0A0);}while(0)
#define timer0OC0AInvertedMode()					do{setBit(TCCR0A, COM0A1);setBit(TCCR0A, COM0A0);}while(0)
// Output compare B behavior
#define timer0OC0BOff()								do{clrBit(TCCR0A, COM0B1);clrBit(TCCR0A, COM0B0);}while(0)
#define timer0OC0BToggleOnCompare()					do{clrBit(TCCR0A, COM0B1);setBit(TCCR0A, COM0B0);}while(0)
#define timer0OC0BClearOnCompare()					do{setBit(TCCR0A, COM0B1);clrBit(TCCR0A, COM0B0);}while(0)
#define timer0OC0BSetOnCompare()					do{setBit(TCCR0A, COM0B1);setBit(TCCR0A, COM0B0);}while(0)
#define timer0OC0BNonInvertedMode()					do{setBit(TCCR0A, COM0B1);clrBit(TCCR0A, COM0B0);}while(0)
#define timer0OC0BInvertedMode()					do{setBit(TCCR0A, COM0B1);setBit(TCCR0A, COM0B0);}while(0)
// Timer overflow interruption configuration
#define timer0ActivateOverflowInterrupt()			setBit(TIMSK0, TOIE0)
#define timer0DeactivateOverflowInterrupt()			clrBit(TIMSK0, TOIE0)
#define timer0ClearOverflowInterruptRequest()		setBit(TIFR0, TOV0)
// Output compare A interruption configuration
#define timer0ActivateCompareAInterrupt()			setBit(TIMSK0, OCIE0A)
#define timer0DeactivateCompareAInterrupt()			clrBit(TIMSK0, OCIE0A)
#define timer0ClearCompareAInterruptRequest()		setBit(TIFR0, OCF0A)
// Output compare B interruption configuration
#define timer0ActivateCompareBInterrupt()			setBit(TIMSK0, OCIE0B)
#define timer0DeactivateCompareBInterrupt()			clrBit(TIMSK0, OCIE0B)
#define timer0ClearCompareBInterruptRequest()		setBit(TIFR0, OCF0B)
// Force output compare
#define timer0ForceCompareA()						setBit(TCCR0B, FOC0A)
#define timer0ForceCompareB()						setBit(TCCR0B, FOC0B)
// Timer value
#define timer0SetCounterValue(value)				TCNT0 = value
#define timer0GetCounterValue()						TCNT0
#define timer0SetCompareAValue(value)				OCR0A = value
#define timer0GetCompareAValue()					OCR0A
#define timer0SetCompareBValue(value)				OCR0B = value
#define timer0GetCompareBValue()					OCR0B

// -----------------------------------------------------------------------------
// Timer/counter 1 -------------------------------------------------------------

// Clock prescaler selection
#define timer1ClockDisable()						do{clrBit(TCCR1B, CS12);clrBit(TCCR1B, CS11);clrBit(TCCR1B, CS10);}while(0)
#define timer1ClockPrescallerOff()					do{clrBit(TCCR1B, CS12);clrBit(TCCR1B, CS11);setBit(TCCR1B, CS10);}while(0)
#define timer1ClockPrescaller8()					do{clrBit(TCCR1B, CS12);setBit(TCCR1B, CS11);clrBit(TCCR1B, CS10);}while(0)
#define timer1ClockPrescaller64()					do{clrBit(TCCR1B, CS12);setBit(TCCR1B, CS11);setBit(TCCR1B, CS10);}while(0)
#define timer1ClockPrescaller256()					do{setBit(TCCR1B, CS12);clrBit(TCCR1B, CS11);clrBit(TCCR1B, CS10);}while(0)
#define timer1ClockPrescaller1024()					do{setBit(TCCR1B, CS12);clrBit(TCCR1B, CS11);setBit(TCCR1B, CS10);}while(0)
#define timer1ClockT1FallingEdge()					do{setBit(TCCR1B, CS12);setBit(TCCR1B, CS11);clrBit(TCCR1B, CS10);}while(0)
#define timer1ClockT1RisingEdge()					do{setBit(TCCR1B, CS12);setBit(TCCR1B, CS11);setBit(TCCR1B, CS10);}while(0)
// Operation mode selection
#define timer1NormalMode()							do{clrBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseCorrectPWM8bitsMode()			do{clrBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseCorrectPWM9bitsMode()			do{clrBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseCorrectPWM10bitsMode()			do{clrBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
#define timer1CTCMode()								do{clrBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1FastPWM8bitsMode()					do{clrBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
#define timer1FastPWM9bitsMode()					do{clrBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1FastPWM10bitsMode()					do{clrBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseFrequencyCorrectPWMICR1Mode()	do{setBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseFrequencyCorrectPWMOCR1AMode()	do{setBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseCorrectPWMICR1Mode()				do{setBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1PhaseCorrectPWMOCR1AMode()			do{setBit(TCCR1B, WGM13);clrBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
#define timer1CTCICR1Mode()							do{setBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);clrBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1FastPWMICR1Mode()						do{setBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);clrBit(TCCR1A, WGM10);}while(0)
#define timer1FastPWMOCR1AMode()					do{setBit(TCCR1B, WGM13);setBit(TCCR1B, WGM12);setBit(TCCR1A, WGM11);setBit(TCCR1A, WGM10);}while(0)
// Input capture configuration
#define timer1EnableInputCaptureNoiseCanceler()		setBit(TCCR1B, ICNC1)
#define timer1DisableInputCaptureNoiseCanceler()	clrBit(TCCR1B, ICNC1)
#define timer1InputCaptureOnFallingEdge()			clrBit(TCCR1B, ICES1)
#define timer1InputCaptureOnRisingEdge()			setBit(TCCR1B, ICES1)
// Output compare A behavior
#define timer1OC1AOff()								do{clrBit(TCCR1A, COM1A1);clrBit(TCCR1A, COM1A0);}while(0)
#define timer1OC1AToggleOnCompare()					do{clrBit(TCCR1A, COM1A1);setBit(TCCR1A, COM1A0);}while(0)
#define timer1OC1AClearOnCompare()					do{setBit(TCCR1A, COM1A1);clrBit(TCCR1A, COM1A0);}while(0)
#define timer1OC1ASetOnCompare()					do{setBit(TCCR1A, COM1A1);setBit(TCCR1A, COM1A0);}while(0)
#define timer1OC1ANonInvertedMode()					do{setBit(TCCR1A, COM1A1);clrBit(TCCR1A, COM1A0);}while(0)
#define timer1OC1AInvertedMode()					do{setBit(TCCR1A, COM1A1);setBit(TCCR1A, COM1A0);}while(0)
// Output compare B behavior
#define timer1OC1BOff()								do{clrBit(TCCR1A, COM1B1);clrBit(TCCR1A, COM1B0);}while(0)
#define timer1OC1BToggleOnCompare()					do{clrBit(TCCR1A, COM1B1);setBit(TCCR1A, COM1B0);}while(0)
#define timer1OC1BClearOnCompare()					do{setBit(TCCR1A, COM1B1);clrBit(TCCR1A, COM1B0);}while(0)
#define timer1OC1BSetOnCompare()					do{setBit(TCCR1A, COM1B1);setBit(TCCR1A, COM1B0);}while(0)
#define timer1OC1BNonInvertedMode()					do{setBit(TCCR1A, COM1B1);clrBit(TCCR1A, COM1B0);}while(0)
#define timer1OC1BInvertedMode()					do{setBit(TCCR1A, COM1B1);setBit(TCCR1A, COM1B0);}while(0)
// Timer overflow interruption configuration
#define timer1ActivateOverflowInterrupt()			setBit(TIMSK1, TOIE1)
#define timer1DeactivateOverflowInterrupt()			clrBit(TIMSK1, TOIE1)
#define timer1ClearOverflowInterruptRequest()		setBit(TIFR1, TOV1)
// Output compare A interruption configuration
#define timer1ActivateCompareAInterrupt()			setBit(TIMSK1, OCIE1A)
#define timer1DeactivateCompareAInterrupt()			clrBit(TIMSK1, OCIE1A)
#define timer1ClearCompareAInterruptRequest()		setBit(TIFR1, OCF1A)
// Output compare B interruption configuration
#define timer1ActivateCompareBInterrupt()			setBit(TIMSK1, OCIE1B)
#define timer1DeactivateCompareBInterrupt()			clrBit(TIMSK1, OCIE1B)
#define timer1ClearCompareBInterruptRequest()		setBit(TIFR1, OCF1B)
// Input capture interruption configuration
#define timer1ActivateInputCaptureInterrupt()		setBit(TIMSK1, ICIE1)
#define timer1DeactivateInputCaptureInterrupt()		clrBit(TIMSK1, ICIE1)
#define timer1ClearInputCaptureInterruptRequest()	setBit(TIFR1, ICF1)
// Force output compare
#define timer1ForceCompareA()						setBit(TCCR1C, FOC1A)
#define timer1ForceCompareB()						setBit(TCCR1C, FOC1B)
// Timer value
void	timer1SetCounterValue(uint16 value);
uint16	timer1GetCounterValue(void);
void	timer1SetCompareAValue(uint16 value);
uint16	timer1GetCompareAValue(void);
void	timer1SetCompareBValue(uint16 value);
uint16	timer1GetCompareBValue(void);
void	timer1SetInputCaptureValue(uint16 value);
uint16	timer1GetInputCaptureValue(void);

// -----------------------------------------------------------------------------
// Timer/counter 2 -------------------------------------------------------------

// Clock prescaler selection
#define timer2ClockDisable()						do{clrBit(TCCR2B, CS22);clrBit(TCCR2B, CS21);clrBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescallerOff()					do{clrBit(TCCR2B, CS22);clrBit(TCCR2B, CS21);setBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescaller8()					do{clrBit(TCCR2B, CS22);setBit(TCCR2B, CS21);clrBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescaller32()					do{clrBit(TCCR2B, CS22);setBit(TCCR2B, CS21);setBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescaller64()					do{setBit(TCCR2B, CS22);clrBit(TCCR2B, CS21);clrBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescaller128()					do{setBit(TCCR2B, CS22);clrBit(TCCR2B, CS21);setBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescaller256()					do{setBit(TCCR2B, CS22);setBit(TCCR2B, CS21);clrBit(TCCR2B, CS20);}while(0)
#define timer2ClockPrescaller1024()					do{setBit(TCCR2B, CS22);setBit(TCCR2B, CS21);setBit(TCCR2B, CS20);}while(0)
// Operation mode selection
#define timer2NormalMode()							do{clrBit(TCCR2B, WGM22);clrBit(TCCR2A, WGM21);clrBit(TCCR2A, WGM20);}while(0)
#define timer2CTCMode()								do{clrBit(TCCR2B, WGM22);setBit(TCCR2A, WGM21);clrBit(TCCR2A, WGM20);}while(0)
#define timer2FastPWMMaxMode()						do{clrBit(TCCR2B, WGM22);setBit(TCCR2A, WGM21);setBit(TCCR2A, WGM20);}while(0)
#define timer2FastPWMOCR2AMode()					do{setBit(TCCR2B, WGM22);setBit(TCCR2A, WGM21);setBit(TCCR2A, WGM20);}while(0)
#define timer2PhaseCorrectPWMMaxMode()				do{clrBit(TCCR2B, WGM22);clrBit(TCCR2A, WGM21);setBit(TCCR2A, WGM20);}while(0)
#define timer2PhaseCorrectPWMOCR2AMode()			do{setBit(TCCR2B, WGM22);clrBit(TCCR2A, WGM21);setBit(TCCR2A, WGM20);}while(0)
// Output compare A behavior
#define timer2OC2AOff()								do{clrBit(TCCR2A, COM2A1);clrBit(TCCR2A, COM0A0);}while(0)
#define timer2OC2AToggleOnCompare()					do{clrBit(TCCR2A, COM2A1);setBit(TCCR2A, COM0A0);}while(0)
#define timer2OC2AClearOnCompare()					do{setBit(TCCR2A, COM2A1);clrBit(TCCR2A, COM0A0);}while(0)
#define timer2OC2ASetOnCompare()					do{setBit(TCCR2A, COM2A1);setBit(TCCR2A, COM0A0);}while(0)
#define timer2OC2ANonInvertedMode()					do{setBit(TCCR2A, COM2A1);clrBit(TCCR2A, COM0A0);}while(0)
#define timer2OC2AInvertedMode()					do{setBit(TCCR2A, COM2A1);setBit(TCCR2A, COM0A0);}while(0)
// Output compare B behavior
#define timer2OC2BOff()								do{clrBit(TCCR2A, COM2B1);clrBit(TCCR2A, COM2B0);}while(0)
#define timer2OC2BToggleOnCompare()					do{clrBit(TCCR2A, COM2B1);setBit(TCCR2A, COM2B0);}while(0)
#define timer2OC2BClearOnCompare()					do{setBit(TCCR2A, COM2B1);clrBit(TCCR2A, COM2B0);}while(0)
#define timer2OC2BSetOnCompare()					do{setBit(TCCR2A, COM2B1);setBit(TCCR2A, COM2B0);}while(0)
#define timer2OC2BNonInvertedMode()					do{setBit(TCCR2A, COM2B1);clrBit(TCCR2A, COM2B0);}while(0)
#define timer2OC2BInvertedMode()					do{setBit(TCCR2A, COM2B1);setBit(TCCR2A, COM2B0);}while(0)
// Timer overflow interruption configuration
#define timer2ActivateOverflowInterrupt()			setBit(TIMSK2, TOIE2)
#define timer2DeactivateOverflowInterrupt()			clrBit(TIMSK2, TOIE2)
#define timer2ClearOverflowInterruptRequest()		setBit(TIFR2, TOV2)
// Output compare A interruption configuration
#define timer2ActivateCompareAInterrupt()			setBit(TIMSK2, OCIE2A)
#define timer2DeactivateCompareAInterrupt()			clrBit(TIMSK2, OCIE2A)
#define timer2ClearCompareAInterruptRequest()		setBit(TIFR2, OCF2A)
// Output compare B interruption configuration
#define timer2ActivateCompareBInterrupt()			setBit(TIMSK2, OCIE2B)
#define timer2DeactivateCompareBInterrupt()			clrBit(TIMSK2, OCIE2B)
#define timer2ClearCompareBInterruptRequest()		setBit(TIFR2, OCF2B)
// Force output compare
#define timer2ForceCompareA()						setBit(TCCR2B, FOC2A)
#define timer2ForceCompareB()						setBit(TCCR2B, FOC2B)
// Timer value
#define timer2SetCounterValue(value)				TCNT2 = value
#define timer2GetCounterValue()						TCNT2
#define timer2SetCompareAValue(value)				OCR2A = value
#define timer2GetCompareAValue()					OCR2A
#define timer2SetCompareBValue(value)				OCR2B = value
#define timer2GetCompareBValue()					OCR2B
// ASSR register
// GTCCR register

// -----------------------------------------------------------------------------
// Serial Peripheral Interface -------------------------------------------------

#define SPI_DDR						DDRB
#define SPI_MOSI					PB3
#define SPI_MISO					PB4
#define SPI_SCK						PB5

#define spiMaster()					spiConfiguration.masterSlave = 1
#define spiSlave()					spiConfiguration.masterSlave = 0
#define spiEnable()					spiConfiguration.enabled = 1
#define spiDisable()				spiConfiguration.enabled = 0
#define spiEnableInterrupt()		spiConfiguration.interruptEnabled = 1
#define spiDisableInterrupt()		spiConfiguration.interruptEnabled = 0
#define spiMSBFirst()				spiConfiguration.msbLsb = 0
#define spiLSBFirst()				spiConfiguration.msbLsb = 1
#define spiSCKIdleLow()				spiConfiguration.sckIdleValue = 0
#define spiSCKIdleHigh()			spiConfiguration.sckIdleValue = 1
#define spiSampleLeadingEdge()		spiConfiguration.leadingTrailingEdge = 0
#define spiSampleTrailingEdge()		spiConfiguration.leadingTrailingEdge = 1
#define spiEnableDoubleSpeed()		spiConfiguration.doubleSpeed = 1
#define spiDisableDoubleSpeed()		spiConfiguration.doubleSpeed = 0
#define spiClockPrescaler2()		spiConfiguration.clockPrescaler = 4
#define spiClockPrescaler4()		spiConfiguration.clockPrescaler = 0
#define spiClockPrescaler8()		spiConfiguration.clockPrescaler = 5
#define spiClockPrescaler16()		spiConfiguration.clockPrescaler = 1
#define spiClockPrescaler32()		spiConfiguration.clockPrescaler = 6
#define spiClockPrescaler64()		spiConfiguration.clockPrescaler = 2
#define spiClockPrescaler128()		spiConfiguration.clockPrescaler = 3

void	spiInit(void);
uint8	spiMasterTransmit(uint8 data);
uint8	spiSlaveTransmit(void);

// -----------------------------------------------------------------------------
// Analog/Digital Converter ----------------------------------------------------

// Channels
#define ADC0			0
#define ADC1			1
#define ADC2			2
#define ADC3			3
#define ADC4			4
#define ADC5			5
#define ADC6			6
#define ADC7			7
#define ADC_TEMPERATURE	8
#define ADC_INTERNAL	14
#define ADC_GND			15
// Reference voltage value
#define ADC_INTERNAL_REFERENCE_VALUE_V	1.1
#define ADC_INTERNAL_REFERENCE_VALUE_MV	1100

// Reference selection
#define adcReferenceAref()					do{clrBit(ADMUX, REFS1);clrBit(ADMUX, REFS0);adcConfiguration.reference = 0;}while(0)
#define adcReferenceAvcc()					do{clrBit(ADMUX, REFS1);setBit(ADMUX, REFS0);adcConfiguration.reference = 1;}while(0)
#define adcReferenceInternal()				do{setBit(ADMUX, REFS1);setBit(ADMUX, REFS0);adcConfiguration.reference = 3;}while(0)
// Clock prescaler
#define adcClockPrescaler2()				do{clrBit(ADCSRA, ADPS2);clrBit(ADCSRA, ADPS1);setBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 1;}while(0)
#define adcClockPrescaler4()				do{clrBit(ADCSRA, ADPS2);setBit(ADCSRA, ADPS1);clrBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 2;}while(0)
#define adcClockPrescaler8()				do{clrBit(ADCSRA, ADPS2);setBit(ADCSRA, ADPS1);setBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 3;}while(0)
#define adcClockPrescaler16()				do{setBit(ADCSRA, ADPS2);clrBit(ADCSRA, ADPS1);clrBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 4;}while(0)
#define adcClockPrescaler32()				do{setBit(ADCSRA, ADPS2);clrBit(ADCSRA, ADPS1);setBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 5;}while(0)
#define adcClockPrescaler64()				do{setBit(ADCSRA, ADPS2);setBit(ADCSRA, ADPS1);clrBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 6;}while(0)
#define adcClockPrescaler128()				do{setBit(ADCSRA, ADPS2);setBit(ADCSRA, ADPS1);setBit(ADCSRA, ADPS0);adcConfiguration.clockPrescaller = 7;}while(0)
// Automatic mode
#define adcEnableAutomaticMode()			do{setBit(ADCSRA, ADATE);adcConfiguration.automaticMode = 1;}while(0)
#define adcDisableAutomaticMode()			do{clrBit(ADCSRA, ADATE);adcConfiguration.automaticMode = 0;}while(0)
// Trigger source
#define adcTriggerContinuous()				do{clrBit(ADCSRB, ADTS2);clrBit(ADCSRB, ADTS1);clrBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 0;}while(0)
#define adcTriggerAnalogComparator()		do{clrBit(ADCSRB, ADTS2);clrBit(ADCSRB, ADTS1);setBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 1;}while(0)
#define adcTriggerInt0()					do{clrBit(ADCSRB, ADTS2);setBit(ADCSRB, ADTS1);clrBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 2;}while(0)
#define adcTriggerTimer0CompareMatchA()		do{clrBit(ADCSRB, ADTS2);setBit(ADCSRB, ADTS1);setBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 3;}while(0)
#define adcTriggerTimer0Overflow()			do{setBit(ADCSRB, ADTS2);clrBit(ADCSRB, ADTS1);clrBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 4;}while(0)
#define adcTriggerTimer1CompareMatchB()		do{setBit(ADCSRB, ADTS2);clrBit(ADCSRB, ADTS1);setBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 5;}while(0)
#define adcTriggerTimer1Overflow()			do{setBit(ADCSRB, ADTS2);setBit(ADCSRB, ADTS1);clrBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 6;}while(0)
#define adcTriggerTimer1CaptureEvent()		do{setBit(ADCSRB, ADTS2);setBit(ADCSRB, ADTS1);setBit(ADCSRB, ADTS0);adcConfiguration.triggerSource = 7;}while(0)
// Result presentation
#define adcResultLeftAdjust()				do{setBit(ADMUX, ADLAR);adcConfiguration.leftAdjust = 1;}while(0)
#define adcResultRightAdjust()				do{clrBit(ADMUX, ADLAR);adcConfiguration.leftAdjust = 0;}while(0)
// Channel selection
#define adcSelectChannel(adcChannel)		do{ADMUX = ((ADMUX & 0xF0) | (adcChannel & 0x0F));adcConfiguration.channel = (adcChannel & 0x0F);}while(0)
#define adcDisableDigitalInput0()			do{setBit(DIDR0, ADC0D);setBit(adcConfiguration.digitalDisabled, 0);}while(0)
#define adcEnableDigitalInput0()			do{clrBit(DIDR0, ADC0D);clrBit(adcConfiguration.digitalDisabled, 0);}while(0)
#define adcDisableDigitalInput1()			do{setBit(DIDR0, ADC1D);setBit(adcConfiguration.digitalDisabled, 1);}while(0)
#define adcEnableDigitalInput1()			do{clrBit(DIDR0, ADC1D);clrBit(adcConfiguration.digitalDisabled, 1);}while(0)
#define adcDisableDigitalInput2()			do{setBit(DIDR0, ADC2D);setBit(adcConfiguration.digitalDisabled, 2);}while(0)
#define adcEnableDigitalInput2()			do{clrBit(DIDR0, ADC2D);clrBit(adcConfiguration.digitalDisabled, 2);}while(0)
#define adcDisableDigitalInput3()			do{setBit(DIDR0, ADC3D);setBit(adcConfiguration.digitalDisabled, 3);}while(0)
#define adcEnableDigitalInput3()			do{clrBit(DIDR0, ADC3D);clrBit(adcConfiguration.digitalDisabled, 3);}while(0)
#define adcDisableDigitalInput4()			do{setBit(DIDR0, ADC4D);setBit(adcConfiguration.digitalDisabled, 4);}while(0)
#define adcEnableDigitalInput4()			do{clrBit(DIDR0, ADC4D);clrBit(adcConfiguration.digitalDisabled, 4);}while(0)
#define adcDisableDigitalInput5()			do{setBit(DIDR0, ADC5D);setBit(adcConfiguration.digitalDisabled, 5);}while(0)
#define adcEnableDigitalInput5()			do{clrBit(DIDR0, ADC5D);clrBit(adcConfiguration.digitalDisabled, 5);}while(0)
// Activation
#define adcEnable()							do{setBit(ADCSRA, ADEN);adcConfiguration.enabled = 1;}while(0)
#define adcDisable()						do{clrBit(ADCSRA, ADEN);adcConfiguration.enabled = 0;}while(0)
#define adcActivateInterrupt()				do{setBit(ADCSRA, ADIE);adcConfiguration.interruptEnabled = 1;}while(0)
#define adcDeactivateInterrupt()			do{clrBit(ADCSRA, ADIE);adcConfiguration.interruptEnabled = 0;}while(0)
#define adcStartConversion()				setBit(ADCSRA, ADSC)
#define adcClearInterruptRequest()			setBit(ADCSRA, ADIF)

#define adcWaitConversionFinish()			waitUntilBitIsClear(ADCSRA, ADSC)

adcConfiguration_t adcGetConfiguration(void);
void adcLoadConfiguration(adcConfiguration_t config);

// -----------------------------------------------------------------------------
// USART0 ----------------------------------------------------------------------

#define USART_RECEIVER_BUFFER_FUNCTION_HANDLER			ISR(USART_RX_vect){usartAddDataToReceiverBuffer(usartReceive());return;}

// Number of data bits
#define usart5DataBits()								usartConfiguration.dataBits = 0
#define usart6DataBits()								usartConfiguration.dataBits = 1
#define usart7DataBits()								usartConfiguration.dataBits = 2
#define usart8DataBits()								usartConfiguration.dataBits = 3
#define usart9DataBits()								usartConfiguration.dataBits = 4
// Number of stop bits
#define usartSingleStopBit()							usartConfiguration.stopBits = 0
#define usartDoubleStopBit()							usartConfiguration.stopBits = 1
// Parity bit
#define usartParityNone()								usartConfiguration.parity = 0
#define usartParityEven()								usartConfiguration.parity = 1
#define usartParityOdd()								usartConfiguration.parity = 2
// Receiver configuration
#define usartEnableReceiver()							do{setBit(UCSR0B,RXEN0);usartConfiguration.receiverEnabled = 1;}while(0)
#define usartDisableReceiver()							do{clrBit(UCSR0B,RXEN0);usartConfiguration.receiverEnabled = 0;}while(0)
// Transmitter configuration
#define usartEnableTransmitter()						do{setBit(UCSR0B,TXEN0);usartConfiguration.transmitterEnabled = 1;}while(0)
#define usartDisableTransmitter()						do{clrBit(UCSR0B,TXEN0);usartConfiguration.transmitterEnabled = 0;}while(0)
// Mode
#define usartAsynchronousMode()							usartConfiguration.mode = 0
#define usartAsynchronousModeDoubleSpeed()				usartConfiguration.mode = 1
#define usartSynchronousMode()							usartConfiguration.mode = 2
#define usartSynchronousModeSpi()						usartConfiguration.mode = 3
// Synchronous clock edge selection
#define usartXckRisingEdge()							usartConfiguration.polarity = 0
#define usartXckFallingEdge()							usartConfiguration.polarity = 1
// Interruption
#define usartActivateReceptionCompleteInterrupt()		do{setBit(UCSR0B, RXCIE0);usartConfiguration.receiverInterruptEnabled = 1;}while(0)
#define usartDeactivateReceptionCompleteInterrupt()		do{clrBit(UCSR0B, RXCIE0);usartConfiguration.receiverInterruptEnabled = 0;}while(0)
#define usartActivateTransmissionCompleteInterrupt()	do{setBit(UCSR0B, TXCIE0);usartConfiguration.transmitterInterruptEnabled = 1;}while(0)
#define usartDeactivateTransmissionCompleteInterrupt()	do{clrBit(UCSR0B, TXCIE0);usartConfiguration.transmitterInterruptEnabled = 0;}while(0)
#define usartActivateBufferEmptyInterrupt()				do{setBit(UCSR0B, UDRIE0);usartConfiguration.bufferEmptyInterruptEnabled = 1;}while(0)
#define usartDeactivateBufferEmptyInterrupt()			do{clrBit(UCSR0B, UDRIE0);usartConfiguration.bufferEmptyInterruptEnabled = 0;}while(0)
// Functions
#define usartStdio()									stdin = stdout = stderr = &usartStream
#define usartIsReceptionComplete()						isBitSet(UCSR0A, RXC0)
#define usartIsTransmissionComplete()					isBitSet(UCSR0A, TXC0)
#define usartIsBufferEmpty()							isBitSet(UCSR0A, UDRE0)
// Buffer
#define usartEnableReceiverBuffer()						usartConfiguration.receiverBufferEnable = 1
#define usartDisableReceiverBuffer()					usartConfiguration.receiverBufferEnable = 0

void usartInit(uint32 baudRate);
uint8 usartCheckError(void);
void usartTransmit(int8 data);
void usartTransmit9bits(uint16 data);
int16 usartTransmitStd(int8 data, FILE * stream);
uint8 usartReceive(void);
uint16 usartReceive9bits(void);
int16 usartReceiveStd(FILE * stream);
void usartClearReceptionBuffer(void);
void usartAddDataToReceiverBuffer(uint8 data);
uint8 usartGetDataFromReceiverBuffer(void);
uint8 usartIsReceiverBufferEmpty(void);
uint32 usartGetCurrentBaudRate(void);

#endif