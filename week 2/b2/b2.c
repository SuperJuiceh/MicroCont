#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int current = 0;

void wait(int ms){
	for(int i = 0; i < ms; i++){
		_delay_ms(1);
	}
}

ISR(INT1_vect){
	if(current < 8){
		PORTE |= (1<<current);
		current++;
	}
}

ISR(INT2_vect){
	if(current > 0){
		PORTE &= ~(1<<current);
		current--;
	}
}

int main(void){
	DDRE = 0xFF;
	DDRD = 0x00;
	
	EICRA |= 0x28; //00101000
	EIMSK |= 0x06; //00000110
	//SREG = 0x80;
	sei();
	
	while(1){
		
	}
	return 0;
}
