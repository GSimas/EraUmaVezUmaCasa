/* -----------------------------------------------------------------------------
 * File:			LS_ATmega328.c
 * Module:			ATmega328 basic interface
 * Author:			Leandro Schwarz
 * Version:			7.3
 * Last edition:	15/09/2014
 * -------------------------------------------------------------------------- */

// -----------------------------------------------------------------------------
// Header files ----------------------------------------------------------------

#include "LS_ATmega328.h"
#if __LS_ATMEGA328_H != 73
	#error Error 101 - Version mismatch on header and source code files (LS_ATmega328).
#endif

// -----------------------------------------------------------------------------
// Global variables ------------------------------------------------------------

adcConfiguration_t		adcConfiguration;
spiConfiguration_t		spiConfiguration;
usartConfiguration_t	usartConfiguration;
FILE usartStream = FDEV_SETUP_STREAM(usartTransmitStd, usartReceiveStd, _FDEV_SETUP_RW);
uint8 usartReceiverBuffer[USART_RECEIVER_BUFFER_SIZE];
uint8 usartReceiverBufferNextRead;	// Pointer to the next read location
uint8 usartReceiverBufferNextWrite;	// Pointer to the next write location
uint8 usartReceiverBufferLength;	// Buffer length

/* -----------------------------------------------------------------------------
 * Writes a byte in the specified address in the EEPROM
 * -------------------------------------------------------------------------- */

void eepromWrite(uint8 data, uint16 address)
{
	waitUntilBitIsClear(EECR, EEPE);
	EEAR = (address & 0x01FF);
	EEDR = data;
	setBit(EECR, EEMPE);
	setBit(EECR, EEPE);
	return;
}

/* -----------------------------------------------------------------------------
 * Reads a byte from the specified address in the EEPROM
 * -------------------------------------------------------------------------- */

uint8 eepromRead(uint16 address)
{
	waitUntilBitIsClear(EECR, EEPE);
	EEAR = (address & 0x01FF);
	setBit(EECR, EERE);
	return EEDR;
}

/* -----------------------------------------------------------------------------
 * Writes the value of register TCNT1 of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

void timer1SetCounterValue(uint16 value)
{
	uint8 sreg;

	sreg = SREG;
	cli();
	TCNT1 = value;
	SREG = sreg;

	return;
}

/* -----------------------------------------------------------------------------
 * Reads the value of register TCNT1 of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

uint16 timer1GetCounterValue(void)
{
	uint8 sreg;
	uint16 aux;

	sreg = SREG;
	cli();
	aux = TCNT1;
	SREG = sreg;

	return aux;
}

/* -----------------------------------------------------------------------------
 * Writes the value of register OCR1A of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

void timer1SetCompareAValue(uint16 value)
{
	uint8 sreg;

	sreg = SREG;
	cli();
	OCR1A = value;
	SREG = sreg;

	return;
}

/* -----------------------------------------------------------------------------
 * Reads the value of register OCR1A of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

uint16 timer1GetCompareAValue(void)
{
	uint8 sreg;
	uint16 aux;

	sreg = SREG;
	cli();
	aux = OCR1A;
	SREG = sreg;

	return aux;
}

/* -----------------------------------------------------------------------------
 * Writes the value of register OCR1B of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

void timer1SetCompareBValue(uint16 value)
{
	uint8 sreg;

	sreg = SREG;
	cli();
	OCR1B = value;
	SREG = sreg;

	return;
}

/* -----------------------------------------------------------------------------
 * Reads the value of register OCR1B of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

uint16 timer1GetCompareBValue(void)
{
	uint8 sreg;
	uint16 aux;

	sreg = SREG;
	cli();
	aux = OCR1B;
	SREG = sreg;

	return aux;
}

/* -----------------------------------------------------------------------------
 * Writes the value of register ICR1 of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

void timer1SetInputCaptureValue(uint16 value)
{
	uint8 sreg;

	sreg = SREG;
	cli();
	ICR1 = value;
	SREG = sreg;

	return;
}

/* -----------------------------------------------------------------------------
 * Reads the value of register ICR1 of timer1 using atomic mode
 * -------------------------------------------------------------------------- */

