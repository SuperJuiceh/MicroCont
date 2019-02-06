#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

int currentNumber = 0;

ISR( INT4_vect )
{
	clearDisplay();
	currentNumber--;
	char c[15];
	sprintf(c, "%d", currentNumber);
	
	display_text(c, 1, 0);
	wait(100);
}

ISR( INT5_vect )
{
	clearDisplay();
	currentNumber++;
	char c[15];
	sprintf(c, "%d", currentNumber);
	
	display_text(c, 1, 0);
	wait(100);
}

int main(void)
{
	currentNumber = 0;
	DDRC = 0b11111111;					// PORTD all output
	DDRE = 0b00000000;					// PORTE all input
	
	EICRB |= 0b000001010;
	EIMSK |= 0b000110000;
	sei();

	init();

    while (1) 
    {
    }
}
