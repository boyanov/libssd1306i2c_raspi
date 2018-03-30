/* -------------------------------------------------------------------------- */

#ifndef _LIBSSD1306I2C_H
#define _LIBSSD1306I2C_H

/* -------------------------------------------------------------------------- */

#include <stdint.h>

// ----------------------------------------------------------------------------

#define ssd1306i2c_clear() ssd1306i2c_fill(0);
#define ssd1306i2c_pos(x, y) ssd1306i2c_setpos(x * 6, y);
#define ssd1306i2c_char(c) ssd1306i2c_char_font6x8(c)
#define ssd1306i2c_string(s) ssd1306i2c_string_font6x8(s)
#define ssd1306i2c_stringxy(x, y, s) ssd1306i2c_string_font8x16xy(x, y, s)

/* -------------------------------------------------------------------------- */

extern uint8_t ssd1306i2c_font6x8[];
extern uint8_t ssd1306i2c_font8x16[];

/* -------------------------------------------------------------------------- */

int ssd1306i2c_init(uint8_t address);

void ssd1306i2c_setpos(uint8_t, uint8_t);

void ssd1306i2c_fill4(uint8_t, uint8_t, uint8_t, uint8_t);
void ssd1306i2c_fill2(uint8_t, uint8_t);
void ssd1306i2c_fill(uint8_t);

void ssd1306i2c_char_font6x8(char);
void ssd1306i2c_string_font6x8(char *);
void ssd1306i2c_string_font8x16xy(uint8_t, uint8_t, const char[]);

#endif

/* --- EOF ------------------------------------------------------------------ */
