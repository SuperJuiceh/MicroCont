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

int main (void)
{
	DDRC = 0x00;
	DDRD = 0xFF;
	
	int waitingtime;
	
	while(1){
		PORTD = 0x01;
		
		if (PINC & 1){
			waitingtime = 25;
		} else {
			waitingtime = 100;
		}
		
		wait(waitingtime);
		PORTD = 0;
		wait(waitingtime);
	}
	
	return 0;
	
}

