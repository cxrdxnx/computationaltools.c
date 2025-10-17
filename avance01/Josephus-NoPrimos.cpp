#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Definicion de la estructura del nodo
typedef struct node {
    int key;
    struct node *next;
} node;

// Inserta un nuevo nodo al final de la lista circular
node *InsertCircularLL(node *tail, int element) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = element;

    if (tail == NULL) {
        newNode->next = newNode;
        tail = newNode;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    return tail;
}

// Calcula el MCD entre dos numeros (algoritmo de Euclides)
int mcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Elimina el nodo apuntado por "target" y devuelve el nuevo tail
node *DeleteNode(node *tail, node *prev, node *target) {
    if (target == tail && target->next == tail) {
        free(target);
        return NULL;
    }

    prev->next = target->next;

    if (target == tail) {
        tail = prev;
    }

    free(target);
    return tail;
}

// Elimina al jugador del juego hasta llegar al ganador
int EliminatePlayer(node *tail) {
    if (tail == NULL) return -1;

    node *pivot = tail->next;      
    node *current, *prev;

    if (pivot->key == 1) {
        node *toFree = pivot;
        tail->next = pivot->next;
        pivot = pivot->next;
        free(toFree);
        if (tail->next == tail) return tail->key; 
    }

    current = pivot->next;
    prev = pivot;

    while (tail != tail->next) {
        int g = mcd(pivot->key, current->key);

        if (g > 1) { 
            tail = DeleteNode(tail, prev, current);
            pivot = prev->next;
            current = pivot->next;
            prev = pivot;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return tail->key; // ultimo jugador en pie
}

int main() {
    int t, n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        node *tail = NULL;
        for (int i = 1; i <= n; i++) {
            tail = InsertCircularLL(tail, i);
        }

        int winner = EliminatePlayer(tail);
        printf("%d\n", winner);
    }

    return 0;
}