uint16 timer1GetInputCaptureValue(void)
{
	uint8 sreg;
	uint16 aux;

	sreg = SREG;
	cli();
	aux = ICR1;
	SREG = sreg;

	return aux;
}

/* -----------------------------------------------------------------------------
 * Configures the SPI controller
 * -------------------------------------------------------------------------- */

void spiInit(void)
{
	if(spiConfiguration.masterSlave){
		setBit(SPI_DDR, SPI_MOSI);
		setBit(SPI_DDR, SPI_SCK);
		clrBit(SPI_DDR, SPI_MISO);
	}else{
		clrBit(SPI_DDR, SPI_MOSI);
		clrBit(SPI_DDR, SPI_SCK);
		setBit(SPI_DDR, SPI_MISO);
	}
	if(spiConfiguration.doubleSpeed)
		setBit(SPSR, SPI2X);
	else
		clrBit(SPSR, SPI2X);
	SPCR =	(spiConfiguration.interruptEnabled << SPIE) | 
			(spiConfiguration.enabled << SPE) | 
			(spiConfiguration.msbLsb << DORD) | 
			(spiConfiguration.masterSlave << MSTR) | 
			(spiConfiguration.sckIdleValue << CPOL) | 
			(spiConfiguration.leadingTrailingEdge << CPHA) | 
			(spiConfiguration.clockPrescaler & 0x03);

	return;
}

/* -----------------------------------------------------------------------------
 * Transmit data at the SPI bus in master mode
 * -------------------------------------------------------------------------- */

uint8 spiMasterTransmit(uint8 data)
{
	SPDR = data;
	waitUntilBitIsClear(SPSR, SPIF);
	return SPDR;
}

/* -----------------------------------------------------------------------------
 * Receives data from the SPI bus
 * -------------------------------------------------------------------------- */

uint8 spiSlaveTransmit(void)
{
	waitUntilBitIsClear(SPSR, SPIF);
	return SPDR;
}

/* -----------------------------------------------------------------------------
 * Get the current ADC configuration
 * -------------------------------------------------------------------------- */

adcConfiguration_t adcGetConfiguration(void)
{
	return adcConfiguration;
}

/* -----------------------------------------------------------------------------
 * Load an ADC configuration
 * -------------------------------------------------------------------------- */

void adcLoadConfiguration(adcConfiguration_t config)
{
	adcConfiguration = config;

	ADMUX =	((config.reference & 0x03) << 6) | 
			(config.leftAdjust << 5) | 
			(config.channel & 0x0F);
	ADCSRA =	(config.enabled << 7) |
				(config.automaticMode << 5) |
				(config.interruptEnabled << 3) |
				(config.clockPrescaller & 0x07);
	ADCSRB =	(config.analogComparator << 6) |
				(config.triggerSource & 0x07);
	DIDR0 =	config.digitalDisabled & 0x3F;
	return;
}

/* -----------------------------------------------------------------------------
 * Configures the USART controller
 * -------------------------------------------------------------------------- */

