/*
===============================================================================
 Name        : Interrupcion.c
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

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
void setup(void);
int main(void) {
	setup();

    // TODO: insert code here

    // Force the counter to be placed into memory
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	if((*FIOPIN&(1<<1))!=0){
    		for(int i=0;i<3000000;i++);
    			if((*FIOPIN&(1<<22))!=0){
    				*FIOCLR|=(1<<22);
    			}else{
    				*FIOSET|=(1<<22);
    			}

    }
    }
    return 0 ;
}
setup(){
	*FIODIR&=~(2<<0);
	*FIODIR|=(1<<22);
}
