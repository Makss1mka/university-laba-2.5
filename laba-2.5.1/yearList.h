#include "model.h"

int** correctYearList(int** yearList, int len);
void yearListSort(int** yearList, int len);

// FROM TREE
int** addModelData(treeElem* node, int** yearList, int* yearListLen);
int** getYearListFromTree(treeElem* top, int* yearListLen);
void makeYearListFromTree(treeElem* top);
