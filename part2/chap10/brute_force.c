#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 512

int bruteForce(char *text, int textSize, int start, char *pattern, int patternSize);

int bruteForce(char *text, int textSize, int start, char *pattern, int patternSize) {
	int i = 0;
	int j = 0;

	for (i = start; i <= (textSize - patternSize); i++) {
		for (j = 0; j < patternSize; j++) {
			if (text[i+j] != pattern[j]) {
				break;
			}
		}
		if (j >= patternSize) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	char *filePath;
	FILE *fp;

	char text[MAX_BUFFER];
	char *pattern;
	int patternSize = 0;
	int line = 0;

	if (argc < 3) {
		printf("wrong input\n");
		return 1;
	}

	filePath = argv[1];
	pattern = argv[2];

	patternSize = strlen(pattern);

	fp = fopen(filePath, "r");

	if (fp) {
		while (fgets(text, MAX_BUFFER, fp) != NULL) {
			int position = bruteForce(text, strlen(text), 0, pattern, patternSize);
			if (position >= 0) {
				printf("line:%d, colums:%d : %s\n", line++, position, text);
			}
		}
		fclose(fp);
	}

	return 0;
}