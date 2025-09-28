#include <stdio.h>
#include <stdlib.h>
#define myInfinite 2000000000
#define MAXT 2000000
// MAXT es ajustable dependiendo del problema

// -------------------- FUNCIONES DE HEAP --------------------

// El padre de un nodo en index0 se obtiene asi:
int Parent(int i){
    return (i - 1) / 2;
}

// Hijo izquierdo en index0:
int Left(int i){
    return 2 * i + 1;
}

// Hijo derecho en index0:
int Right(int i){
    return 2 * i + 2;
}

void MinHeapify(int Q[], int i, int heapSize){
    int l = Left(i);
    int r = Right(i);
    int least = i;

    if(l < heapSize && Q[l] < Q[least])
        least = l;

    if(r < heapSize && Q[r] < Q[least])
        least = r;

    if (least != i){
        int temp = Q[i];
        Q[i] = Q[least];
        Q[least] = temp;
        MinHeapify(Q, least, heapSize);
    }
}

void MaxHeapify(int Q[], int i, int heapSize) {
    int l = Left(i);
    int r = Right(i);
    int largest = i;

    if (l < heapSize && Q[l] > Q[largest])
        largest = l;

    if (r < heapSize && Q[r] > Q[largest])
        largest = r;

    if (largest != i) {
        int temp = Q[i];
        Q[i] = Q[largest];
        Q[largest] = temp;
        MaxHeapify(Q, largest, heapSize);
    }
}

// Minimo siempre esta en Q[0] en index0
int MinPQ_Minimum(int Q[]){
    return Q[0];
}

int MinPQ_Extract(int Q[], int *heapSize){
    if(*heapSize <= 0){
        printf("ERROR: Heap underflow\n");
        return -1;
    }
    int min = Q[0];
    Q[0] = Q[*heapSize - 1];
    (*heapSize)--;
    MinHeapify(Q, 0, *heapSize);
    return min;
}

int MaxPQ_Extract(int Q[], int *heapSize){
    if(*heapSize <= 0){
        printf("ERROR: Heap underflow\n");
        return -1;
    }
    int max = Q[0];
    Q[0] = Q[*heapSize - 1];
    (*heapSize)--;
    MaxHeapify(Q, 0, *heapSize);
    return max;
}

void MinPQ_DecreaseKey(int Q[], int i, int key){
    if(key > Q[i]){
        printf("ERROR: New key is higher than current key\n");
        return;
    }
    Q[i] = key;
    while(i > 0 && Q[Parent(i)] > Q[i]){
        int p = Parent(i);
        int temp = Q[i];
        Q[i] = Q[p];
        Q[p] = temp;
        i = p;
    }
}

void MaxPQ_IncreaseKey(int Q[], int i, int key){
    if(key < Q[i]){
        printf("ERROR: New key is lower than current key\n");
        return;
    }
    Q[i] = key;
    while(i > 0 && Q[Parent(i)] < Q[i]){
        int p = Parent(i);
        int temp = Q[i];
        Q[i] = Q[p];
        Q[p] = temp;
        i = p;
    }
}

// Insertar siguiendo el esquema CLRS: primero aumentar heapSize y usar heapSize-1 como indice
void MinPQ_Insert(int Q[], int key, int *heapSize){
    (*heapSize)++;                                   // EDIT: aumentar tamano del heap antes de insertar (usar indice heapSize-1)
    Q[*heapSize - 1] = myInfinite;                   // EDIT: colocar un valor muy grande temporal en la nueva posicion
    MinPQ_DecreaseKey(Q, *heapSize - 1, key);        // EDIT: ajustar la nueva posicion al valor real 'key'
}

void MaxPQ_Insert(int Q[], int key, int *heapSize){
    (*heapSize)++;                                   // EDIT: aumentar tamano del heap antes de insertar (usar indice heapSize-1)
    Q[*heapSize - 1] = -1 * myInfinite;              // EDIT: colocar un valor muy bajo temporal en la nueva posicion
    MaxPQ_IncreaseKey(Q, *heapSize - 1, key);        // EDIT: ajustar la nueva posicion al valor real 'key'
}

// -------------------- PROGRAMA PRINCIPAL --------------------
int main(void){
    int n, minHeapSize = 0, maxHeapSize = 0, ID_element, element, MaxPQ_Array[MAXT], MinPQ_Array[MAXT];
    float suma_medianas = 0, mediana = 0, media = 0;

    if(scanf("%d", &n) != 1) return 0;

    for(ID_element = 0; ID_element < n; ID_element++){
        scanf("%d", &element);

        // Insertar en el heap correcto
        if(maxHeapSize == 0 || element <= MaxPQ_Array[0])
            MaxPQ_Insert(MaxPQ_Array, element, &maxHeapSize);
        else
            MinPQ_Insert(MinPQ_Array, element, &minHeapSize);

        // Rebalancear los heaps si es necesario
        if(maxHeapSize > minHeapSize + 1){
            int raiz = MaxPQ_Extract(MaxPQ_Array, &maxHeapSize);
            MinPQ_Insert(MinPQ_Array, raiz, &minHeapSize);
        }
        else if(minHeapSize > maxHeapSize){
            int raiz = MinPQ_Extract(MinPQ_Array, &minHeapSize);
            MaxPQ_Insert(MaxPQ_Array, raiz, &maxHeapSize);
        }

        // Calcular la mediana despues de cada insercion y rebalanceo
        // EDIT: tomar siempre la raiz del Max-Heap como mediana (posicion (len-1)/2 segun enunciado)
        //       NO promediar en caso par
        mediana = (float) MaxPQ_Array[0];

        suma_medianas += mediana;
    }

    media = suma_medianas / (float)n;
    printf("%.2f\n", media);

    return 0;
}
