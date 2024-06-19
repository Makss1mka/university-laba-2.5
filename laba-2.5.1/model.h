#pragma once
#include <stdio.h>

enum FrameType {

	micro = 0,
	sedan = 1,
	cupe = 2,
	crossover = 3,
    cabriolet = 4,
    picap = 5,
	track = 6,

};

typedef struct Complectation {

    int issueDate;
    int issueDateEnd;
    int engCap;
    enum FrameType frame;

} comp;

typedef struct Model {
    
    char* modelName;
    int ammountOfComps;
    comp* comp;
    int id;

} model;

typedef struct TreeElement {

    model* model;

    struct TreeElement* left;
    struct TreeElement* right;

} treeElem;

// PRINTING
void printModel(model* model, char* offset);
char* getFrameStr(int frameNum);

// CREATING
model* createModel();

// FREE
void modelFree(model* model);

