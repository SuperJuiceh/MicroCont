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

int main(void){
	
	DDRD = 0b11111111;
	
	char counter;
	
	while (1){
		for (counter = 0; counter < 8; counter++){
			PORTD = BIT(counter);
			_delay_ms(50);
		}
	}
}

