
/*
 * EraUmaVezUmaCasa
 * UM PROJETO DE AUTOMAÇÃO RESIDENCIAL
 *
 * Parido em: 16/12/2015 14:53:16
 * Desenvolvedores: ED e SIMAS
 * VERSAO 1.0
 *
 *ULTIMA ATUALIZACAO FEV/2016
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "ls_atmega328.h"
#include "ls_defines.h"
#include "ls_hd44780.h"

#define delay _delay_ms(30);

#define COOLER PC0
#define LED PC1
#define LM35 PC2
#define LDR PC3
#define LED2 PC4

#define ADC_LM35 ADC2
#define ADC_LDR ADC3

#define DISPLAY_PORT PORTB
#define DISPLAY_DDR DDRB

#define SERIAL_PORT PORTD
#define SERIAL_DDR DDRD

volatile int temp_LM35 = 0;
volatile int lux_LDR = 0;
volatile uint8 estado = 0;
volatile char channel = 'm';
volatile uint8 porta_aberta = 0;
volatile uint8 estado_porta = 0;
volatile char recebe_bt = 0;
volatile char transmit_bt = 0;
volatile char command = 0;

ISR(TIMER0_COMPA_vect);

ISR(TIMER2_COMPA_vect);
ISR(TIMER2_COMPB_vect);
ISR(ADC_vect);

void SelecionaCanal();
void ADC_SelecionaCanal();
void LuzNoturna();
void TaQuente();
void AbrirPorta();
void UsartBuffer();

//MaIN////////////////////////////////

int main(void)
{
	SERIAL_PORT = 0xFF;
	SERIAL_DDR = 0b00000010;
	
	PORTC = 0x00;
	DDRC = 0b00110011;
	
	DDRD = 0b11110010;
	
	// Configuração do Display
	/*lcdStdio();
	lcdInit();
	lcdDisplayOn();*/
	
	usartEnableTransmitter();
	usartEnableReceiver();
	usartStdio();
	usartInit(9600);
	
	int0SenseRisingEdge();
	int0ActivateInterrupt();
	
	// Configuração do Timer
	timer0ClockPrescaller1024();
	timer0ActivateCompareAInterrupt();
	timer0FastPWMMaxMode();
	timer0SetCompareAValue(50);

	timer0OC0BNonInvertedMode();
	timer0SetCompareBValue(estado_porta);
	timer0ActivateCompareBInterrupt();
			
	// Configuração do ADC
	adcReferenceAvcc();
	adcClockPrescaler128();
	adcEnableAutomaticMode();
	adcTriggerTimer0CompareMatchA();
	adcSelectChannel(ADC_LM35);
	adcResultRightAdjust();
	adcEnable();
	adcActivateInterrupt();
	adcStartConversion();
	
	sei();
	

	
    while(1)
    {
			TaQuente();
			UsartBuffer();
	}
}

//FIM DA MaIN//////////////////////////////

//FuNCOES/////////////////////////////////


void SelecionaCanal() //para selecionar canal adc a ser verificado
{
	switch (channel) //selecionar canal do conversor
	{
		case 'm': //caso esteja no canal do LM
		temp_LM35 = ADC * 5;
		temp_LM35 /= 10;
		printf("%d", temp_LM35);
		adcSelectChannel(ADC_LDR); //seleciona canal do LDR
		channel = 'r';
		delay;
		break;
		
		case 'r': //caso esteja no canal do LDR
		lux_LDR = ADC;
		adcSelectChannel(ADC_LM35); //seleciona canal do LM
		channel = 'm';
		delay;
		break;
	}
}


void LuzNoturna() //para ativar led quando luminosidade estiver baixa
{
	switch (command) //verifica comando manual desativado
	{
		case 0:
		if(lux_LDR <= 250)
		{
			setBit(PORTC, LED);
			setBit(PORTC, LED2);
			
		}
		
		
		else if(lux_LDR > 270)
		{
			clrBit(PORTC, LED);
			clrBit(PORTC, LED2);
		
		}
		
		break;
		
		default:
		break;
	}
	
}

void TaQuente() //para acionar cooler (climatizador) de acordo com a temperatura
{
	if(command == 0) //se comando manual estiver desativado
	{
		if(temp_LM35 >= 20) //para ativar
		setBit(PORTC, COOLER);
	
		if(temp_LM35 < 18)
		clrBit(PORTC, COOLER);
	}

}

void AbrirPorta() //para abrir ou fechar portas
{
	
	switch (recebe_bt) //verificar a variavel que recebe o dado pelo bluetooth
	{
		
		case 'd': //para fechar porta
		if(porta_aberta == 1){
			estado_porta = 0; //valor para o PWM do servo que movimenta a porta
			timer0SetCompareBValue(estado_porta);
			porta_aberta = 0; //porta está fechada
			_delay_ms(5);
		}
		break;
		
		case 'b': //para abrir porta
		if(porta_aberta == 0){
			estado_porta = 30;  //valor para o PWM do servo que movimenta a porta
			timer0SetCompareBValue(estado_porta);
			porta_aberta = 1; //porta está aberta
			_delay_ms(5);
		}
		break;
	}
	
}

