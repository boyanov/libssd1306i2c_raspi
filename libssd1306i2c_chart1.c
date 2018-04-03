/*
 * This is a testing program for the LibSSD1306i2c library.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

	// ---- Print some test chart data on the screen ----
	for (uint8_t val = 0; val <= 254; val += 7) {
		printf("val=0x%02X (%04i) ", val, val);
		ssd1306i2c_chart_val(val);
		ssd1306i2c_chart_shift();
		ssd1306i2c_chart_out(0);
	}

	// ---- Print some random chart data on the screen ----
	for (int16_t val = 127;;) {
		uint8_t rnd = rand() & 0x3f; /* random number */
		val += (32 - rnd);
		if (val > 255) val = 255;
		if (val < 0) val = 0;
		ssd1306i2c_chart_val(val);
		ssd1306i2c_chart_shift();
		ssd1306i2c_chart_out(0);
	}

	return 0;
}
