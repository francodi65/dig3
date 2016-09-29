.syntax unified
.data
.global EsperaEnAssembler
.type EsperaEnAssembler,function

	SUBS R1,R1,#1;
	BNE EsperaEnAssembler;
	LDR R2,#0x2009C018;
	ADDS R2,#0x400000;
	PUSH
EsperaEnAssembler:
	SUBS R0,R0,#1;
	BNE EsperaEnAssembler;
	MOV PC,LR;
.END