void usartInit(uint32 baudRate)
{
	uint64 aux64;

	// Clear errors
	UCSR0A &= 0xE3;
	usartConfiguration.frameError = 0;
	usartConfiguration.bufferOverflowError = 0;
	usartConfiguration.parityError = 0;

	// USART configuration
	switch(usartConfiguration.mode){
	case 0:
		clrBit(UCSR0A, U2X0);			// Normal speed
		clrBit(UCSR0C, UCPOL0);			// Write zero in asynchronous mode
		clrBit(UCSR0C, UMSEL01);		// Asynchronous mode
		clrBit(UCSR0C, UMSEL00);		// Asynchronous mode
		aux64 = F_CPU / 16 / baudRate;
		usartConfiguration.ubrr = (uint16)(aux64 - 1);
		break;
	case 1:
		setBit(UCSR0A, U2X0);			// Double speed
		clrBit(UCSR0C, UCPOL0);			// Write zero in asynchronous mode
		clrBit(UCSR0C, UMSEL01);		// Asynchronous mode
		clrBit(UCSR0C, UMSEL00);		// Asynchronous mode
		aux64 = F_CPU / 8 / baudRate;
		usartConfiguration.ubrr = (uint16)(aux64 - 1);
		break;
	case 2:
		clrBit(UCSR0A, U2X0);			// Write zero in synchronous mode
		if(usartConfiguration.polarity)
			setBit(UCSR0C, UCPOL0);		// XCK rising edge
		else
			clrBit(UCSR0C, UCPOL0);		// XCK falling edge
		clrBit(UCSR0C, UMSEL01);		// Synchronous mode
		setBit(UCSR0C, UMSEL00);		// Synchronous mode
		break;
	case 3:
		clrBit(UCSR0A, U2X0);			// Write zero in synchronous mode
		if(usartConfiguration.polarity)
			setBit(UCSR0C, UCPOL0);		// XCK rising edge
		else
			clrBit(UCSR0C, UCPOL0);		// XCK falling edge
		setBit(UCSR0C, UMSEL01);		// Master SPI mode
		setBit(UCSR0C, UMSEL00);		// Master SPI mode
		aux64 = F_CPU / 2 / baudRate;
		usartConfiguration.ubrr = (uint16)(aux64 - 1);
		break;
	}

	// Sets the baud rate
	UBRR0H = (uint8)(usartConfiguration.ubrr >> 8);
	UBRR0L = (uint8)usartConfiguration.ubrr;

	// Receiver buffer
	if(usartConfiguration.receiverBufferEnable)
		usartActivateReceptionCompleteInterrupt();

	return;
}

/* -----------------------------------------------------------------------------
 * Checks if an error occurred during transmission or reception
 * -------------------------------------------------------------------------- */

uint8 usartCheckError(void)
{
	usartConfiguration.frameError = isBitSet(UCSR0A, FE0);
	usartConfiguration.bufferOverflowError = isBitSet(UCSR0A, DOR0);
	usartConfiguration.parityError = isBitSet(UCSR0A, UPE0);
	return (usartConfiguration.parityError | usartConfiguration.bufferOverflowError | usartConfiguration.frameError);
}

/* -----------------------------------------------------------------------------
 * Transmits data in 5, 6, 7 or 8 bits modes using the USART controller
 * -------------------------------------------------------------------------- */

void usartTransmit(int8 data)
{
	
	while(!usartIsBufferEmpty())
		;	// Waits until last transmission ends
	UDR0 = data;
	return;
}

/* -----------------------------------------------------------------------------
 * Transmits data in 9 bits mode using the USART controller
 * -------------------------------------------------------------------------- */

void usartTransmit9bits(uint16 data)
{
	uint8 aux;

	while(!usartIsBufferEmpty())
		;	// Waits until last transmission ends
	aux = ((data & 0x100) >> 8);
	if(aux)
		setBit(UCSR0B, TXB80);
	else
		clrBit(UCSR0B, TXB80);
	UDR0 = (uint8)data;
	return;
}

/* -----------------------------------------------------------------------------
 * Transmits data in 5, 6, 7 or 8 bits modes using the USART controller and
 * standard output heandler
 * -------------------------------------------------------------------------- */

int16 usartTransmitStd(int8 data, FILE * stream)
{
	while(!usartIsBufferEmpty())
		;	// Waits until last transmission ends
	UDR0 = data;
	return FALSE;
}

/* -----------------------------------------------------------------------------
 * Receives data in 5, 6, 7 or 8 bits modes using the USART controller
 * -------------------------------------------------------------------------- */

