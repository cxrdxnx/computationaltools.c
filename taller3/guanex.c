#include "stdio.h"
#include "stdlib.h"

void push_back(int **arr, int value, int *size)
{
    int *temp = (int *)realloc(*arr, (*size + 1) * sizeof(int));
    if (temp == NULL)
    {
        fprintf(stderr, "Error: no se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    *arr = temp;

    (*arr)[*size] = value;
    (*size)++;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return (i * 2) + 1;
}

int right(int i)
{
    return (i * 2) + 2;
}

void insert(int **mheap, int value, int *heap_size)
{
    push_back(mheap, value, heap_size);
    int current = (*heap_size) - 1;

    // mientras current no sea la raiz y sea menor a su padre
    while (current > 0 && (*mheap)[current] < (*mheap)[parent(current)])
    {
        // flotar a current para cumplir propiedad de min-heap.
        int temp = (*mheap)[current];
        (*mheap)[current] = (*mheap)[parent(current)]; 
        (*mheap)[parent(current)] = temp;

        current = parent(current);
    }
}

void min_heapify(int **mheap, int index, int *heap_size)
{
    int smallest = index;
    int l = left(index);
    int r = right(index);

    if (l < (*heap_size) && (*mheap)[l] < (*mheap)[smallest]) smallest = l;
    if (r < (*heap_size) && (*mheap)[r] < (*mheap)[smallest]) smallest = r;

    // el elemento en index tenia hijos (no era una hoja)
    if (smallest != index)
    {
        int temp = (*mheap)[index];
        (*mheap)[index] = (*mheap)[smallest];
        (*mheap)[smallest] = temp;

        min_heapify(mheap, smallest, heap_size);
    }
}

void extract(int **mheap, int *heap_size)
{
    (*mheap)[0] = (*mheap)[(*heap_size) - 1]; // intercambiar raiz y ultimo valor.
    (*heap_size)--; // eliminar ultimo elemento logicamente(no en memoria).
    if (*heap_size > 0)
    {
        min_heapify(mheap, 0, heap_size);
    }
}

int main()
{
    int queries = 0; // de 1 a 2*10^6
    scanf("%d", &queries);

    int *mheap = NULL;
    int size = 0;

    while(queries--)
    {
        int type = 0;
        scanf("%d", &type);

        if (type == 1)
        {
            int value = 0; // de 0 a 10^6
            scanf("%d", &value);
            insert(&mheap, value, &size);
        }
        else if (type == 2)
        {
            if (size > 0)
            {
                extract(&mheap, &size);
            }
        }
        else if (type == 3)
        {
            (size > 0) ? printf("%d\n", mheap[0]) : printf("Empty!\n");
        }
    }

    return 0;
}
