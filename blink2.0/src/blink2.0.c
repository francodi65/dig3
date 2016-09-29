/*
===============================================================================
 Name        : blink2.0.c
 Author      : Grupo 11 Di Lorenzo y Del Boca
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#define AddrFIO0DIR 0x2009C000
#define AddrFIO0CLR 0x2009C01C
#define AddrFIO0SET 0x2009C018
#define aIntEnR 0x40028090
#define aIntClr 0x4002808C

unsigned int volatile *const FIO0DIR=(unsigned int *) AddrFIO0DIR;
unsigned int volatile *const FIO0CLR=(unsigned int *) AddrFIO0CLR;
unsigned int volatile *const FIO0SET=(unsigned int *) AddrFIO0SET;
unsigned int volatile * const IntClr = (unsigned int*) aIntClr;
unsigned int volatile * const IntEnR = (unsigned int*) aIntEnR;

extern void EsperaEnAssembler(int,int);
void setup();


#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int state=0;
int retardo=10000000;

int main(void) {
	setup();
	while(1){
		EsperaEnAssembler(retardo,state);
    }
    return 0 ;
}
void EINT3_IRQHandler(void){
	*IntClr=0xff;
	for(int i=0;i<6000000;i++);
	if(state==0){
		state=1;
	}else{
		state=0;
	}
}
void setup(){
	*FIO0DIR&=~(2<<0);
	*FIO0DIR|=(1<<22);
	*IntEnR|=(1<<1);
	NVIC_EnableIRQ(EINT3_IRQn);

}
