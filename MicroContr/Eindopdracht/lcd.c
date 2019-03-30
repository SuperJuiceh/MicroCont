/*
 * lcd.c
 *
 * Created: 23-2-2016 10:46:20
 *  Author: sander
 */ 
 #include <avr/io.h>
#include <util/delay.h>
 #include "lcd.h"
int i =1;

 void init()
 {
 lcd_command( 0x02 );
 lcd_command( 0x28 ); 
 lcd_command( 0x0C );
 lcd_command( 0x06 );
 lcd_command( 0x80 );
 
 }
 
 void display_text(char* str, int d)
 {
	for (int i=0; i<= d; i++) 
	{
		lcd_writeChar(str[i]);
	}
	
 }
void switchline(){

	if (i == 0){
	_delay_ms(50);
	lcd_command(0x80);
	_delay_ms(50);
	i = 1;
	}
	else{
	_delay_ms(50);
	lcd_command(0xc0);
	_delay_ms(50);
	i = 0;
	}
}
 void setcursor(int position)
 {
	for (int i = 0; i <position;i++){
	 lcd_command(0b0000010100);
	}
 }
 void clear(){
 lcd_command(0x01);
 }
 void lcd_command ( unsigned char dat )
 {
	 PORTC = dat & 0xF0; 
	 PORTC = PORTC | 0x08; 
	 _delay_ms(50);
	 PORTC = 0x04; 
	 PORTC = (dat & 0x0F) << 4; 
	 PORTC = PORTC | 0x08;
	 _delay_ms(50); 
	 PORTC = 0x00; 
	 
 }
 void lcd_writeChar( unsigned char dat )
 {
	 
	 PORTC = dat & 0xF0; 
	 PORTC = PORTC | 0x0c; 
	 _delay_ms(50); 
	 PORTC = 0x04;

	 PORTC = (dat & 0x0F) << 4;
	 PORTC = PORTC | 0x0c;
	 _delay_ms(50); 
	 PORTC = 0x00; 
	 
 }