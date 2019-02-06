#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int digit = 0;
const unsigned char NUMBERS[16] = {
0b00111111, // 0
0b00000110, // 1
0b01011011, // 2
0b01001111, // 3
0b01100110, // 4
0b01101101, // 5
0b01111101, // 6
0b00000111, // 7
0b01111111, // 8
0b01101111, // 9
0b01110111,//A
0b01111100,//B
0b00111001,//C
0b01011110,//D
0b01111001,//E
0b01110001//F
};

void display(){
	if(digit >= 0 && digit <= 15){
		PORTD = NUMBERS[digit];
	} else {
		PORTD = NUMBERS[14];
	}
}

ISR(INT4_vect){
	digit++;
	display();
}

ISR(INT5_vect){
	digit--;
	display();
}

int main(void){
	
	DDRD = 0xFF;
	DDRE = 0x0;
	
	EICRB |= 0x0F;
	EIMSK |= 0x30;
	
	digit = 0;
	display();
	
	sei();
	
	while(1){
	}
	return 1;
}