void UsartBuffer() //para receber e enviar dados módulo bluetooth
{
		recebe_bt = usartReceive();	//para receber a informacao	
		
		//SWITCHZÃO RECEBE_BT
		switch (recebe_bt)
		{			
			
			//COMANDO MANUAL
			case 'x': //para habilitar e desabilitar comando manual
			if(command == 0) //se comando manual estiver desabilitado
			{
				printf("Sensores Ativados!\n");
				command = 1;
			}
			
			else if(command == 1) //se comando manual estiver habilitado
			{
				printf("Sensores Desativados!\n");
				command = 0;
			}
			break;
			
			//TEMPERATURA
			case 't': //se dado enviado for para ver a temperatura
			printf("Temperatura: %d C", temp_LM35);
			break;
			
			//
			case 'l': //se dado enviado for para ver o estado da luz
			
			if(command == 0)
			{
				if(isBitSet(PORTC, LED))
				printf("Luz Ligada!\n");
				
				if(isBitClr(PORTC, LED))
				printf("Luz Desligada!\n");
			}
			
			else if(command == 1)
			{
				if( isBitSet(PINC, LED)) //verifica se iluminação está ligada
				{
					clrBit(PORTC, LED); //desliga a luz 
					printf("Luz Desligada!\n");
				}
				
				else if(isBitClr(PINC, LED)) //verifica se iluminação está desligada
				{
					setBit(PORTC, LED); //liga a luz
					printf("Luz Ligada!\n");
				}
				
			}
			break;
			
			case 'k': //se dado enviado for para ver o estado da luz
			
			if(command == 0)
			{
				if(isBitSet(PORTC, LED2))
				printf("Luz Ligada!\n");
				
				if(isBitClr(PORTC, LED2))
				printf("Luz Desligada!\n");
			}
			
			else if(command == 1)
			{
				if(isBitSet(PINC, LED2)) //verifica se iluminação está ligada
				{
					clrBit(PORTC, LED2);
					printf("Luz2 Desligada!\n");
				}
				
				else if(isBitClr(PINC, LED2)) //verifica se iluminação está desligada
				{
					setBit(PORTC, LED2);
					printf("Luz2 Ligada!\n");
				}
				
			}
			break;			
			
			//COOLER
			case 'c': //se dado enviado for para ver o estado do cooler
			if(command == 0)
			{
				if(temp_LM35 >= 15)
				printf("Cooler Ligado!\n");
				if(temp_LM35 < 12)
				printf("Cooler Desligado!\n");
			}
			
			else if(command == 1)
			{
				if(isBitSet(PINC, COOLER)) //verifica se cooler está ligado
				clrBit(PORTC, COOLER);
					
				else if(isBitClr(PINC, COOLER)) //verifica se cooler está desligado
				setBit(PORTC, COOLER);
			}
			break;
			
			//PORTA
			case 'p': //se dado enviado for para ver o estado da porta
			if(porta_aberta == 1)
			printf("Porta Aberta!\n");
			if(porta_aberta == 0)
			printf("Porta Fechada!\n");				
			break;
			
			//VERIFICAR TUDO
			case 'f':
			if(command == 0)
			printf("Sensores Ativados!\n");
			if(command == 1)
			printf("Sensores Desativados!\n");
			printf("Temperatura: %d", temp_LM35);
			if(isBitSet(PORTC, LED))
			printf("Luz Ligada!\n");
			if(isBitClr(PORTC, LED))
			printf("Luz Desligada!\n");
			if(isBitSet(PORTC, LED2))
			printf("Luz2 Ligada!\n");
			if(isBitClr(PORTC, LED2))
			printf("Luz2 Desligada!\n");
			if(isBitSet(PORTC, COOLER))
			printf("Cooler Ligado!\n");
			if(isBitClr(PORTC, COOLER))
			printf("Cooler Desligado!\n");
			if(porta_aberta == 1)
			printf("Porta Aberta!\n");
			if(porta_aberta == 0)
			printf("Porta Fechada!\n");
			break;
			
		}

		
}

//InTERRUPCOES////////////////////////////////////

ISR(TIMER0_COMPA_vect)
{
	
}

ISR(TIMER0_COMPB_vect)
{
	AbrirPorta();
}

ISR(ADC_vect)
{
	SelecionaCanal();
	LuzNoturna();	
	
	adcWaitConversionFinish();
	adcClearInterruptRequest();
}

ISR(INT0_vect)
{
	switch(porta_aberta) //verificar o estado da porta
	{
	
	case 1:
		estado_porta = 0; //valor para o PWM do servo que movimenta a porta
		timer0SetCompareBValue(estado_porta);
		porta_aberta = 0; //porta está fechada
		_delay_ms(25);
	break;
	
	case 0: //para abrir porta
		estado_porta = 30;  //valor para o PWM do servo que movimenta a porta
		timer0SetCompareBValue(estado_porta);
		porta_aberta = 1; //porta está aberta
		_delay_ms(25);
	break;
	
	}
}


//FIM DO CóDIGO/////////////////////////////////
