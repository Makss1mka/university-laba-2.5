#include "model.h"

treeElem* getNextNode(treeElem* node, int dir);

// PRINTING
void treePrint(treeElem* top);
void nodePrint(treeElem* node);

// ADDING
treeElem* addModelToTree(treeElem* top, model* model);

// FIND
model* find(char* name, treeElem* top);
void findByName(treeElem* top);

// FREE
void freeNode(treeElem* node);
void freeNodeData(treeElem* node);
treeElem* freeTree(treeElem* top);

// DELETING
treeElem* delete(treeElem* node);
treeElem* copySubTree(treeElem* node, treeElem* subTree);
treeElem* checkAndDelete(treeElem* node, int frame);
treeElem* deleteByFrameFromTree(treeElem* top);

treeElem* deleteByIndInTree(treeElem* top, int ammountOfModels);
treeElem* findAndDelete(treeElem* node, int ind);

// INDECATION
int indecation(treeElem* top);
int indecateNode(treeElem* node, int *curInd);
