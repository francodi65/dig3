/*
===============================================================================
 Name        : blink.c
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

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {
    int i;
    LPC_GPIO0->FIODIR |= (1<<22);

    while(1) {
        LPC_GPIO0->FIOCLR=(1<<22);

        for(i=0;i<10000000;i++)
        {

        }
		LPC_GPIO0->FIOSET=(1<<22);
        for(i=0;i<10000000;i++)
        {

        }
    }
    return 0 ;
}
