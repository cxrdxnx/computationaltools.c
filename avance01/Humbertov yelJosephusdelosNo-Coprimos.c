#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


struct node {
    int key;
    int maxValue;
    int minValue;
    int sumPush;
    struct node* next;
};


struct node* push(struct node* top, int element, int maxValue, int minValue) {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->key = element;
    newNode->maxValue = maxValue;
    newNode->minValue = minValue;
    newNode->next = top;

    if (top == NULL) {
        newNode->sumPush = element;
    } else {
        newNode->sumPush = element + top->sumPush;
    }


    top = newNode;
    return top;
}


int pop(struct node** top) {
    struct node* actualNode = *top;
    int element = actualNode->key;
    *top = actualNode->next;
    free(actualNode);
    return element;
}


int stackEmpty(struct node* top) {
    if (top == NULL)
        return TRUE;
    else
        return FALSE;
}

int myMaximum(int value1, int value2) {
    int maxValue;
    if (value1 > value2)
        maxValue = value1;
    else
        maxValue = value2;
    return maxValue;
}


int myMinimum(int value1, int value2) {
    int minValue;
    if (value1 < value2)
        minValue = value1;
    else
        minValue = value2;
    return minValue;
}


struct node* deleteStack(struct node* top) {
    struct node* actualNode = top;
    while (actualNode != NULL) {
        top = actualNode->next;
        free(actualNode);
        actualNode = top;
    }
    return top;
}

void sumStack(struct node* top) {
    printf("%d\n", top->sumPush);
}



int main() {
    struct node* top = NULL;
    int operation, element, totalCases, idCase;
    int totalQueries, idQuery, maxValue, minValue;

    scanf("%d", &totalCases);

    for (idCase = 1; idCase <= totalCases; idCase++) {
        scanf("%d", &totalQueries);
        for (idQuery = 1; idQuery <= totalQueries; idQuery++) {
            scanf("%d", &operation);
            if (operation == 1) { 
                scanf("%d", &element);
                if (stackEmpty(top)) {
                    maxValue = element;
                    minValue = element;
                } else {
                    maxValue = myMaximum(element, top->maxValue);
                    minValue = myMinimum(element, top->minValue);
                }
                top = push(top, element, maxValue, minValue);
            } else if (operation == 2) { 
                if (!stackEmpty(top)) {
                    element = pop(&top);
                }
            } else if (operation == 3) {
                if (stackEmpty(top)) {
                    printf("Empty!\n");
                } else {
                    sumStack(top);
                }
            }
        }
   
        top = deleteStack(top);
    }

    return 0;
}

