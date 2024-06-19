#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "file.c"
#include "hashTable.h"
#include "hashTable.c"
#include "model.h"
#include "model.c"
#include "tools.h"
#include "tools.c"
#include "yearList.h"
#include "yearList.c"

void menu(char* filePath) {
    int choice;
	table* table = getAllInTable(filePath);
	table->ammountOfModels = indecation(table);

	while (1) {
		printf("\n\tMenu:\n\t1) Create new model\n\t2) Find model by time issue period\n\t3) Get year list\n\t4) Delete by frame type\n\t5) Print current model list\n\t6) Save current table\n\t7) Delete by index\n\t8) Exit\n\tSelect the option - ");

		switch (choice = intScanWithLimitCheck(1, 8)) {
		case 1:
			addModelToTable(table, createModel());
			table->ammountOfModels = indecation(table);
			break;
		case 2:
			findModelByTimePeriod(table);
			break;
		case 3:
			makeYearListFromTable(table);
			break;
		case 4:
			deleteByFrameType(table);
			table->ammountOfModels = indecation(table);
			break;
		case 5:
			tablePrint(table);
			break;
		case 6:
			tableSave(table, filePath);
			break;
		case 7:
			deleteByInd(table);
			table->ammountOfModels = indecation(table);
			break;
		case 8:
			table = tableFree(table);

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
    char filePath[] = "bd table.txt";

	printf("\n------------------------\n");

    menu(filePath);

	printf("\n------------------------\n");
}





