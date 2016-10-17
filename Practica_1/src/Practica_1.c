/*
 ===============================================================================
 Name        : Practica_1.c
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

int delay(int);

int main(void) {
	uint32_t j;
	uint32_t time = 5000;

	*FIO0DIR |= (1 << 22);

	while (1) {

		for (j = 0; j < 200; j++) {
			*FIO0SET |= (1 << 22);
			delay(time);
		}
		for (j = 0; j < 200; j++) {
			*FIO0CLR |= (1 << 22);
			delay(time);
		}
		time += 8000;

		for (j = 0; j < 200; j++) {
			*FIO0SET |= (1 << 22);
			delay(time);
		}
		for (j = 0; j < 200; j++) {
			*FIO0CLR |= (1 << 22);
			delay(time);
		}
		time -= 8000;
	}
	return 0;
}

int delay(int time) {
	int i;
	for (i = 0; i < time; i++)
		return;
}

