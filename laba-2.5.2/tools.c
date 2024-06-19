#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MEMORY
void* mallocWithoutNull(unsigned size) {
	void* returnArr = NULL;
	int count = 0;

	while (1) {
		returnArr = malloc(size);
		if (returnArr != NULL) return returnArr;

		count++;
		if (count > 50) {
			printf("\n\n\tMalloc cycle error");
			exit(-1);
		}
	}
}

void* reallocWithoutNull(void* inputPtr, unsigned newSize) {
	int count = 0;

	while (1) {
		inputPtr = realloc(inputPtr, newSize);
		if (inputPtr != NULL) return inputPtr;

		count++;
		if (count > 50) {
			printf("\n\n\tRealloc cycle error");
			exit(-1);
		}
	}
	return NULL;
}

// NUMBER SCANS
int intScanWithLimitCheck(int min, int max) {
	int num;

	while (scanf_s("%d", &num) == 0 || getchar() != '\n'
		|| num < min || num > max) {
		printf("\n\tIncorrect input, make another input - ");
		rewind(stdin);
	}

	return num;
}

// FILE
void* fileOpener(void* filePath, void* mode) {
	FILE* file = NULL;
	file = fopen(filePath, mode);

	if (file == NULL) {
		printf("\n\tFailed access to the file\n");
		exit(1);
	}

	return file;
}

// STRINGS
char* strCorrection(char* str) {
	str[strlen(str) - 1] = '\0';

	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '\t' || str[i] == '\n') str[i] == ' ';
	}

	return str;
}

// MATRIX
void matrixPrint(int** matrix, int rows, int cols, char* message) {

	fputs(message, stdout);
	for (int row = 0; row < rows; row++) {
		printf("\n\t\t");
		for (int col = 0; col < cols; col++) {
			printf("\t%d", matrix[row][col]);
		}
	}

}

int in(int checkingValue, int** checkingArray, int arrayLength) {
	for (int i = 0; i < arrayLength; i++) {
		if (checkingValue == checkingArray[i][0]) return i;
	}

	return -1;
}

