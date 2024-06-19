#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "file.c"
#include "model.h"
#include "model.c"
#include "tools.h"
#include "tools.c"
#include "tree.h"
#include "tree.c"
#include "yearList.h"
#include "yearList.c"

void menu(char* filePath) {
    int choice;
	treeElem* top = getAllinTree(filePath);
    int ammountOfModels = indecation(top);

	while (1) {
		printf("\n\tMenu:\n\t1) Create new model\n\t2) Find model by name\n\t3) Get year list\n\t4) Delete by frame type\n\t5) Print current model list\n\t6) Save current tree\n\t7) delete by ind\n\t8) Exit\n\tSelect the option - ");

		switch (choice = intScanWithLimitCheck(1, 8)) {
		case 1:
			top = addModelToTree(top, createModel());
			ammountOfModels = indecation(top);
			break;
		case 2:
			findByName(top);
			break;
		case 3:
			makeYearListFromTree(top);
			break;
		case 4:
			top = deleteByFrameFromTree(top);
			ammountOfModels = indecation(top);
			break;
		case 5:
			treePrint(top);
			break;
		case 6:
			saveTree(top, filePath);
			break;
		case 7:
			top = deleteByIndInTree(top, ammountOfModels);
			ammountOfModels = indecation(top);
			break;
		case 8:
			top = freeTree(top);

			printf("\n------------------------\n");
			exit(0);
			break;
		default:
			printf("\n\nIncorrect input");
			break;
		}
	}
}

void main() {
    char filePath[] = "bd tree.txt";

	printf("\n------------------------\n");

    menu(filePath);

	printf("\n------------------------\n");
}





