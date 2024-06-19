// NUMBER SCANS
int intScanWithLimitCheck(int min, int max);

// MEMORY
void* reallocWithoutNull(void* inputPtr, unsigned newSize);
void* mallocWithoutNull(unsigned size);

// FILE
void* fileOpener(void* filePath, void* mode);

// STRINGS
int strCompare(char* str1, char* str2);
int strCompareWithFree(char* str1, char* str2);
char* lower(char* str);
char* strCorrection(char* str);

//MATRIX
void matrixPrint(int** matrix, int rows, int cols, char* message);
int in(int checkingValue, int** checkingArray, int arrayLength);


