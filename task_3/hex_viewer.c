#include <stdio.h> // for fopen, ferror, fseek, feof
#include <assert.h>
#include <ctype.h> // for isprint
#include <stdlib.h> // for atoi

#define ROW_BYTE 16
#define LINE_HEAD_SIZE_DEFAULT 8

const char CONTROL_CHAR_DISPLAY = '.';
int line_head_size = 8;

// Considers fp has been opened successfully.
void print_file_stream_in_hex(FILE* fp) {
	assert(!ferror(fp));

	size_t pos = 0;
	char line[ROW_BYTE] = {0};

	for (pos = 0; !feof(fp); pos++) {
		if (pos % 16 == 0) printf("%0*x  ", line_head_size, (unsigned int)pos);
		
		char c = fgetc(fp);

		if (feof(fp)) {
			size_t extra_byte = pos % ROW_BYTE;
			// padding the last line by whitespace
			size_t padding_size = (ROW_BYTE - extra_byte) * 3;
			// add a whitespace for every 8 byte.
			padding_size += (((pos % 16) / 8) == 0 ? 2 : 1);
			for (int i = 0; i < extra_byte; i++) {
				if (i == 0) printf("%*s|", (unsigned int)padding_size, "");
				putchar(isprint(line[i]) ? line[i] : CONTROL_CHAR_DISPLAY);
				if (i == extra_byte - 1) printf("|\n");
			}
		} else {
			printf("%02x ", (unsigned char)c);
			// add a whitespace for every 8 byte.
			if (pos % 8 == 7) putchar(' ');
			// save the printable char
			line[pos % ROW_BYTE] = c;
			// line tail
			if (pos % 16 == 15) {
				// display the char
				for (int i = 0; i < ROW_BYTE; i++) {
					if (i == 0) printf("|");
					putchar(isprint(line[i]) ? line[i] : CONTROL_CHAR_DISPLAY);
					if (i == ROW_BYTE - 1) printf("|");
				}
				putchar('\n');
			}
		}
	}
	if (--pos % 16 != 0) printf("%0*x", line_head_size, (unsigned int)pos);
	putchar('\n');
}

int main(int argc, char* argv[]) {
	
	if (argc < 2 || argc > 3) {
		printf("Usage: ./hex_viewer [file]\n");
		return -1;
	}

	line_head_size = argc == 3 ? atoi(argv[2]) : LINE_HEAD_SIZE_DEFAULT;
	
	FILE* fp = fopen(argv[1], "rb");
	if (!fp) {
		printf("Cannot open the file %s.\n", argv[1]);
		return -1;
	}

	print_file_stream_in_hex(fp);

	fclose(fp);
	return 0;
}
