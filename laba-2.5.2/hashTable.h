#include "model.h"

int getHash(int period, int percent);
table* tableInit(int len);
void addModelToTable(table* table, model* model);
void tablePrint(table* table);
void findModelByTimePeriod(table* table);

// DELETING
void deleteModelFromBucket(bucket* currentBucket, int ind);
void deleteByFrameType(table* table);

// void deleteByInd(table* table);

// FREE
table* tableFree(table* table);

// INDECATION
int indecation(table* table);
