#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))

void wait(int ms)
{
	for(int i=0; i<ms; i++){
		_delay_ms(1);
	}
}

int main(void){
	DDRD = 0xFF;
	
	PORTD = 0x40; // 0100 0000
	
	while (1){
		wait(100);
		// XOR -> 0100 0000 ^ 1000 0000 = 1100 0000 (oneven x-te cycle)
		// XOR -> 1000 0000 ^ 1000 0000 = 0000 0000 (even x-te cycle)
		PORTD ^= BIT(7);
		// XOR -> 1100 0000 ^ 0100 0000 = 1000 0000
		// XOR -> 0000 0000 ^ 0100 0000 = 0100 0000
		PORTD ^= BIT(6);
	}
}
