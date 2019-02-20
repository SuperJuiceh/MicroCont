/*
 * main.c
 *
 * Created: 20-Feb-19 10:52:41 AM
 *  Author: Bilel
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void wait(int ms){
	for(int i = 0; i<=ms; i++){
		_delay_ms(1);
	}
}


int main(void){
	
		
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	ADMUX = 0b01100001;
	ADCSRA = 0b011100110;
	
	while (1){
		PORTB = ADCL;
		PORTA = ADCH;
		
		wait(100);
	}
}