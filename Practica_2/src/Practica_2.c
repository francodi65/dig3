/*
===============================================================================
 Name        : Practica_2.c
 Author      : Di Lorenzo Franco, Del Boca Juan
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <stdint.h>

#define AddrFIO0DIR 0x2009C000
#define AddrFIO0SET 0x2009C018
#define AddrFIO0CLR 0x2009C01C
#define AddrFIO0PIN 0x2009C014

unsigned int volatile * const FIO0DIR = (unsigned int *) AddrFIO0DIR;
unsigned int volatile * const FIO0SET = (unsigned int *) AddrFIO0SET;
unsigned int volatile * const FIO0CLR = (unsigned int *) AddrFIO0CLR;
unsigned int volatile * const FIO0PIN = (unsigned int *) AddrFIO0PIN;

int main(void) {

	*FIO0DIR |= (1 << 1);
	*FIO0DIR &= (~(1 << 2));
	while (1) {
		if (*FIO0PIN & (1 << 2))
			*FIO0SET |= (1 << 1);
		else
			*FIO0CLR |= (1 << 1);
	}

	return 0;
}
