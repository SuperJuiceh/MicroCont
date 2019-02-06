#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define BIT(x) (1 << (x))


void wait(int ms)
{
	while(ms > 0){
		_delay_ms(1);
		ms--;
	}
}

 typedef struct {
	unsigned char bits;
} STATE;

int main (void)
{
	// Patroon
	STATE bit_pattern[8] = { {BIT(0)}, {BIT(1)}, {BIT(2)}, {BIT(3)},
							  {BIT(4)}, {BIT(5)}, {BIT(6)}, {BIT(7)}};

	DDRD = 0b11111111;	
	
	while (1) {
		char counter = 8;

		while (counter > 0) {
			PORTD = bit_pattern[counter - 1].bits;
			counter--;
			wait(100);
		}
	}
}

