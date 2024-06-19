#include "model.h"

int** correctYearList(int** yearList, int len);
void yearListSort(int** yearList, int len);

// FROM TABLE
int** getYearListFromTable(table* table, int* yearListLen);
void makeYearListFromTable(table* table);
