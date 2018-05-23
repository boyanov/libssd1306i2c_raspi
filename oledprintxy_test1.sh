#!/bin/sh

BIN_DIR=bin

# Initialize the display, clear the screen and print the "hello world" text
${BIN_DIR}/oledprintxy -i -l "Hello, World!"
sleep 1

# Clear the screen and print 2 lines of text
${BIN_DIR}/oledprintxy -l "Hello, World!" "This is a test 123456"
sleep 1

# Print a horizontal "line" at specified row and column 0 of the screen
${BIN_DIR}/oledprintxy -r 2 "_-_-_-_-_-_-_-_-_-_-_"
sleep 1

# Print text at specified row/column position
${BIN_DIR}/oledprintxy -r 3 -c 3 "Text at r=3,c=3"
sleep 1

# Print text at specified x/y position
${BIN_DIR}/oledprintxy -x 12 -y 32 "Text at x=12,y=32"
sleep 1

# Print concatenated texts at specified x/y position
${BIN_DIR}/oledprintxy -x 0 -y 40 -k "Text fragments " "concatenated in one long string of text 123456789"
sleep 1

