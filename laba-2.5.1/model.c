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
    model *model = NULL;
	model = mallocWithoutNull(sizeof(model) * 1);

    printf("\n\tCreating new model:");

	printf("\n\n\tinput the car model name - ");
	char* temp = mallocWithoutNull(30);
	temp = fgets(temp, 30, stdin);
	rewind(stdin);
	model->modelName = strCorrection(temp);

    printf("\tEnter the ammount of complecations (0-100) - ");
    model->ammountOfComps = intScanWithLimitCheck(0, 100);
    model->comp = mallocWithoutNull(sizeof(comp) * model->ammountOfComps);
	
    for (int i = 0; i < model->ammountOfComps; i++) {
        printf("\tisuue date (1850-2024y) - ");
	    model->comp[i].issueDate = intScanWithLimitCheck(1850, 2024);

	    printf("\tisuue end date (1850-2024y) - ");
	    model->comp[i].issueDateEnd = intScanWithLimitCheck((*model).comp[i].issueDate, 2024);

	    printf("\tengine capacity (0-10l) - ");
	    model->comp[i].engCap = intScanWithLimitCheck(0, 10);

	    printf("\tenter frame type (0-micro, 1-sedan, 2-cupe, 3-crossover, 4-cabriolet, 5-picap, 6-track) - ");
	    model->comp[i].frame = intScanWithLimitCheck(0, 6);
    }
	
	rewind(stdin);
	return model;
}

void modelFree(model* currentModel) {
    free(currentModel->comp);
    free(currentModel->modelName);
}

