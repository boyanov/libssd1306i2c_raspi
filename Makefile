# This Makefile file for the test program for the LIBSSD1306I2C library.

CC=gcc
CFLAGS=-c -Wall
LIBS=-lwiringPi

all: libssd1306i2c_demo1 libssd1306i2c_test1 libssd1306i2c_test2 libssd1306i2c_chart1 libssd1306i2c_printxy1 oledprintxy

# libssd1306i2c_demo1

libssd1306i2c_demo1: libssd1306i2c_demo1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) libssd1306i2c_demo1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o libssd1306i2c_demo1

libssd1306i2c_demo1.o: libssd1306i2c_demo1.c
	$(CC) $(CFLAGS) libssd1306i2c_demo1.c

# libssd1306i2c_test1

libssd1306i2c_test1: libssd1306i2c_test1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) libssd1306i2c_test1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o libssd1306i2c_test1

libssd1306i2c_test1.o: libssd1306i2c_test1.c
	$(CC) $(CFLAGS) libssd1306i2c_test1.c

# libssd1306i2c_test2

libssd1306i2c_test2: libssd1306i2c_test2.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) libssd1306i2c_test2.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o libssd1306i2c_test2

libssd1306i2c_test2.o: libssd1306i2c_test2.c
	$(CC) $(CFLAGS) libssd1306i2c_test2.c

# libssd1306i2c_chart1

libssd1306i2c_chart1: libssd1306i2c_chart1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) libssd1306i2c_chart1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o libssd1306i2c_chart1

libssd1306i2c_chart1.o: libssd1306i2c_chart1.c
	$(CC) $(CFLAGS) libssd1306i2c_chart1.c

# libssd1306i2c_printxy1

libssd1306i2c_printxy1: libssd1306i2c_printxy1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) libssd1306i2c_printxy1.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o libssd1306i2c_printxy1

libssd1306i2c_printxy1.o: libssd1306i2c_printxy1.c
	$(CC) $(CFLAGS) libssd1306i2c_printxy1.c

# oledprintxy

oledprintxy: oledprintxy.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o
	$(CC) oledprintxy.o libssd1306i2c.o libssd1306i2c6x8.o libssd1306i2c8x16.o $(LIBS) -o oledprintxy

oledprintxy.o: oledprintxy.c
	$(CC) $(CFLAGS) oledprintxy.c

# Other library files

libssd1306i2c.o: libssd1306i2c.c
	$(CC) $(CFLAGS) libssd1306i2c.c

libssd1306i2c6x8.o: libssd1306i2c6x8.c
	$(CC) $(CFLAGS) libssd1306i2c6x8.c

libssd1306i2c8x16.o: libssd1306i2c8x16.c
	$(CC) $(CFLAGS) libssd1306i2c8x16.c

# Clean

clean:
	rm *.o libssd1306i2c_demo1 libssd1306i2c_test1 libssd1306i2c_test2 libssd1306i2c_chart1 libssd1306i2c_printxy1 oledprintxy

