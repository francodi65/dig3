/*
===============================================================================
 Name        : VOLTIMETRO.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#define aFIODIR 0x2009C000
#define aFIOSET 0x2009C018
#define aFIOCLR 0x2009C01C
#define aFIOPIN 0x2009C014
#define aIntEnR 0x40028090
#define aIntClr 0x4002808C
#define aT0IR 	0x40004000
#define aT0TCR	0x40004004
#define	aT0TC	0x40004008
#define aT0PR	0x4000400C
#define aT0PC	0x40004010
#define aT0MCR	0x40004014
#define aT0MR0	0x40004018
#define aPCONP	0x400FC0C4
#define aAD0CR	0x40034000
#define aPINSEL1 0x4002C004
#define aADDR0 	0x40034010

unsigned int volatile * const FIODIR = (unsigned int*) aFIODIR;
unsigned int volatile * const FIOSET = (unsigned int*) aFIOSET;
unsigned int volatile * const FIOCLR = (unsigned int*) aFIOCLR;
unsigned int volatile * const FIOPIN = (unsigned int*) aFIOPIN;

unsigned int volatile * const T0IR = (unsigned int*) aT0IR;
unsigned int volatile * const T0TCR = (unsigned int*) aT0TCR;
unsigned int volatile * const T0TC = (unsigned int*) aT0TC;
unsigned int volatile * const T0PR = (unsigned int*) aT0PR;
unsigned int volatile * const T0PC = (unsigned int*) aT0PC;
unsigned int volatile * const T0MCR = (unsigned int*) aT0MCR;
unsigned int volatile * const T0MR0 = (unsigned int*) aT0MR0;

unsigned int volatile * const PCONP = (unsigned int*) aPCONP;
unsigned int volatile * const AD0CR = (unsigned int*) aAD0CR;
unsigned int volatile * const PINSEL1 = (unsigned int*) aPINSEL1;
unsigned int volatile * const ADDR0 = (unsigned int*) aADDR0;


int num[]= {63,6,91,79,102,109,125,7,127,103};	//array usado para conversion a binario
int num1= 0;
int num2= 0;

void setup();
void set(int num1,int num2);
void delay(int ms);

int main(void) {
	setup();

	while (1) {
		set(num[num1],num[num2]);

	}
	return 0;
}

void setup() {
	*FIODIR = 0x03FF; //Todos entradas menos los pines 0-10 que son salidas
	//NVIC_EnableIRQ(ADC_IRQn);

		LPC_SC -> PCONP |= 2;						//Enciendo Timer0
		LPC_TIM0 -> TCR |= 2;						//Reset de TC
		LPC_TIM0 -> PR = SystemCoreClock/(4*1000)-1;//1ms
		LPC_TIM0 -> MCR = 1 << 10;					//Reset Match 3
		LPC_TIM0 -> MR3 = 25;						//define Match 3 en 25
		LPC_TIM0 -> EMR = 3 << 10;					//Selecciona match externo.

		LPC_SC -> PCONP |= (1<<12);					//Enciende ADC
		LPC_PINCON -> PINSEL1 |=(1 << 14);			//Configuro entradas analogicas
		LPC_PINCON -> PINSEL1 &=~(1<<15);
		LPC_ADC -> ADCR |= (1<<0);					//Canal 0
		LPC_ADC->ADCR |= (1 << 8); 					//Frecuencia/2
		LPC_ADC->ADCR |= (1 << 21); 				//Prendo ADC
		LPC_ADC->ADCR &= ~(1 << 27); 				//Flanco de MR3 de subida
		LPC_ADC->ADCR |= (5 << 24); 				//Convierte en flanco de MR3
		LPC_ADC->ADINTEN = 1; 						//Interrupcion ADC

		NVIC_EnableIRQ(ADC_IRQn);					//Habilito interrupcion por ADC

		LPC_TIM0->TCR=1;
}


void ADC_IRQHandler(){
	num1=0;
	num2=0;
	float value = 0;
	if(LPC_ADC->ADDR0 & (1<<31)){			//Controlo de que canal es la muestra
			value = (LPC_ADC->ADDR0>>4) & 0xfff;	//Almaceno valor muestreado

			value=(value/4096)*33;
			num2=value/10;
			num1=(int)value%10;

		}



}


void set(int num1,int num2) {
	/*
	 * Funcionamiento:
	 * El FIOSET pone en alto la salida cuando el bit correspondiente a su pin esta en 1.
	 * Si le envÃ­o por ejemplo el 8 en BCD (127 en decimal) en binario es 01111111, por lo cual si hago un
	 * OR con lo que contiene el registro FIOSET con ese valor, solo se pondrÃ¡n en alto los bits 0-6.
	 * El FIOCLR pone en bajo la salida cuando el bit correspondiente a su pin esta en 1.
	 * Continuando con el ejemplo, si nuevo el valor "num" obtengo 0xFFFFFF80, por lo cuÃ¡l, si hago un OR
	 * con eso, estarÃ­a modificando todos los valores de los pines a partir de 7. Por eso, se hace una AND,
	 * de este valor con 0x000000FF para que solo se puedan modificar los pines entre 0-7. En este caso,
	 * va a quedar utilizable solo 10000000, por lo cual el bit 7 se pondrÃ¡ en 0 y los demÃ¡s no se modifican.
	 */


	*FIOCLR |= 0xFF;
	*FIOSET |= num1;
	*FIOCLR |= ((~num1) & 0xFF);
	*FIOSET |= (1<<8);

	delay(1);
	*FIOCLR |= (1<<8);
	*FIOCLR |= 0xFF;

	*FIOSET |= num2;
	*FIOCLR |= ((~num2) & 0xFF);
	*FIOSET |= (1<<9);

	delay(1);
	*FIOCLR |= (1<<9);
	*FIOCLR |= 0xFF;


}

void delay(int ms){
	int volatile delay= (30000000/1000)*ms;
	for (int i=0; i<delay; i++);

}
