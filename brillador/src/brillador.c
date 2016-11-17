/*
===============================================================================
 Name        : brillador.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#define AddrFIO0DIR 	0x2009C000
#define AddrFIO0SET 	0x2009C018
#define AddrFIO0CLR 	0x2009C01C
#define AddrFIO0PIN 	0x2009C014

#define AddrSCS 		0x400FC1A0
#define AddrCLKSRCSEL	0x400FC10C
#define AddrCCLKCFG		0x400FC104

#define AddrT0TCR		0x40004004
#define AddrT0TC		0x40004008
#define AddrT0PR		0x4000400C
#define AddrT0PC		0x40004010
#define AddrT0MCR		0x40004014
#define AddrT0MR0		0x40004018
#define AddrT0MR1		0x4000401C
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

unsigned int volatile * const T0TCR = (unsigned int *) AddrT0TCR;
unsigned int volatile * const T0TC = (unsigned int *) AddrT0TC;
unsigned int volatile * const T0PR = (unsigned int *) AddrT0PR;
unsigned int volatile * const T0PC = (unsigned int *) AddrT0PC;
unsigned int volatile * const T0MCR = (unsigned int *) AddrT0MCR;
unsigned int volatile * const T0MR0 = (unsigned int *) AddrT0MR0;
unsigned int volatile * const T0MR1 = (unsigned int *) AddrT0MR1;
unsigned int volatile * const T0CTCR = (unsigned int *) AddrT0CTCR;
unsigned int volatile * const T0EMR = (unsigned int *) AddrT0EMR;
unsigned int volatile * const T0IR = (unsigned int *) AddrT0IR;

unsigned int volatile * const IntEnR = (unsigned int *) 0x00000000;
unsigned int volatile * const IntClr = (unsigned int *) 0x00000000;

void setup();
int state;
int main(void) {

    setup();
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}


void setup(){
	/* Captura:

	*T0CTCR&= (3<<2);			//Capturo por CAP0
	*T0CCR|= (5<<0);			//Capturo por alto e interrumpe
	*T0CR0 --> aca estan los datos grabados.
	 */

	*T0MCR|= (3<<0);		// Resetea e interrumpe match 0
	*T0MCR|= (1<<2);		// Interrumpe match 1

	*T0PR= 0;				//Preescaler en 0;
	*T0MR0= 60000;
	*T0MR1= 30000;
	*T0TCR|=(1<<0);			//arranco timer
	*IntEnR |=(1<<0);		//seteo pin 0 como interrupcion por flanco ascendente
	*TC=0;

	NVIC_EnableIRQ(EINT3_IRQn);		//habilito interrupciones
	NVIC_EnableIRQ(TIMER0_IRQn);
}

void Timer0_IRQHandler(void){
	*T0IR |= (3 << 0);					//Levanto la bandera de interrupción
	if(*FIO0PIN&(1<<22)){
		*FIO0CLR|=(1<<22);
	}else{
		*FIO0SET|=(1<<22);
	}

void Eint3_IRQHandler(void){

	switch(state){
	case 0:
		//gana wolfi *T0MR0=*T0MR0*2;
		*T0MR0<<1;
		break;
	case 1:
		*T0MR0<<1;
		break;
	case 2:
		*T0MR0<<1;
		break;
	case 3:
		*T0MR0<<1;
		break;
	case 4:
		*T0MR0>>4;
		state=0;
		break;
	}
	*IntClr |= 0xFF; //bajo flag de int
}
}
