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
int strCompareWithFree(char* str1, char* str2) {
	int minLen = (strlen(str1) > strlen(str2)) ? strlen(str2) : strlen(str1);
	
	for(int i = 0; i < minLen; i++) {
		if (str1[i] == str2[i]) continue;
		if ((int)str1[i] > (int)str2[i]) return 1;
		return -1;
	}

	if (strlen(str1) == strlen(str2)) return 0;
	
	int res = (strlen(str1) > strlen(str2)) ? 1 : -1;

	// free(str1);
	// free(str2);
	// str1 = NULL, str2 = NULL;

	return res;
}

int strCompare(char* str1, char* str2) {
	int minLen = (strlen(str1) > strlen(str2)) ? strlen(str2) : strlen(str1);
	
	for(int i = 0; i < minLen; i++) {
		if (str1[i] == str2[i]) continue;
		if ((int)str1[i] > (int)str2[i]) return 1;
		return -1;
	}

	if (strlen(str1) == strlen(str2)) return 0;
	
	char res = (strlen(str1) > strlen(str2)) ? 1 : -1;

	return res;
}

char* lower(char* str) {
	char* temp = mallocWithoutNull(sizeof(char) * strlen(str));
	strcpy(temp, str);

	for(int i = 0; i < strlen(str); i++) {
		if (temp[i] >= 65 && temp[i] <= 90) temp[i] = (char)(((int)temp[i]) + 32);
	}
	
	return temp;
}

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

