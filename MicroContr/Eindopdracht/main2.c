#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int place = 0;
int rotations = 0;

typedef struct {
	unsigned char data;
} PATTERN_STRUCT;
PATTERN_STRUCT liftup[] = {
	  {0b00000000}
	, {0b10011100}
	, {0b10110110}
	, {0b10100010}
	, {0b10100010}
	, {0b10100010}
	, {0b10110110}
	, {0b10011100} // END 0
		
	, {0b10000000}
	, {0b10000000}

	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100} // END PIJL 1
	, {0b10000000}	
		
	, {0b10000000}
	, {0b10000000} // Extra trans

	, {0b10000000}
	, {0b10001000}
	, {0b10001100}
	, {0b10001010}
	, {0b10001000}
	, {0b10001000}
	, {0b10001000}
	, {0b10111110} // END 1.
		
	, {0b10000000}
	, {0b10000000}
		
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b00000000}
		
	, {0b10000000}
	, {0b10000000}
		
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10010000}
	, {0b10001000}
	, {0b10000100}
	, {0b10111110}
	, {0b10000000}
		
	, {0b10000000}	
	, {0b10000000}
		
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b10000000}
		
	, {0b10000000}
	, {0b10000000}	
		
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10011000}
	, {0b10100000}
	, {0b10100010}
	, {0b10011100}
	, {0b10000000}
};

PATTERN_STRUCT happySmiley[] = {30, 33, 210, 192, 210, 204, 33, 30};
PATTERN_STRUCT neutralSmiley[] = {{30} , {33}  , {210}  , {192}  , {222}  , {192}  , {33} , {30}};
PATTERN_STRUCT madSmiley[] = {{30} 	, {33}	, {210}	, {192}	, {204}	, {210}	, {33}	, {30}};

void displayStruct(PATTERN_STRUCT str[]){
	
	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(str[adres/2].data);	// data
		twi_stop();
	}
}

void run(){

	int num = PINA;
	
	switch (num){
		case 1: Liftup(place + 20); break;
		case 2: Liftdown(place - 20); break;
		case 4: clearmatrix(); break;
		case 8: displayStruct(happySmiley); break;
		case 16: displayStruct(madSmiley); break;
		case 32: rotations = rotations == 1? rotations = 0:1; break;
	}
}

PATTERN_STRUCT currentPattern[] = {0,0,0,0,0,0,0,0};

PATTERN_STRUCT rotated[] = { 0,0,0,0,0,0,0,0};

void rotate ()
{
	rotations = rotations % 4;
	
	if (rotations == 0)
		memcpy(rotated , currentPattern, sizeof(currentPattern));
	
	for (int currentRotation = 0; currentRotation < rotations; currentRotation++){ 
		setRotatedPattern(0,0,0,0,0,0,0,0);
		DDRC = 0xFF;
		PORTC = currentRotation;
		int i, j, val;
 
		// Lekker draaien
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				// i,j = 0
				val = (currentPattern[i].data >> j) & 1;
				rotated[7-j].data |= (val << i);
			}
		}
		
		setCurrentPattern(rotated[0].data, rotated[1].data, rotated[2].data, rotated[3].data, rotated[4].data, rotated[5].data, rotated[6].data, rotated[7].data);
		
	}

}

void setCurrentPattern(int a, int b, int c, int d, int e, int f, int g, int h){
	currentPattern[0].data = a;
	currentPattern[1].data = b;
	currentPattern[2].data = c;
	currentPattern[3].data = d;
	currentPattern[4].data = e;
	currentPattern[5].data = f;
	currentPattern[6].data = g;
	currentPattern[7].data = h;
	
}

void setRotatedPattern(int a, int b, int c, int d, int e, int f, int g, int h){
	rotated[0].data = a;
	rotated[1].data = b;
	rotated[2].data = c;
	rotated[3].data = d;
	rotated[4].data = e;
	rotated[5].data = f; 
	rotated[6].data = g;
	rotated[7].data = h;
	
}

void LiftStart(void){
	setCurrentPattern(liftup[place].data, liftup[place + 1].data, liftup[place + 2].data, liftup[place + 3].data,
									liftup[place + 4].data, liftup[place + 5].data, liftup[place + 6].data, liftup[place + 7].data );

	rotate();
			
	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(rotated[adres/2].data);	// data
		twi_stop();
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
	
	if (place > 59)
		return; 
			
	for (place; place <= desti; place++){
		setCurrentPattern(	liftup[place].data, liftup[place + 1].data, liftup[place + 2].data, liftup[place + 3].data,
							liftup[place + 4].data, liftup[place + 5].data, liftup[place + 6].data, liftup[place + 7].data );
		rotate();
		
		for (int adres = 0; adres <= 14; adres += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(adres);	// Address
			twi_tx(rotated[adres/2].data);	// data
			twi_stop();
		}
		
		wait(1250);
	}
	
	place--;
	

}

void Liftdown(int desti){
	if (place < 19)
		return;
	
	
	
	for (place; place >= desti; place--){
		setCurrentPattern(	liftup[place].data, liftup[place + 1].data, liftup[place + 2].data, liftup[place + 3].data,
							liftup[place + 4].data, liftup[place + 5].data, liftup[place + 6].data, liftup[place + 7].data );
		rotate();
		
		for (int adres = 0; adres <= 14; adres += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(adres);	// Address
			twi_tx(rotated[adres/2].data);	// data
			twi_stop();
		}
		
		wait(1250);
	}
	
	place++;

	
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
		run();
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

