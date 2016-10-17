/*
 ===============================================================================
 Name        : Blink Timer.c
 Author      : Di Lorenzo Franco, Del Boca Juan
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
#define AddrPLL0CON		0x400FC080
#define AddrPLL0FEED	0x400FC08C
#define AddrPLL0CFG		0x400FC084
#define AddrPLL0STAT	0x400FC088

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

void delay(int);
void setup();

int main(void) {
	int time = 1500000;
	setup();

	while (1) {
		if ((*FIO0PIN & (1 << 22)) == 0) {
			*FIO0SET |= (1 << 22);
			delay(time);
		} else {
			*FIO0CLR |= (1 << 22);
			delay(time);
		}
	}
	return 0;
}

void delay(int time) {
	for (int i = 0; i < time; i++);
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
	*CCLKCFG |= (1<<1);				//Divisor por 3


	//*PLL0CFG &= ~(0x3FFF);			// M=0
	//*PLL0CFG &= ~(0xFF << 16);		// N=0
	*PLL0CFG |= (2 << 0);				// M=3
	*PLL0CFG |= (1 << 16);				// N=2
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;
	*PLL0CON |= (1 << 0);				//Habilitar PLL
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;
	while ((*PLL0STAT & (1 << 26)) == 0);

	*PLL0CON |= (1 << 1);			//Conectar PLL
	*PLL0FEED |= 0xAA;				//Guardo los cambios
	*PLL0FEED |= 0x55;






}

