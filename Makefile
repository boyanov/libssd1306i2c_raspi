# This Makefile file for the test program for the LIBSSD1306I2C library.

CC=gcc
CFLAGS=-c -Wall
LIBS=-lwiringPi
OBJ_DIR=build
BIN_DIR=bin
OBJS=$(patsubst %, $(OBJ_DIR)/%, \
	libssd1306i2c.o \
	libssd1306i2c6x8.o \
	libssd1306i2c8x16.o \
)
EXECUTABLES=$(patsubst %, $(BIN_DIR)/%, \
	libssd1306i2c_demo1 \
	libssd1306i2c_test1 \
	libssd1306i2c_test2 \
	libssd1306i2c_chart1 \
	libssd1306i2c_printxy1 \
	oledprintxy \
)

all: directories $(EXECUTABLES)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLES): $(BIN_DIR)/%: $(OBJ_DIR)/$(notdir /%).o $(OBJS)
	$(CC) $< $(OBJS) $(LIBS) -o $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
