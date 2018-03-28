# This Makefile file for the libssd1306i2c_test test program for the libssd1306i2c library.

CC=gcc
CFLAGS=-c -Wall
LIBS=-lwiringPi

all: libssd1306i2c_test

libssd1306i2c_test: libssd1306i2c_test.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) libssd1306i2c_test.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o libssd1306i2c_test

libssd1306i2c_test.o: libssd1306i2c_test.c
	$(CC) $(CFLAGS) libssd1306i2c_test.c

libssd1306i2c.o: libssd1306i2c.c
	$(CC) $(CFLAGS) libssd1306i2c.c

libssd1306i2c6x8.o: libssd1306i2c6x8.c
	$(CC) $(CFLAGS) libssd1306i2c6x8.c

libssd1306i2c8x16.o: libssd1306i2c8x16.c
	$(CC) $(CFLAGS) libssd1306i2c8x16.c

clean:
	rm *.o libssd1306i2c_test

