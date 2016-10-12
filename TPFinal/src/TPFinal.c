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

// TODO: insert other definitions and declarations here

int main(void) {

    // TODO: insert code here
//	int status;
//	setupI2c();
//    status= startI2c();
//    if (status)
//    	return 0;
//    volatile static int i = 0 ;
//    // Enter an infinite loop, just incrementing a counter
//    while(i<5000) {
//    	puts(send('1'));
//        i++ ;
//    }

	I2CInit(I2CMASTER);
	void i2c_clearbuffers(void);
	I2CMasterBuffer[0]= 14;
	I2CMasterBuffer[1]= 14;
	I2CMasterBuffer[2]= 2;
	I2CMasterBuffer[3]= 3;
	I2CWriteLength= 4;

	while(1)
		I2CEngine();


    return 0 ;
}