uint8 usartReceive(void)
{
	uint8 status;

	while(!usartIsReceptionComplete())
		;	// Waits until last reception ends
	status = UCSR0A;
	usartConfiguration.frameError = isBitSet(status, FE0);
	usartConfiguration.bufferOverflowError = isBitSet(status, DOR0);
	usartConfiguration.parityError = isBitSet(status, UPE0);
	return UDR0;
}

/* -----------------------------------------------------------------------------
 * Receives data in 9 bits modes using the USART controller
 * -------------------------------------------------------------------------- */

uint16 usartReceive9bits(void)
{
	uint8 status;
	uint8 byteh;
	uint8 bytel;
	uint16 byte;

	while(!usartIsReceptionComplete())
		;	// Waits until last reception ends
	status = UCSR0A;
	byteh = UCSR0B;
	bytel = UDR0;

	usartConfiguration.frameError = isBitSet(status, FE0);
	usartConfiguration.bufferOverflowError = isBitSet(status, DOR0);
	usartConfiguration.parityError = isBitSet(status, UPE0);

	byte = (uint16)(byteh & 0x02) << 7;
	byte |= bytel;
	return  byte;
}

/* -----------------------------------------------------------------------------
 * Receives data in 5, 6, 7 or 8 bits modes using the USART controller and
 * standard input heandler
 * -------------------------------------------------------------------------- */

int16 usartReceiveStd(FILE * stream)
{
	while(!usartIsReceptionComplete())
		;	// Waits until last reception ends
	return (int16)UDR0;
}

/* -----------------------------------------------------------------------------
 * Clears the receptor data buffer
 * -------------------------------------------------------------------------- */

void usartClearReceptionBuffer(void)
{
	uint8 aux;
	while(usartIsReceptionComplete())
		aux = UDR0;
	return;
}

/* -----------------------------------------------------------------------------
 * Adds data to the reception buffer. The function has NO CONTROL of lost data.
 * -------------------------------------------------------------------------- */

void usartAddDataToReceiverBuffer(uint8 data)
{
	if(((usartReceiverBufferNextWrite + 1) % USART_RECEIVER_BUFFER_SIZE) != usartReceiverBufferNextRead){
		usartReceiverBuffer[usartReceiverBufferNextWrite] = data;
		usartReceiverBufferNextWrite = (usartReceiverBufferNextWrite + 1) % USART_RECEIVER_BUFFER_SIZE;
		usartReceiverBufferLength++;
	}
	return;
}

/* -----------------------------------------------------------------------------
 * Gets data from the reception buffer. If the buffer is empty, the last
 * retrieved data will be returned and the pointer will not be changed. The
 * usartIsReceiverBufferEmpty() function must be called to check if there is new
 * data in the buffer.
 * -------------------------------------------------------------------------- */

uint8 usartGetDataFromReceiverBuffer(void)
{
	uint8 data = usartReceiverBuffer[usartReceiverBufferNextRead];
	if(usartReceiverBufferLength > 0){
		usartReceiverBufferNextRead = (usartReceiverBufferNextRead + 1) % USART_RECEIVER_BUFFER_SIZE;
		usartReceiverBufferLength--;
	}
	return data;
}

/* -----------------------------------------------------------------------------
 * Verifies if there is new data in the receiver buffer. Must be called before
 * reading the buffer.
 * -------------------------------------------------------------------------- */

uint8 usartIsReceiverBufferEmpty(void)
{
	if(usartReceiverBufferLength == 0)
		return TRUE;
	return FALSE;
}

/* -----------------------------------------------------------------------------
 * Returns the current baud rate.
 * -------------------------------------------------------------------------- */

 uint32 usartGetCurrentBaudRate(void)
 {
	uint32 aux32 = 0;

	switch(usartConfiguration.mode){
	case 0:
		aux32 = F_CPU / 16 / (UBRR0 + 1);
		break;
	case 1:
		aux32 = F_CPU / 8 / (UBRR0 + 1);
		break;
	case 2:
		aux32 = F_CPU / 2 / (UBRR0 + 1);
		break;
	}
	return aux32;
 }