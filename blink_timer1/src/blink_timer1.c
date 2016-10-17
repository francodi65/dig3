/*
 ===============================================================================
 Name        : Blink Timer.c
 Author      : Di Lorenzo Franco, Del Boca Juan
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#include "LPC17xx.h"

#define AddrFIO0DIR 	0x2009C000
#define AddrFIO0SET 	0x2009C018
#define AddrFIO0CLR 	0x2009C01C
#define AddrFIO0PIN 	0x2009C014

#define AddrSCS 		0x400FC1A0
#define AddrCLKSRCSEL	0x400FC10C
#define AddrCCLKCFG		0x400FC104

#define AddrPLL0CON		0x400FC080
#define AddrPLL0FEED	0x400FC08C
#define AddrPLL0CFG		0x400FC084
#define AddrPLL0STAT	0x400FC088

#define AddrT0TCR		0x40004004
#define AddrT0TC		0x40004008
#define AddrT0PR		0x4000400C
#define AddrT0PC		0x40004010
#define AddrT0MCR		0x40004014
#define AddrT0MR0		0x40004018
#define AddrT0CTCR		0x40004070
#define AddrT0EMR		0x4000403C
#define AddrT0IR		0x40004000

unsigned int volatile * const FIO0DIR = (unsigned int *) AddrFIO0DIR;
unsigned int volatile * const FIO0SET = (unsigned int *) AddrFIO0SET;
unsigned int volatile * const FIO0CLR = (unsigned int *) AddrFIO0CLR;
unsigned int volatile * const FIO0PIN = (unsigned int *) AddrFIO0PIN;

unsigned int volatile * const SCS = (unsigned int *) AddrSCS;
unsigned int volatile * const CLKSRCSEL = (unsigned int *) AddrCLKSRCSEL;
unsigned int volatile * const CCLKCFG = (unsigned int *) AddrCCLKCFG;

unsigned int volatile * const PLL0CON = (unsigned int *) AddrPLL0CON;
unsigned int volatile * const PLL0FEED = (unsigned int *) AddrPLL0FEED;
unsigned int volatile * const PLL0CFG = (unsigned int *) AddrPLL0CFG;
unsigned int volatile * const PLL0STAT = (unsigned int *) AddrPLL0STAT;

unsigned int volatile * const T0TCR = (unsigned int *) AddrT0TCR;
unsigned int volatile * const T0TC = (unsigned int *) AddrT0TC;
unsigned int volatile * const T0PR = (unsigned int *) AddrT0PR;
unsigned int volatile * const T0PC = (unsigned int *) AddrT0PC;
unsigned int volatile * const T0MCR = (unsigned int *) AddrT0MCR;
unsigned int volatile * const T0MR0 = (unsigned int *) AddrT0MR0;
unsigned int volatile * const T0CTCR = (unsigned int *) AddrT0CTCR;
unsigned int volatile * const T0EMR = (unsigned int *) AddrT0EMR;
unsigned int volatile * const T0IR = (unsigned int *) AddrT0IR;

void setup();

int main(void) {
	int time = 1500000;
	setup();
	NVIC_EnableIRQ(TIMER0_IRQn);

	while (1) {
	}
	return 0;
}

void setup() {
	*FIO0DIR |= (1 << 22);			//Pin 22 salida (led)

	*PLL0CON &= ~(3 << 0);			//Desactivo y deshabilito PLL0
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;

	*SCS |= (1 << 5);					//Activo el cristal
	while ((*SCS & (1 << 6)) == 0);		//Espero que se active

	*CLKSRCSEL |= (1 << 0);			//Selecciono el cristal como fuente
	*CLKSRCSEL &= ~(1 << 1);		//""

	*CCLKCFG &= ~(0xFF);			//Divisor por 1

	/*
	*PLL0CFG |= (2 << 0);				// M=3
	*PLL0CFG |= (1 << 16);				// N=2
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;
	*PLL0CON |= (1 << 0);				//Habilitar PLL
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;
	while ((*PLL0STAT & (1 << 26)) == 0);

	*PLL0CON |= (3 << 0);			//Conectar PLL
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;
	while (((*PLL0STAT & ((1<<25) | (1<<24)))) == 0);
	*/

	*T0CTCR &= ~(3 << 0); 			//Contador funciona como timer
	*T0PR = 0;						// Prescaler =0
	*T0MR0 = 3000000;				// Match en 3MHz
	*T0MCR |= (3 << 0);			// Reset TC cuando llega al Match e interrumpe
	*T0TC = 0;						// TC=0
	*T0TCR |= (1 << 0);				//Activo el TC
}

void TIMER0_IRQHandler( TIMER0_IRQn) {
	*T0IR |= (1 << 0);					//Levanto la bandera de interrupción
	if ((*FIO0PIN & (1 << 22)) == 0)
		*FIO0SET |= (1 << 22);
	else
		*FIO0CLR |= (1 << 22);

}

