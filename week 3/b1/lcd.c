#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>
#include "lcd.h"


void wait(int ms){
	for(int i = 0; i<=ms; i++){
		_delay_ms(1);
	}
}

void lcd_command(unsigned char dat)
{
	PORTC = dat & 0XF0;     // top nibble
	PORTC = PORTC | 0x08;   // data (RS=0)
	// start (EN=1)
	_delay_ms(1);               // Wait 1 ms
	PORTC = 0x04;           // stop (EN=0)

	PORTC = (dat & 0x0F) << 4;  // Down nibble
	PORTC = PORTC | 0x08;       // data (RS=0)
	// start (EN=1)
	_delay_ms(1);                   // Wait 1 ms
	PORTC = 0x00;               // stop(EN=0, RS=0)
	              // wait 15 ms for command delay
}

void clearDisplay(){
	lcd_command(0x01);
}

void main(void){
	DDRC = 0xFF;
	PORTC = 0x00;
	_delay_ms(20);
	init();
	_delay_ms(10);
	char str[] = "Hallo iedereen\0";
	display_text(str, 1, 0);
}

void init(void){
	_delay_ms(1000);         // wait 300 ms for initialisation
	lcd_command( 0x02 );    // return home
	_delay_ms(15);
	lcd_command( 0x28 );    // set mode to: 4 bits interface data, 2 lines, 5x8 dots
	_delay_ms(15);
	lcd_command( 0x0E );    // display: on, cursor off, blinking off
	_delay_ms(15);
	lcd_command( 0x06 );    // entry mode: cursor to right, no shift
	_delay_ms(15);
	lcd_command( 0x80 );    // RAM address: 0, first position, line 1
	_delay_ms(100);         // wait 100 ms
	clearDisplay();
}

void toggleE(void){
	PORTC |= (1<<3);
	PORTC &= ~(1<<3);
}

void display_text(char str[], int row, int scroll){
	switch(scroll){
		default:
		case 0:
				display_text_noscroll(str, row);
				break;
		case 1:
				display_text_scroll(str, row);
				break;
	}
}

void display_text_scroll(char str[], int row){
	lcd_command(0x18);
	display_text_noscroll(str, row);
}

void display_text_noscroll(char str[], int row){
	int size = strlen(str);
	lcd_setLine(row);
	if(size > 16)
	{		
		
		for (int i = 0; i < 16; i++)
		{
			lcd_writeChar((unsigned char)str[i]);
		}
		
		lcd_setLine(row++);
		for (int i = 16; i < strlen(str); i++)
		{
			lcd_writeChar((unsigned char)str[i]);
		}
	}
	else
	{
		char c;		
		for(int i=0; i<strlen(str); i++){
			lcd_writeChar(str[i]);
		}
	}
}

void lcd_setLine(int row){
	switch (row)
	{
		case 1: 
			lcd_command(0x80);      // Position on row 1 col 1
			break;
		case 2: 
			lcd_command(0xC0);      // Position on row 2 col 1
			break;
		default: 
			lcd_command(0x80);	// Position on row 1 col 1
			break;
	}	   
}

// Write a single char to LCD
void lcd_writeChar(unsigned char dat )
{
	PORTC = dat & 0XF0;     // top nibble
	PORTC = PORTC | 0x0C;   // data (RS=1)
	// start (EN=1)
	_delay_ms(1);               // Wait 1 ms
	PORTC = 0x04;           // stop (EN=0)

	PORTC = (dat & 0x0F) << 4;  // Down nibble
	PORTC = PORTC | 0x0C;       // data (RS=1)
	// start (EN=1)
	_delay_ms(1);                   // Wait 1 ms
	PORTC = 0x00;               // stop(EN=0, RS=0)
	_delay_ms(15);              // wait 15 ms for command delay
}
