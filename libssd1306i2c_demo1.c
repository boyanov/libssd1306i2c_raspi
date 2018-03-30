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

	// ---- Init the library and the display ----
	if(ssd1306i2c_init(0x3c) == -1) {
		printf("E: Cannot setup the I2C device.\n");
		return -1;
	}
	printf("I: I2C device initialized.\n");

	// ---- Fill out screen with patters ----
	ssd1306i2c_fill(0xAA);
	delay(200);
	ssd1306i2c_fill2(0x55, 0xAA);
	delay(200);
	ssd1306i2c_fill4(0xCC, 0xCC, 0x33, 0x33);
	delay(400);
	ssd1306i2c_fill(0);

	// ---- Print some small text on the screen ----
	ssd1306i2c_setpos(0, 0);
	for (int i = 0; i <= 20; i++) ssd1306i2c_char_font6x8('A' + i);
	ssd1306i2c_setpos(0, 2);
	ssd1306i2c_string_font6x8("This is a testing app");

	// ---- Print some large and small text on the screen ----
	ssd1306i2c_string_font8x16xy(12, 4, "LibSSD1306i2c");
	ssd1306i2c_setpos(0, 6);
	ssd1306i2c_string_font6x8("library for I2C/OLEDs");

	return 0;
}
