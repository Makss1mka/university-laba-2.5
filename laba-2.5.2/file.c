#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include "model.h"
#include "tools.h"

char* normalFscanf(FILE* file) {
	char* str = mallocWithoutNull(sizeof(char) * 30);
	char curChar = fgetc(file);
	int len = 0;
    
	while (curChar != EOF && curChar != '\n') {
		str[len++] = curChar;

		curChar = fgetc(file);
	}
    
	str[len] = '\0';
	return str;
}

model* getOneModelEntry(FILE* file) {
    model* createdModel = NULL;
    createdModel = mallocWithoutNull(sizeof(model) * 1);

    createdModel->modelName = normalFscanf(file);
    
    fscanf(file, "%d\n", &(createdModel->ammountOfComps));
    createdModel->comp = mallocWithoutNull(sizeof(comp) * createdModel->ammountOfComps);
    
    for(int i = 0; i < createdModel->ammountOfComps; i++) {
        fscanf(file, "%d\n", &createdModel->comp[i].issueDate);
        fscanf(file, "%d\n", &createdModel->comp[i].issueDateEnd);
        fscanf(file, "%d\n", &createdModel->comp[i].engCap);
        fscanf(file, "%d", &createdModel->comp[i].frame);
    }

	fgetc(file);
    
    createdModel->id = 0;   //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

	return createdModel;
}

// FOR HASH TABLE
table* getAllInTable(char* fileName) {
    FILE* file = fileOpener(fileName, "rt");
    model* curModel = NULL;
    int len = 0; 
    
    fscanf(file, "%d", &len);
    table* table = tableInit(len);

    fgetc(file);
    while (fgetc(file) != EOF) {  
        curModel = getOneModelEntry(file);
        
        addModelToTable(table, curModel);
    }
    
    curModel = NULL;

    fclose(file);

    return table;
}

// SAVINGS
void writeEntry(FILE* file, model* currentModel) {
	fprintf(file,"\n\n%s\n", currentModel->modelName);
    fprintf(file, "%d", currentModel->ammountOfComps);

    for(int i = 0; i < currentModel->ammountOfComps; i++) {
        fprintf(file, "\n%d\n", currentModel->comp[i].issueDate);
        fprintf(file, "%d\n", currentModel->comp[i].issueDateEnd);
        fprintf(file, "%d\n", currentModel->comp[i].engCap);
        fprintf(file, "%d", currentModel->comp[i].frame);
    }
}

void tableSave(table* table, char* filePath) {
    FILE* file = fileOpener(filePath, "wt");

    int ammount = 0;
    for(int i = 0; i < table->len; i++) ammount += table->modelList[i].len;
    fprintf(file,"%d", ammount);

    for(int i = 0; i < table->len; i++) {
        for (int j = 0; j < table->modelList[i].len; j++) {
            writeEntry(file, table->modelList[i].list[j]);
        }
    } 

    fclose(file);
}

