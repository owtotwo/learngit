#include <stdio.h>
/* You can add any standard libraries in C if you want.*/

#define ROW_BYTE 16
#define LINE_HEAD_SIZE_DEFAULT 8

const char CONTROL_CHAR_DISPLAY = '.';

/* Your code here */


int main(int argc, char* argv[]) {
	
	if (argc < 2 || argc > 3) {
		printf("Usage: ./hex_viewer <file> [<num>]\n");
		return -1;
	}
	
	/* Your code here */

	return 0;
}
