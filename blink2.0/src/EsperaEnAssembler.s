.syntax unified
.data
.global EsperaEnAssembler
.type EsperaEnAssembler,function

EsperaEnAssembler:
.equ FIO0DIR,      0x2009C000
.equ FIO0PIN,      0x2009C014
.equ FIO0SET,      0x2009C018
.equ FIO0CLR,      0x2009C01C
.equ PIN22,        0x400000;

	LDR R4,=FIO0SET				//Cargo las direcciones en los registros
	LDR R5,= FIO0CLR
	MOV R6,#PIN22				//Cargo en R6 un 1 en el bit 22(LED)
	MOV R2,#0					//Uso R2 como registro auxiliar para el loop
	ADD R2,R0					//Le cargo a R2 el retardo
	CMP R1,#0
	IT EQ						//Si el estado es 1, hago loop, sino vuelvo al main
	BEQ loop1
	MOV PC,LR


	loop1:						//Simple loop para prender y apagar el led
	SUBS R2,R2, #1
	BNE loop1
	STR R6,[R4]
	ADD R2,R0
	loop2:
	SUBS R2,R2, #1
	BNE loop2
	STR R6,[R5]
	MOV PC,LR

.END
