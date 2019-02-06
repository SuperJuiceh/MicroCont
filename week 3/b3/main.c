/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timer2init( void );

#define BIT(x) (1 << (x))

/*
typedef struct STUFF {
	{ 0x00, 0x01, 0x02, 0x04, 0x08 }
} STUFF;
*/

int msCount 	= 	0;
int seconden 	= 	0;
int minuten 	= 	0;
int uren    	= 	0;

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR (TIMER2_COMP_vect){
	msCount++;
	// Bij elke 50 hits een incrementie fixen
	if (msCount == 50){
		PORTC ^= BIT(0);
		msCount = 0;
		seconden++;
		
		if (seconden == 60){
			seconden = 0;
			minuten++;
			
			if (minuten == 60){
				minuten = 0;
				uren++;
			}
		}
	}
}

void timer2init(){
	OCR2 = 250;
	TIMSK |= BIT(7);
	SREG |= BIT(7);
	TCCR2 = 0b00001011;
}

int main( void ) { 
	DDRC = 0xFF;
	TCCR2 = 0b00001011;
	// set PORTC for output (toggle PC0) 
	timer2init(); 
	while (1) 
	{ 
		wait(10);
	} 
} 
