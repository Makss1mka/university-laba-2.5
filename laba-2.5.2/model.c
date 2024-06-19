#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "tools.h"

void printModel(model* currentModel, char* offset) {

    printf("\n\t%sid: %d, model name: %s, ", offset, currentModel->id, currentModel->modelName);

    for(int i = 0; i < currentModel->ammountOfComps; i++) {
        printf("\n\t\t%sissue period: %d-%d, ", offset, currentModel->comp[i].issueDate, currentModel->comp[i].issueDateEnd);
        printf("eng cap: %d, ", currentModel->comp[i].engCap);
        printf("frame: %s", getFrameStr(currentModel->comp[i].frame));
    }

}

char* getFrameStr(int frameNum) {

	if (frameNum == 0) return "micro";
	if (frameNum == 1) return "sedan";
	if (frameNum == 2) return "cupe";
	if (frameNum == 3) return "crossover";
	if (frameNum == 4) return "cabriolet";
    if (frameNum == 5) return "picap";
    if (frameNum == 6) return "track";

}

model* createModel() {
    model *createdModel = NULL;
	createdModel = mallocWithoutNull(sizeof(model) * 1);

    printf("\n\tCreating new model:");

	printf("\n\n\tinput the car model name - ");
	char* temp = mallocWithoutNull(30);
	temp = fgets(temp, 30, stdin);
	rewind(stdin);
	createdModel->modelName = strCorrection(temp);

    printf("\tEnter the ammount of complecations (0-100) - ");
    createdModel->ammountOfComps = intScanWithLimitCheck(0, 100);
    createdModel->comp = mallocWithoutNull(sizeof(comp) * createdModel->ammountOfComps);
	
    for (int i = 0; i < createdModel->ammountOfComps; i++) {
        printf("\tisuue date (1850-2024y) - ");
	    createdModel->comp[i].issueDate = intScanWithLimitCheck(1850, 2024);

	    printf("\tisuue end date (1850-2024y) - ");
	    createdModel->comp[i].issueDateEnd = intScanWithLimitCheck((*createdModel).comp[i].issueDate, 2024);

	    printf("\tengine capacity (0-10l) - ");
	    createdModel->comp[i].engCap = intScanWithLimitCheck(0, 10);

	    printf("\tenter frame type (0-micro, 1-sedan, 2-cupe, 3-crossover, 4-cabriolet, 5-picap, 6-track) - ");
	    createdModel->comp[i].frame = intScanWithLimitCheck(0, 6);
    }

	createdModel->id = 0;

	rewind(stdin);
	return createdModel;
}

void modelFree(model* currentModel) {
    free(currentModel->comp);
    free(currentModel->modelName);
}

int getModelTimePeriod(model* currentModel) {
	if (currentModel->ammountOfComps == 0) return 0;

	int min, max, isFirst = 1;

	for(int i = 0; i < currentModel->ammountOfComps; i++) {
		if (isFirst == 1) {
			max = currentModel->comp[i].issueDateEnd;
			min = currentModel->comp[i].issueDate;
			continue;
		}
		if (currentModel->comp[i].issueDateEnd > max) max = currentModel->comp[i].issueDateEnd;
		if (currentModel->comp[i].issueDate < min) min = currentModel->comp[i].issueDate;
	}

	return max - min;
}
