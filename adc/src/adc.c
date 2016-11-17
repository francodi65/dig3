/*
===============================================================================
 Name        : adc.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


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

void setup();
int main(void) {

	setup();
    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}

void setup (){
	*PCONP|= (1<<12);					//Habilito adc

	*PINSEL1|= (1<<14);					//Habilito P0.23 como ADC0
	*PINSEL1&= ~(1<<15);

	*ADCR|= (1<<0);					//Selecciono canal 0
	*ADCR|= (1<<8);					//Divido cclk/2

	*ADCR|= (1<<16);				// Burst ON
	*ADCR&= ~(7<<24);				// START en 000 para que funcione burst

	*ADCR|= (1<<21); 				//START burst


}
