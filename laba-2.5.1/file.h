#include <stdlib.h>
#include "model.h"

char* normalFscanf(FILE* file);
model* getOneModelEntry(FILE* file);

// FOR TREE
treeElem* getAllinTree(char* fileName);

// SAVING
void saveTree(treeElem* top, char* filePath);
void saveNode(treeElem* node, FILE* file);
void writeEntry(FILE* file, model* model);
