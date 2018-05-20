/*
 * This is a testing program for the LibSSD1306i2c library.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "libssd1306i2c.h"

int main (int argc, char *argv[]) {

	// TODO: Add "-f" option for fill with a byte pattern
	// TODO: Add "-p" option for fill with a 2-byte pattern

	int i_flag = 0, l_flag = 0, k_flag = 0;
	char *c_opt, *r_opt, *x_opt, *y_opt;
	c_opt = r_opt = x_opt = y_opt = NULL;
	int oled_x = 0, oled_y = 0;
	int c;
	opterr = 0;
	while ((c = getopt (argc, argv, ":c:r:x:y:ilkh")) != -1) {
		switch (c) {
		case 'c':	// column
			c_opt = optarg;
			break;
		case 'r':	// row
			r_opt = optarg;
			break;
		case 'x':	// x
			x_opt = optarg;
			break;
		case 'y':	// y
			y_opt = optarg;
			break;
		case 'i':
			i_flag = 1;
			break;
		case 'l':
			l_flag = 1;
			break;
		case 'k':
			k_flag = 1;
			break;
		case 'h':	// Help
			printf("How to use this command: TBD.\n");
			exit(0);
			break;
		case ':':
			fprintf(stderr, "ERROR: Option \"-%c\" requires an argument.\n", optopt);
			fprintf(stderr, "INFO: optarg=\"%s\" optopt=\"%c\" optind=\"%i\"\n", optarg, optopt, optind);
			break;
		case '?':
			if (isprint (optopt)) {
				fprintf(stderr, "WARNING: Unknown option \"-%c\" (ignored).\n", optopt);
				fprintf(stderr, "INFO: optarg=\"%s\" optopt=\"%c\" optind=\"%i\"\n", optarg, optopt, optind);
			} else {
				fprintf(stderr, "WARNING: Unknown option character \"0x%X\" (ignored).\n", optopt);
				fprintf(stderr, "INFO: optarg=\"%s\" optopt=\"%c\" optind=\"%i\"\n", optarg, optopt, optind);
			}
			break;
		default:
			fprintf(stderr, "WARNING: Unknown state - optarg=\"%s\" optopt=\"%c\" optind=\"%i\"\n", optarg, optopt, optind);
			abort();
		}
	}

	if (x_opt != NULL) {
		oled_x = atoi(x_opt);
	} else 	if (c_opt != NULL) {
		oled_x = atoi(c_opt) * 6;
	} // ELSE use the default

	if (y_opt != NULL) {
		oled_y = atoi(y_opt) / 8;
	} else if (r_opt != NULL) {
		oled_y = atoi(r_opt);
	}

	// Debugging
	/*
	printf("args:\t" \
	       "c_opt=%s,r_opt=%s \t" \
	       "x_opt=%s,y_opt=%s \t" \
	       "oled_x=%i,oled_y=%i \t" \
	       "k_flag = %d, l_flag = %d, \t" \
	       "\n",
	       c_opt, r_opt,
	       x_opt, y_opt,
	       oled_x, oled_y,
	       k_flag, l_flag
	      );
	*/

	// Debugging
	/*
	printf ("The rest of the arguments:\n");
	for (int i = optind; i < argc; i++)
		printf ("[%02i]=%s\n", i, argv[i]);
	*/

	// ---- Init the library and the display ----
	wiringPiSetup();
	// NOTE: Use i2cdetect command to find your device address
	int init_result;
	if (i_flag)
		init_result = ssd1306i2c_init(0x3c);
	else
		init_result = ssd1306i2c_initq(0x3c);
	if(init_result == -1) {
		fprintf(stderr, "ERROR: Cannot setup the I2C device.\n");
		return -1;
	}

	if (l_flag) ssd1306i2c_clear();

	ssd1306i2c_setpos(oled_x, oled_y);
	for (int i = optind; i < argc; i++) {
		ssd1306i2c_string_font6x8(argv[i]);
		if (!k_flag) {
			oled_y++;
			ssd1306i2c_setpos(oled_x, oled_y);
		}
	}

	return 0;
}
