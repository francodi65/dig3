
/*
===============================================================================
 Name        : TP5.c
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

unsigned int volatile * const FIODIR = (unsigned int*) aFIODIR;
unsigned int volatile * const FIOSET = (unsigned int*) aFIOSET;
unsigned int volatile * const FIOCLR = (unsigned int*) aFIOCLR;
unsigned int volatile * const FIOPIN = (unsigned int*) aFIOPIN;

unsigned int volatile * const IntEnR = (unsigned int*) aIntEnR;
unsigned int volatile * const IntClr = (unsigned int*) aIntClr;

unsigned int volatile * const T0IR = (unsigned int*) aT0IR;
unsigned int volatile * const T0TCR = (unsigned int*) aT0TCR;
unsigned int volatile * const T0TC = (unsigned int*) aT0TC;
unsigned int volatile * const T0PR = (unsigned int*) aT0PR;
unsigned int volatile * const T0PC = (unsigned int*) aT0PC;
unsigned int volatile * const T0MCR = (unsigned int*) aT0MCR;
unsigned int volatile * const T0MR0 = (unsigned int*) aT0MR0;


int number = 0;	//numero contado
int input = 10;	//pin del boton de interrupcion
int state = 0;	//lleva el estado de nuestra maquina de estados
int num[]= {63,6,91,79,102,109,125,7,127,103};	//array usado para conversion a binario

void setup();
void set(int num1,int num2);
void delay(int ms);

int main(void) {
	setup();
	while (1) {

	set(num[(number/10)],num[(number%10)]);
	}
	return 0;
}

void setup() {
	*FIODIR = 0x03FF; //Todos entradas menos los pines 0-15 que son salidas

	NVIC_EnableIRQ(EINT3_IRQn);
	*IntEnR |= (1<<input);

	*T0MCR |= (1<<0)| (1<<1);
	*T0PR = 0;
	*T0MR0= 30000000;
	*T0TC= 0;
	*T0TCR= (1<<0);

}

void EINT3_IRQHandler(){
	delay(200);
	*IntClr |= 0xFF;		//Bajo la bandera

	//set(6,6);
	if (state)
	{
		NVIC_DisableIRQ(TIMER0_IRQn);	      //Depende el estado, habilito o no las interrupciones x timer
		state=0;
	} else {
		state=1;
		*T0TC=0;
		set(0,0);
		//set(num[number/10],num[number%10]);
		NVIC_EnableIRQ(TIMER0_IRQn);
	}


}

void TIMER0_IRQHandler(){
	//Falta hacer la logica del timer, cuando llega una interrupcion que aumente un segundo hasta llega a 60.
	// Ya esta programado para que se interrumpa cada 1segundo.
	*T0IR|=(1<<0);
	number++;
	if (number==61)
	{
		number=0;
	}
	//set(num[number/10],num[number%10]);

}


void set(int num2,int num1) {
	/*
	 * Funcionamiento:
	 * El FIOSET pone en alto la salida cuando el bit correspondiente a su pin esta en 1.
	 * Si le envío por ejemplo el 8 en BCD (127 en decimal) en binario es 01111111, por lo cual si hago un
	 * OR con lo que contiene el registro FIOSET con ese valor, solo se pondrán en alto los bits 0-6.
	 * El FIOCLR pone en bajo la salida cuando el bit correspondiente a su pin esta en 1.
	 * Continuando con el ejemplo, si nuevo el valor "num" obtengo 0xFFFFFF80, por lo cuál, si hago un OR
	 * con eso, estaría modificando todos los valores de los pines a partir de 7. Por eso, se hace una AND,
	 * de este valor con 0x000000FF para que solo se puedan modificar los pines entre 0-7. En este caso,
	 * va a quedar utilizable solo 10000000, por lo cual el bit 7 se pondrá en 0 y los demás no se modifican.
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
	int delay= (30000000/1000)*ms;
	for (int i=0; i<delay; i++);
}
