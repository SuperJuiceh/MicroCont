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

int main (void)
{
	DDRD = 0b11111111;
	
	while (1)
	{
		PORTD = 0b1000000;
		wait(500);
		PORTD = 0b0100000;
		wait(500);
	}
	return 1;
}
