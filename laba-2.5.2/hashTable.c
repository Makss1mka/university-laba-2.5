#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "tools.h"

table* tableInit(int len) {
    table* hashTable = NULL;
    hashTable = mallocWithoutNull(sizeof(table));
    
    hashTable->len = len;
    hashTable->ammountOfModels = 0;
    hashTable->modelList = mallocWithoutNull(sizeof(bucket) * len);
    
    for (int i = 0; i < hashTable->len; i++) {
        hashTable->modelList[i].len = 0;
        hashTable->modelList[i].list = NULL;
    }
    
    return hashTable;
}

int getHash(int period, int percent) {
    int hash = 666;

    for (int i = 0; i < period + 16; i += 3) {
        for (int j = i % 5; j < period + i + 6; j++) {
            if (i % 2 == 0 && j % 2 == 0) hash += i * j * period;
            if (i % 2 != 0 && j % 2 == 0) hash -= i * 8 - j * 2;
            if (i % 2 == 0 && j % 2 != 0) hash += i * 3;
            if (i % 3 == 0 && j % 3 != 0) hash -= i * 7 * period;
            if (i % 3 != 0 && j % 3 == 0) hash -= j * 3 + period;
        }
    }
    
    if (hash < 0) hash *= -1;

    return hash % percent;
}

void addModelToTable(table* table, model* currentModel) {
    int hash = getHash(getModelTimePeriod(currentModel), table->len);
    
    if (table->modelList[hash].list == NULL || table->modelList[hash].len == 0) {
        table->modelList[hash].list = (model**)mallocWithoutNull(sizeof(model*) * 1);
        table->modelList[hash].list[0] = currentModel;
        table->modelList[hash].len++;
    } else {
        table->modelList[hash].list = realloc(table->modelList[hash].list, sizeof(model*) * (table->modelList[hash].len + 1));
        table->modelList[hash].list[table->modelList[hash].len++] = currentModel;
    }
}

void tablePrint(table* table) {
    if (table == NULL) {
        printf("\n\tCurrent model hash table is free.\n");
        return;
    }
    printf("\n\tCurrent models:");
    for (int i = 0; i < table->len; i++) {
        printf("\n\t\t%d-th socket:", i);
        for (int j = 0; j < table->modelList[i].len; j++) {
            printModel(table->modelList[i].list[j], "\t\t");
        }
    }
    printf("\n");
}

void findModelByTimePeriod(table* table) {
    if (table == NULL || table->len == 0) {
        printf("\n\tCurrent model table is empty.\n");
    }

    printf("\n\tInput the time period - ");
    int timePeriod = intScanWithLimitCheck(0, 300);
    int hashedPeriod = getHash(timePeriod, table->len);

    printf("\n\tFind models: \n");

    for(int i = 0; i < table->modelList[hashedPeriod].len; i++) {
        if (getModelTimePeriod(table->modelList[hashedPeriod].list[i]) == timePeriod) {
            printModel(table->modelList[hashedPeriod].list[i], "\t");
        }
    }

    printf("\n");
}

// DELETING
void deleteByFrameType(table* table) {
    if (table == NULL || table->len == 0) {
		printf("\n\tOperation canceled. Model table is empty.\n");
		return;
	}

    printf("\n\tInput the frame type (0-micro, 1-sedan, 2-cupe, 3-crossover, 4-cabriolet, 5-picap, 6-track) - ");
	int frameType = intScanWithLimitCheck(0, 6);
    int isNonDeletble = 0;

    for(int i = 0; i < table->len; i++) {
        for (int j = 0; j < table->modelList[i].len; j++) {
            for(int k = 0; k < table->modelList[i].list[j]->ammountOfComps; k++) {
                if (table->modelList[i].list[j]->comp[k].frame == frameType) {
                    isNonDeletble = 1;
                    break;
                }
            }

            if (isNonDeletble == 1) {
                isNonDeletble = 0;
                continue;
            }

            deleteModelFromBucket(table->modelList + i, j);
            j--;
        }
    }
}

void deleteModelFromBucket(bucket* currentBucket, int ind) {
    modelFree(currentBucket->list[ind]);
    //free(currentBucket->list[ind]);

    for(int i = ind + 1; i < currentBucket->len; i++) currentBucket->list[i - 1] = currentBucket->list[i];

    currentBucket->len--;
    currentBucket->list = reallocWithoutNull(currentBucket->list, sizeof(model*) * currentBucket->len);
}

// FREE
table* tableFree(table* table) {
    for(int i = 0; i < table->len; i++) {
        for (int j = 0; j < table->modelList[i].len; j++) {
            modelFree(table->modelList[i].list[j]);
        }
        free(table->modelList[i].list);
    }
    free(table->modelList);
    free(table);
    table = NULL;
    return table;
}




void deleteByInd(table* table) {
    if (table == NULL || table->len == 0) {
		printf("\n\tOperation canceled. Model tree is empty.\n");
		return;
	}

    printf("\n\tInput the ind (0-%d) - ", table->ammountOfModels - 1);
	int id = intScanWithLimitCheck(0, table->ammountOfModels - 1);

    for (int i = 0; i < table->len; i++) {
        for(int j = 0; j < table->modelList[i].len; j++) {
            if (table->modelList[i].list[j]->id == id) {
                deleteModelFromBucket(table->modelList + i, j);
                break;
            }
        }
    }
}

// INDECATION
int indecation(table* table) {
    int curInd = 0;

    for (int i = 0; i < table->len; i++) {
        for(int j = 0; j < table->modelList[i].len; j++) {
            table->modelList[i].list[j]->id = curInd;
            curInd++;
        }
    }

    return curInd;
}


