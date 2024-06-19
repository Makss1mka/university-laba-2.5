#include <stdlib.h>
#include "model.h"

char* normalFscanf(FILE* file);
model* getOneModelEntry(FILE* file);

// FOR TABLE
table* getAllInTable(char* fileName);

// SAVINGS
void writeEntry(FILE* file, model* currentModel);
void tableSave(table* table, char* filePath);
