/*
===============================================================================
 Name        : blink_casero.c
 Author      : Di Lorenzo Franco, Del Boca Juan
 Version     :
 Description : Trabajo 1
===============================================================================
*/

#define gpi0 (0x2009C000)
#define led 22
#define fioset (0x2009C018)
#define fioclr (0x2009C01C)


int main(void) {
	unsigned int volatile *p= (unsigned int *)gpi0;


    int i;
    *p |= (1<<led);

    while(1) {
    	p =(unsigned int *) fioclr;
        *p |=(1<<led);

        for(i=0;i<10000000;i++)
        {

        }
        p=(unsigned int *) fioset;
		*p|=(1<<led);
        for(i=0;i<10000000;i++)
        {

        }
    }
    return 0 ;
}

