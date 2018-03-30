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

	// ---- Clear the screen ----
	ssd1306i2c_fill(0xff);
	delay(400);

	// ---- Print some small text on the screen ----
	ssd1306i2c_setpos(0, 0);
	for (int i = 0; i <= 20; i++) ssd1306i2c_char_font6x8('A' + i);
	ssd1306i2c_setpos(0, 1);
	ssd1306i2c_string_font6x8("This is a testing app");
	
	// ---- Print some large and small text on the screen ----
	ssd1306i2c_string_font8x16xy(12, 2, "LibSSD1306i2c");
	ssd1306i2c_setpos(0, 4);
	ssd1306i2c_string_font6x8("library for I2C/OLEDs");
	
	// ---- More text on the screen ----
	ssd1306i2c_setpos(0, 5);
	ssd1306i2c_string_font6x8("host:");
	ssd1306i2c_setpos(36, 5);
	char *host = "localhost";
	ssd1306i2c_string_font6x8(host);
	ssd1306i2c_setpos(0, 6);
	ssd1306i2c_string_font6x8("ip:");
	ssd1306i2c_setpos(36, 6);
	uint32_t ip = 0x6a7b8c9d;
	char ip_sb[16];
	sprintf(ip_sb, "%d.%d.%d.%d", (ip>>24 & 0xff), (ip>>16 & 0xff), (ip>>8 & 0xff), (ip & 0xff));
	ssd1306i2c_string_font6x8(ip_sb);
	ssd1306i2c_setpos(0, 7);
	ssd1306i2c_string_font6x8("val3:");
	ssd1306i2c_setpos(36, 7);
	float v3 = 123.456789;
	char v3_sb[16];
	sprintf(v3_sb, "%09.4f", v3);
	ssd1306i2c_string_font6x8(v3_sb);
	ssd1306i2c_string_font6x8(" xps/m");

	return 0;
}
