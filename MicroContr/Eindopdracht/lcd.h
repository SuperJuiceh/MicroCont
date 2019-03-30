/*
 * lcd.h
 *
 * Created: 23-2-2016 10:46:34
 *  Author: sander
 */ 
 #ifndef LCD_H_   
 #define LCD_H_

void init();
void display_text(char* str, int d);
void switchline();
void setcursor(int position);
void clear();
#endif