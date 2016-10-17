/*
===============================================================================
 Name        : TPFinal.c
 Author      : Di Lorenzo Franco - Del Boca Juan
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "i2c.h"
#include <cr_section_macros.h>

// TODO: insert other include files here

void delay();

// TODO: insert other definitions and declarations here

int main(void) {

	I2CInit(I2CMASTER);

	I2CWriteLength= 1;
	I2CMasterBuffer[1]= 25;

	while(1){
		I2CMasterBuffer[0]= 14;
		I2CMasterBuffer[1]+=1;
		I2CEngine();
		delay();

	}

    return 0 ;
}


void delay(){
	for (int i=0; i<3000000; i++);
}


