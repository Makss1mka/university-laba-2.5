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

typedef struct Bucket {

    int len;
    model** list;

} bucket;

typedef struct HashTable {

    bucket* modelList;
    int len;
    int ammountOfModels;

} table;

// PRINTING
void printModel(model* currentModel, char* offset);
char* getFrameStr(int frameNum);

// CREATING
model* createModel();

// FREE
void modelFree(model* currentModel);

int getModelTimePeriod(model* currentModel);
