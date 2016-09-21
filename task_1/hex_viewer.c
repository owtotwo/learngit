#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	if (argc < 2) {
		printf("Usage: ./hex_viewer [file]\n");
		exit(1);
	}
	
	FILE* fp = fopen(argv[1], "rb");
	if (!fp) {
		printf("Cannot open the file %s.\n", argv[1]);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buffer = (char*)malloc(length);
	if (!buffer) exit(EXIT_FAILURE);
	fread(buffer, sizeof(char), length, fp);

	for (int i = 0; i < length; i++) {
		if (i % 16 == 0) printf("%08x| ", i);
		printf("%02x ", (unsigned char)buffer[i]);
		if (i % 16 == 15) putchar('\n');
	}
	putchar('\n');
	
	free(buffer);
	fclose(fp);

	return 0;
}
