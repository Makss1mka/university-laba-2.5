#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "tools.h"

// CORRECTION
int** correctYearList(int** yearList, int len) {
	for (int i = 0; i < len; i++) {
		yearList[i][1] /= yearList[i][2];

		yearList[i] = reallocWithoutNull(yearList[i], sizeof(int) * 2);
	}

	return yearList;
}

// SORT
void yearListSort(int** yearList, int len) {
	int* temp;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - 1; j++) {
			if (yearList[j][1] < yearList[j + 1][1]) {
				temp = yearList[j];
				yearList[j] = yearList[j + 1];
				yearList[j + 1] = temp;
			}
		}
	}
}

// FROM TREE
int** addModelData(treeElem* node, int** yearList, int* yearListLen) {
    if (node == NULL) return yearList;
   
    int ind = -1;
    for (int i = 0; i < node->model->ammountOfComps; i++) {
        if (ind = in(node->model->comp[i].issueDate, yearList, *yearListLen) != -1) {
            yearList[ind][1] += node->model->comp[i].engCap;
            yearList[ind][2]++;
            continue;
        }
        
        yearList = reallocWithoutNull(yearList, sizeof(int*) * (1 + *yearListLen));
		yearList[*yearListLen] = mallocWithoutNull(sizeof(int) * 3);

		yearList[*yearListLen][0] = node->model->comp[i].issueDate;
		yearList[*yearListLen][1] = node->model->comp[i].engCap;
		yearList[(*yearListLen)++][2] = 1;
    }
    
    yearList = addModelData(node->left, yearList, yearListLen);
    yearList = addModelData(node->right, yearList, yearListLen);
	
	return yearList;
}

int** getYearListFromTree(treeElem* top, int* yearListLen) {
	int** yearList = mallocWithoutNull(0);
    
	yearList = addModelData(top, yearList, yearListLen);
	
	return correctYearList(yearList, *yearListLen);
}

void makeYearListFromTree(treeElem* top) {
    if (top == NULL) {
        printf("\n\tCurrent model tree is empty.\n");
        return;
    }
    
	int yearListLen = 0;
	int** yearList = getYearListFromTree(top, &yearListLen);
    
	matrixPrint(yearList, yearListLen, 2, "\n\tYear list before sorting:");
    yearListSort(yearList, yearListLen);
	matrixPrint(yearList, yearListLen, 2, "\n\tYear list after sorting:");
	printf("\n");
}

