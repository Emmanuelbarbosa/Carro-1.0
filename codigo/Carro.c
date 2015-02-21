/*
Projeto carro :1.0 com 4051 + adc0832 + joystick + L293D +MCU8051ide
OBS: sem uso do uRTOS
*/

#include<8051.h>
#define clock P3_4
#define cs P3_7
#define data_io P3_5

void atraso(){				//Atraso de 6 microsegundos
	TMOD = 3;
	TR0  = 0;
	TL0  = 0xFA;
	TR0  = 1;
	while(TF0==0){}
	TF0=0; 
}

void pulso(){				//Pulso de clock
	clock = 1;
	atraso();
	clock = 0;
	atraso();
}

void leitor_x(){			//Leitor da entrada x
unsigned char valor=0,cont=0;
	cs = 0;
	data_io = 1;
	pulso();
	pulso();
	pulso();

	for(cont=0; cont<8; cont++){
	pulso();
	}
	atraso();
	for(cont=0; cont<8; cont++){
	valor >>= 1;
		if(data_io) valor |= 0b10000000;
		pulso();
		}
			if(valor<100){
			P1_3 = 1;
			valor = 0;
			}
			else if(valor>200){
			P1_2 = 1;
			valor =0;
			}
			else if(valor>=100 & valor<=200){
			P1_2 = 0;
			P1_3 = 0;
			valor = 0;
			}
		cs =1;
}

void leitor_y(){			//Leitor da entrada y
unsigned char valor=0,cont=0;
	P1_5 = 1;
	P1_7 = 1;
	cs = 0;
	data_io = 1;
	pulso();
	pulso();
	data_io = 0;
	pulso();

	data_io = 1;
	for(cont=0; cont<8; cont++){
	pulso();
	}
	atraso();
	for(cont=0; cont<8; cont++){
	valor >>= 1;
		if(data_io) valor |= 0b10000000;
		pulso();
		}
			if(valor<100){
			P1_4 = 1;
			valor = 0;
			}
			else if(valor>200){
			P1_6 = 1;
			valor =0;
			}
			else if(valor>=100 & valor<=200){
			P1_4 = 0;
			P1_6 = 0;
			valor = 0;
			}
	
		cs =1;
}

void main(){

	P1_7 = 0;
	P1_5 = 0;
	data_io = 0;
	clock = 0;
	
	while(1){
	leitor_x();

	leitor_y();

		}
}