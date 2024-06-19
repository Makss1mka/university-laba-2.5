#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "tools.h"

treeElem* getNextNode(treeElem* node, int dir) {
    if (node == NULL) return NULL;
    if(dir == 1) return node->right;
    return node->left;
}

// PRINTING
void nodePrint(treeElem* node) { 
    if (node->left != NULL) nodePrint(node->left);
    
    printModel(node->model, "\t");
    
    if (node->right != NULL) nodePrint(node->right);
}

void treePrint(treeElem* top) {
    if (top == NULL) {
        printf("\n\tCurrent model tree is free.\n");
        return;
    }
    printf("\n\tCurrent models:");
    nodePrint(top);
    printf("\n");
}

// ADDING
treeElem* addModelToTree(treeElem* top, model* currentModel) {
    treeElem* currentNode = mallocWithoutNull(sizeof(treeElem));
    currentNode->model = currentModel;
    currentNode->right = NULL, currentNode->left = NULL;

    if(top == NULL) {
        top = currentNode;
        currentNode = NULL;
        return top;
    }

    treeElem* comparable = top;
    int dir = strCompareWithFree(lower(currentNode->model->modelName), lower(comparable->model->modelName));

    while (getNextNode(comparable, dir) != NULL && dir != 0) {
        comparable = getNextNode(comparable, dir);
        dir = strCompareWithFree(lower(currentNode->model->modelName), lower(comparable->model->modelName));
    }

    if (dir == 0) {
        printf("\n\tIncorrect name.\n");
        return NULL;
    } 

    if (dir == 1) {
        comparable->right = currentNode;
    } else if (dir == -1) {
        comparable->left = currentNode;
    }

    return top;
}

// FIND
model* find(char* name, treeElem* top) {
    treeElem* comparable = top;
    int dir = strCompareWithFree(lower(name), lower(comparable->model->modelName));

    while(dir != 0 && getNextNode(comparable, dir) != NULL) {
        comparable = getNextNode(comparable, dir);
        dir = strCompareWithFree(lower(name), lower(comparable->model->modelName));
    }

    if (dir == 0) return comparable->model;

    return NULL;
}

void findByName(treeElem* top) {
    printf("\n\tInput the car model name - ");
    char* name = mallocWithoutNull(30);
    name = fgets(name, 30, stdin);
    rewind(stdin);
    name = strCorrection(name);

    model* findableModel = find(name, top);

    if (findableModel == NULL) {
        printf("\n\tModel with that name doesn't exist in the tree.\n");
        return;
    }

    printf("\n\tFindable model:");
    printModel(findableModel, "\t");
    printf("\n");
}

// FREE
void freeNodeData(treeElem* node) {
    modelFree(node->model);
    free(node->model);
    free(node);
}

void freeNode(treeElem* node) {
    if (node == NULL) return;

    freeNode(node->left);
    freeNode(node->right);
    freeNodeData(node);
}

treeElem* freeTree(treeElem* top) {
    freeNode(top);

    return NULL;
}

// DELETING
treeElem* copySubTree(treeElem* node, treeElem* subTree) {
    if (node->left == NULL) return subTree;
    
    node->left = copySubTree(node->left, subTree);
    
    return node;
}

treeElem* delete(treeElem* node) {
    treeElem* temp;
    
    if (node->right == NULL && node->left == NULL) {
        freeNodeData(node);
        return NULL;
    } else if (node->right == NULL && node->left != NULL) {
        temp = node->left;
        freeNodeData(node);
        return temp;
    } else if (node->right != NULL && node->left == NULL) {
        temp = node->right;
        freeNodeData(node);
        return temp;
    } else {
        temp = node->right;
       
        while(temp->left != NULL) {
            temp = temp->left;
        }

        modelFree(node->model);
        free(node->model);
        node->model = temp->model;
        
        node->right = copySubTree(node->right, temp->right);

        temp = NULL;

        return node;
    }
}

treeElem* checkAndDelete(treeElem* node, int frame) {
    if (node == NULL) return NULL;
    
    char* camparable = NULL;

    for(int i = 0; i < node->model->ammountOfComps; i++) {
        if (node->model->comp[i].frame == frame) {
            while (node->left != NULL) {
                camparable = node->left->model->modelName;
                node->left = checkAndDelete(node->left, frame);

                if (node->left == NULL || strcmp(node->left->model->modelName, camparable) == 0) break;
            }
            while(node->right != NULL) {
                camparable = node->right->model->modelName;
                node->right = checkAndDelete(node->right, frame);

                if (node->right == NULL || strcmp(node->right->model->modelName, camparable) == 0) break;
            }
            return node;
        }
    }
    
    return delete(node);
}

treeElem* deleteByFrameFromTree(treeElem* top) {
    if (top == NULL) {
		printf("\n\tOperation canceled. Model tree is empty.\n");
		return NULL;
	}

    printf("\n\tInput the frame type (0-micro, 1-sedan, 2-cupe, 3-crossover, 4-cabriolet, 5-picap, 6-track) - ");
	int frameType = intScanWithLimitCheck(0, 6);

    char* camparable = top->model->modelName;

    while (1) {
        top = checkAndDelete(top, frameType);

        if (top == NULL || strcmp(top->model->modelName, camparable) == 0) return top;

        camparable = top->model->modelName;
    }

    return top;
}





treeElem* findAndDelete(treeElem* node, int id) {
    if (node == NULL) return NULL;

    if (node->model->id == id) return delete(node);

    if (id < node->model->id) {
        node->left = findAndDelete(node->left, id);
    } else {
        node->right = findAndDelete(node->right, id);
    }

    return node;
}

treeElem* deleteByIndInTree(treeElem* top, int ammountOfModels) {
    if (top == NULL) {
		printf("\n\tOperation canceled. Model tree is empty.\n");
		return NULL;
	}

    printf("\n\tInput the ind (0-%d) - ", ammountOfModels - 1);
	int id = intScanWithLimitCheck(0, ammountOfModels - 1);

    top = findAndDelete(top, id);

    return top;
}

// INDECATION
int indecation(treeElem* top) {
    int currentInd = 0;

    return indecateNode(top, &currentInd);
}

int indecateNode(treeElem* node, int* curInd) {
    if (node == NULL) return *curInd;

    *curInd = indecateNode(node->left, curInd);

    node->model->id = *curInd;
    (*curInd)++;
    
    *curInd = indecateNode(node->right, curInd);

    return *curInd;
} 
