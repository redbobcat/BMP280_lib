/*
 * HD44780 TEST
 *
 *  Created on: 10.06.2017
 *      Author: red_bobcat
 */
#define set_bit(reg,bit) { reg |= 1 << bit; }
#define unset_bit(reg,bit) { reg &= ~(1 << bit);}
//#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "hd44780.h"
#include "BMP280/BMP280.h"
#include "i2c/i2cmaster.h"

void main(void)
{
	lcd_init();
	lcd_clrscr();
	
	lcd_puts("  Hello");
	lcd_goto(0x40);
	lcd_puts("RED_BOBCAT");
	_delay_ms(1000);
	lcd_clrscr();
	lcd_goto(0x00);
	unsigned char temp;
	unsigned char n, buffer[10];
	
	temp = bmp280_init();
	lcd_putc(temp+0x30);
	lcd_puts(" Init");
	bmp280_pres=664;
	bmp280_temp=664;
		
	for(;;)
	{
		bmp280_measure();
		lcd_clrscr();
		lcd_goto(0x00);
		ultoa(bmp280_temp, buffer, 10);
		for (n=0; n<8; n++)
		{
			if (buffer[n]=='\0') break;
			lcd_putc(buffer[n]);
		}
		lcd_putc('t');
		
		lcd_goto(0x40);
		ultoa(bmp280_pres, buffer, 10);
		for (n=0; n<8; n++)
		{
			if (buffer[n]=='\0') break;
			lcd_putc(buffer[n]);
		}
		lcd_putc('p');
		_delay_ms(300);
	}
	
}
