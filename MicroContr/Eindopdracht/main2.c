#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

int place = 0;
// 0 = nothing, 1 = up, 2 = down
int lastScrollAction = 0;

typedef struct {
	unsigned char data;
} PATTERN_STRUCT;
PATTERN_STRUCT liftup[] = {
	//0
	{0b10011100}
	, {0b10110110}
	, {0b10100010}
	, {0b10100010}
	, {0b10100010}
	, {0b10110110}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//1
	, {0b10001000}
	, {0b10001100}
	, {0b10001010}
	, {0b10001000}
	, {0b10001000}
	, {0b10001000}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//2
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10010000}
	, {0b10001000}
	, {0b10000100}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//3
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10011000}
	, {0b10100000}
	, {0b10100010}
	, {0b10011100}


};
PATTERN_STRUCT liftdown[] = {
	//0
	{0b10011100}
	, {0b10110110}
	, {0b10100010}
	, {0b10100010}
	, {0b10100010}
	, {0b10110110}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b11111111}
	, {0b10111110}
	, {0b10011100}
	, {0b10001000}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//1
	, {0b10001000}
	, {0b10001100}
	, {0b10001010}
	, {0b10001000}
	, {0b10001000}
	, {0b10001000}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b11111111}
	, {0b10111110}
	, {0b10011100}
	, {0b10001000}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//2
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10010000}
	, {0b10001000}
	, {0b10000100}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b11111111}
	, {0b10111110}
	, {0b10011100}
	, {0b10001000}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//3
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10011000}
	, {0b10100000}
	, {0b10100010}
	, {0b10011100}


};
PATTERN_STRUCT smileys[] = {
	//smileyblij
	{30}, {33}, {210}, {192}, {210}, {204}, {33}, {30}
	//smiley neutraal
	, {30} , {33}  , {210}  , {192}  , {222}  , {192}  , {33} , {30}

	//smiley niet blij
	, {30} 	, {33}	, {210}	, {192}	, {204}	, {210}	, {33}	, {30}


};


void writeToMatrix(char data){

	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(smileys[adres/2].data);	// data
		twi_stop();
	}
}

void smileyHappy(void){
	writeToMatrix(smileys[0].data);

}
void smileyneut(void){
	writeToMatrix(smileys[8].data);


}
void smileyniet(void){
	writeToMatrix(smileys[16].data);

}


void buttoncheck(){

	int num = PINA;

	switch (num){
		case 1: Liftup(place + 17); break;
		case 2: Liftdown(place - 17); break;
		case 4: clearmatrix(); break;
		case 8: smileyHappy(); break;
		case 16: smileyneut(); break;
	}
}

void LiftStart(void){
	int x = 0;
	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(liftup[x].data);	// data
		twi_stop();
		x++;
	}
	
	
}

void clearmatrix(void){
	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(0);	// data
		twi_stop();
	}
}
void Liftup(int desti){
	PORTA = place; 
	if (place > 50)
		return;
		
	if (lastScrollAction == 2){
		place--;
	}
		
	
	for (place; place <= desti; place++)
	{
		int x = place;
		for (int adres = 0; adres <= 14; adres += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(adres);	// Address
			twi_tx(liftup[x].data);	// data
			twi_stop();
			x++;
		}
		wait(1250);
	}
	

		
	lastScrollAction = 1;
	

}

void Liftdown(int desti){
	if (place < 1)
		return;
		
	if (lastScrollAction == 1){
		place++;
	}
		
		
	for (place; place >= desti; place--)
	{
		int x=place;
		for (int adres = 0; adres <= 14; adres += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(adres);	// Address
			twi_tx(liftdown[x - 1].data);	// data
			twi_stop();
			x++;
		}
		wait(1250);
	}
	

	
	lastScrollAction = 2;
	
	
}



void initall(){
	twi_init();		// Init TWI interface

	// Init HT16K22.
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}

int main( void )
{
	DDRD = 0b11111111;
	DDRC = 0xFF;
	
	initall();
			
	LiftStart();
			
	while (1)
	{
		buttoncheck();
	}

	return 1;
}

void wait( int ms )
{
	for (int sms=0; sms<ms; sms++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void twi_init(void)
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void)
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void)
{
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data)
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

