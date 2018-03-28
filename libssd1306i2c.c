/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "libssd1306i2c.h"

/* -------------------------------------------------------------------------- */

static int ssd1306i2c_fd;

const uint8_t ssd1306i2c_init_sequence[] = {	// Initialization Sequence
	0xAE,			// Display OFF (sleep mode)
	0x20, 0b00,		// Set Memory Addressing Mode
					// 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
					// 10=Page Addressing Mode (RESET); 11=Invalid
	0xB0,			// Set Page Start Address for Page Addressing Mode, 0-7
	0xC8,			// Set COM Output Scan Direction
	0x00,			// ---set low column address
	0x10,			// ---set high column address
	0x40,			// --set start line address
	0x81, 0x3F,		// Set contrast control register
	0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
	0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xA8, 0x3F,		// Set multiplex ratio(1 to 64)
	0xA4,			// Output RAM to Display
					// 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0xD5,			// --set display clock divide ratio/oscillator frequency
	0xF0,			// --set divide ratio
	0xD9, 0x22,		// Set pre-charge period
	0xDA, 0x12,		// Set com pins hardware configuration
	0xDB,			// --set vcomh
	0x20,			// 0x20,0.77xVcc
	0x8D, 0x14,		// Set DC-DC enable
	0xAF			// Display ON in normal mode

};

/* -------------------------------------------------------------------------- */

int ssd1306i2c_init(uint8_t address) {
	ssd1306i2c_fd = wiringPiI2CSetup(address);
	if (ssd1306i2c_fd == -1) return ssd1306i2c_fd;
	for (uint8_t i = 0; i < sizeof (ssd1306i2c_init_sequence); i++) {
		wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x00, ssd1306i2c_init_sequence[i]);
	}
	return ssd1306i2c_fd;
}

/* -------------------------------------------------------------------------- */

void ssd1306i2c_pos(uint8_t x, uint8_t y) {
	wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x00, 0xb0 + y);
	wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x00, (x >> 4) | 0x10); // | 0x10
	wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x00, (x & 0x0f)); // | 0x01
}

void ssd1306i2c_fill4(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
	ssd1306i2c_pos(0, 0);
	for (uint16_t i = 0; i < 128 * 8 / 4; i++) {
		wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, p1);
		wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, p2);
		wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, p3);
		wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, p4);
	}
}

void ssd1306i2c_fill2(uint8_t p1, uint8_t p2) {
	ssd1306i2c_fill4(p1, p2, p1, p2);
}

void ssd1306i2c_fill(uint8_t p) {
	ssd1306i2c_fill4(p, p, p, p);
}

/* -------------------------------------------------------------------------- */

void ssd1306i2c_char_font6x8(char c) {
	uint8_t b = c - 32;
	uint8_t *font6x8 = ssd1306i2c_font6x8;
	for (uint8_t i = 0; i < 6; i++) {
		wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, font6x8[b * 6 + i]);
	}
}

void ssd1306i2c_string_font6x8(char *s) {
	while (*s) {
		ssd1306i2c_char_font6x8(*s++);
	}
}

/* -------------------------------------------------------------------------- */

void ssd1306i2c_string_font8x16xy(uint8_t x, uint8_t y, const char s[]) {
	while (*s) {
		uint8_t c = (*s++) - 32; // Convert ASCII code to font data index.
		if (x > 120) {
			x = 0;
			y++;
		}
		ssd1306i2c_pos(x, y);
		for (uint8_t i = 0; i < 8; i++) {
			wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, ssd1306i2c_font8x16[c * 16 + i]);
		}
		ssd1306i2c_pos(x, y + 1);
		for (uint8_t i = 0; i < 8; i++) {
			wiringPiI2CWriteReg8(ssd1306i2c_fd, 0x40, ssd1306i2c_font8x16[c * 16 + i + 8]);
		}
		x += 8;
	}
}

/* --- EOF ------------------------------------------------------------------ */
