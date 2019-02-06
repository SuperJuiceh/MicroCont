#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef struct{
	unsigned char data;
	unsigned int delay;
}PATTERN_STRUCT;

PATTERN_STRUCT PATTERN[] = {
	{0b01010110, 100}, {0b01001000, 100}, {0b00000001, 100}, {0b11111111, 100}, {0b01011110, 100}, {0b01010100, 100}
};

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void){
	DDRD = 0xFF;
	int index = 0;
	while(1){
		if(index > sizeof(PATTERN)){
			index = 0;
		} else{
			index++;
		}
		PORTD = PATTERN[index].data;
		wait(PATTERN[index].delay);
	}
	return 1;
}
