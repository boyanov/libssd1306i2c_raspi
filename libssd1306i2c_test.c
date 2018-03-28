/*
 * This is a testing program for the LibSSD1306i2c library.
 *
 */

#include <stdio.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "libssd1306i2c.h"

int main (int argc, char *argv[]) {
	wiringPiSetup();
	/* Use i2cdetect command to find your device address */
	if(ssd1306i2c_init(0x3c) == -1) {
		printf("E: Cannot setup the I2C device.\n");
		return -1;
	}
	printf("I: I2C device initialized.\n");
	ssd1306i2c_clear();

	// ---- Fill out screen with patters ----
	ssd1306i2c_fill(0xAA);
	delay(400);
	ssd1306i2c_fill2(0x55, 0xAA);
	delay(400);
	ssd1306i2c_fill4(0xCC, 0xCC, 0x33, 0x33);
	delay(400);

	// ---- Print some small and large text on the screen ----
	ssd1306i2c_clear();
	ssd1306i2c_pos(0, 0);
	ssd1306i2c_string("This is demo for the");
	ssd1306i2c_string_font8x16xy(0, 1, " LibSSD1306i2c ");
	ssd1306i2c_pos(0, 3);
	ssd1306i2c_string("library for I2C/OLED");
	ssd1306i2c_pos(0, 4);
	for (int i = 0; i < 20; i++)
		ssd1306i2c_char('1' + i);
	ssd1306i2c_pos(0, 5);
	for (int i = 0; i < 20; i++)
		ssd1306i2c_char('A' + i);
	ssd1306i2c_pos(0, 6);
	for (int i = 0; i < 20; i++)
		ssd1306i2c_char('a' + i);
	ssd1306i2c_pos(0, 7);
	for (int i = 0; i < 20; i++)
		ssd1306i2c_char(' ' + i);
	delay(1000);
	// ssd1306i2c_clear();
	
	return 0;
}
