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

// FROM TABLE
int** getYearListFromTable(table* table, int* yearListLen) {
	int** yearList = NULL;
	char isFirst = 1;
    
	int ind = -1;
	for (int i = 0; i < table->len; i++) {
		for (int j = 0; j < table->modelList[i].len; j++) {
			for (int k = 0; k < table->modelList[i].list[j]->ammountOfComps; k++) {
				if (isFirst == 1) {
					yearList = mallocWithoutNull(sizeof(int*) * (1));
					yearList[0] = mallocWithoutNull(sizeof(int) * 3);
				
					yearList[0][0] = table->modelList[i].list[j]->comp[k].issueDate;
					yearList[0][1] = table->modelList[i].list[j]->comp[k].engCap;
					yearList[(*yearListLen)++][2] = 1;

					isFirst = 0;
					continue;
				}
				
				ind = in(table->modelList[i].list[j]->comp[k].issueDate, yearList, *yearListLen);
				if (ind != -1) {
					yearList[ind][1] += table->modelList[i].list[j]->comp[k].engCap;
					yearList[ind][2]++;
					continue;
				}
				
				yearList = reallocWithoutNull(yearList, sizeof(int*) * (1 + *yearListLen));
				yearList[*yearListLen] = mallocWithoutNull(sizeof(int) * 3);
				
				yearList[*yearListLen][0] = table->modelList[i].list[j]->comp[k].issueDate;
				yearList[*yearListLen][1] = table->modelList[i].list[j]->comp[k].engCap;
				yearList[(*yearListLen)++][2] = 1;
			}
		}
	}

	return correctYearList(yearList, *yearListLen);
}

void makeYearListFromTable(table* table) {
	if (table == NULL || table->len == 0) {
        printf("\n\tCurrent model tree is empty.\n");
        return;
    }
	
	int yearListLen = 0;
	int** yearList = getYearListFromTable(table, &yearListLen);
	
	matrixPrint(yearList, yearListLen, 2, "\n\tYear list before sorting:");
    yearListSort(yearList, yearListLen);
	matrixPrint(yearList, yearListLen, 2, "\n\tYear list after sorting:");
	printf("\n");
}


