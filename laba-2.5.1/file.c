#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "tools.h"
#include "tree.h"

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
    model* currentModel = NULL;
    currentModel = mallocWithoutNull(sizeof(model) * 1);

    currentModel->modelName = normalFscanf(file);
    
    fscanf(file, "%d\n", &(currentModel->ammountOfComps));
    currentModel->comp = mallocWithoutNull(sizeof(comp) * currentModel->ammountOfComps);
    
    for(int i = 0; i < currentModel->ammountOfComps; i++) {
        fscanf(file, "%d\n", &currentModel->comp[i].issueDate);
        fscanf(file, "%d\n", &currentModel->comp[i].issueDateEnd);
        fscanf(file, "%d\n", &currentModel->comp[i].engCap);
        fscanf(file, "%d", &currentModel->comp[i].frame);
    }

	fgetc(file);
    
	return currentModel;
}

// FOR TREE
treeElem* getAllinTree(char* fileName) {
    FILE* file = fileOpener(fileName, "rt");
    treeElem* top = NULL;

    fgetc(file);
    
    while (fgetc(file) != EOF) {
        top = addModelToTree(top, getOneModelEntry(file));
    }

    fclose(file);

    return top;
}

// SAVING
void saveTree(treeElem* top, char* filePath) {
    FILE* file = fileOpener(filePath, "wt");

    saveNode(top, file);

    fclose(file);
}

void saveNode(treeElem* node, FILE* file) {
    if (node == NULL) return;

    writeEntry(file, node->model);

    saveNode(node->left, file);
    saveNode(node->right, file);
}

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
