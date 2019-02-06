/*
 * Project name:
     Demo4_4 : PWM with timer 1 Fast PWM mode at PORTB.7 = OCR1A
 * Author: Avans-TI, JW
 * Revision History: 
     20101230: - initial release;
 * Description:
     This program gives an interrupt on each ms
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON the PORT LEDs at SW12.1 - SW12.8
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#define BIT(x)			(1 << (x))
#define INTERVAL  		2273

void setRed( int R );
void setGreen( int G );
void setBlue( int B);
void setColor( int A, int B, int C);

unsigned int sCount=0, minutes=0, hours=0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );				// library function (max 30 ms at 8MHz)
	}
}

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void timer1Init( void )
{
	ICR1 = INTERVAL;				// TOP value for counting = INTERVAL*us
	TCCR1A = 0b10101010;			// timer, compare output at OC1A=PB5
	TCCR1B = 0b00000001;			// PWM, Phase Control, 8 bit
}
// Methodes zodat we de intensiteit van 0-255 kunnen instellen.
void setRed( int R ){
	if (R < 256 && R > -1)
		OCR1A = R;
}
void setGreen( int G ){
	if (G < 256 && G > -1)
		OCR1B = G;
}
void setBlue( int B){
	if (B < 256 && B > -1)
		OCR1C = B;
}

void setColor( int R, int G, int B){
	setRed(R);
	setGreen(G);
	setBlue(B);
}




// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;					// set PORTB for compare output 
	DDRA = 0xFF;					// set PORTA for output in main program
	timer1Init();					// it is running now!!

	int rIntense, gIntense, bIntense;

	while (1)
	{
		// Fade up red
		for(intensity = 0; intensity < 255; intensity++){
			setRed(intensity);


			wait(4);
		}

		while (intensity > 0){
			setRed(intensity);
			intensity--;
			wait(4);
		}

		for(intensity = 0; intensity < 255; intensity++){
			setGreen(intensity);
			wait(4);
		}

		while (intensity > 0){
			setGreen(intensity);
			intensity--;
			wait(4);
		}

		for(intensity = 0; intensity < 255; intensity++){
			setBlue(intensity);
			wait(4);
		}

		while (intensity > 0){
			setBlue(intensity);
			intensity--;
			wait(4);
		}

		// do something else
		//setColor(255, 0, 255);
		wait(1000);					// every 100 ms (busy waiting)
		//setColor(0, 0, 0);
	}
}
