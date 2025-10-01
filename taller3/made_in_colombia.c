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

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return i * 2 + 1;
}

int right(int i)
{
    return i * 2 + 2;
}

void max_heapify(int *arr, int index, int size)
{
    int greatest = index;
    int l = left(index);
    int r = right(index);

    if (l < size && arr[l] > arr[greatest]) greatest = l;
    if (r < size && arr[r] > arr[greatest]) greatest = r;

    if (greatest != index)
    {
        swap(&arr[index], &arr[greatest]);
        max_heapify(arr, greatest, size);
    }
}

void min_heapify(int *arr, int index, int size)
{
    int smallest = index;
    int l = left(index);
    int r = right(index);

    if (l < size && arr[l] < arr[smallest]) smallest = l;
    if (r < size && arr[r] < arr[smallest]) smallest = r;

    if (smallest != index)
    {
        swap(&arr[index], &arr[smallest]);
        min_heapify(arr, smallest, size);
    }
}

void insert_max(int **max_heap, int value, int *heap_size)
{
    push_back(max_heap, value, heap_size);
    int current = (*heap_size) - 1;

    while (current > 0 && (*max_heap)[current] > (*max_heap)[parent(current)])
    {
        swap(&(*max_heap)[current], &(*max_heap)[parent(current)]);
        current = parent(current);
    }
}

void insert_min(int **min_heap, int value, int *heap_size)
{
    push_back(min_heap, value, heap_size);
    int current = (*heap_size) - 1;

    while (current > 0 && (*min_heap)[current] < (*min_heap)[parent(current)])
    {
        swap(&(*min_heap)[current], &(*min_heap)[parent(current)]);
        current = parent(current);
    }
}

int extract_max(int *max_heap, int *heap_size)
{
    int max_val = max_heap[0];
    max_heap[0] = max_heap[(*heap_size) - 1];
    (*heap_size)--;
    max_heapify(max_heap, 0, *heap_size);
    return max_val;
} 

int extract_min(int *min_heap, int *heap_size)
{
    int min_val = min_heap[0];
    min_heap[0] = min_heap[(*heap_size) - 1];
    (*heap_size)--;
    min_heapify(min_heap, 0, *heap_size);
    return min_val;
} 

int main()
{
    int n;

    while(scanf("%d", &n) == 1 && n > 0)
    {
        int *min_heap = NULL;
        int min_heap_size = 0;

        int *max_heap = NULL;
        int max_heap_size = 0;

        double median_sum = 0.0;
        for (int i = 0; i < n; ++i)
        {
            int element = 0; // entre 0 y 10^9
            scanf("%d", &element);

            // Si es el primer elemento, o pertenece al lado izquierdo.
            if (max_heap_size == 0 || element <= max_heap[0])
            {
                insert_max(&max_heap, element, &max_heap_size);
            }
            else
            {
                insert_min(&min_heap, element, &min_heap_size);
            }

            // Mantener cantidad de elementos del max heap igual a la cantidad de elementos de  min heap + 1 como maximo.
            // balanceo
            if (max_heap_size > min_heap_size + 1)
            {
                int val = extract_max(max_heap, &max_heap_size);
                insert_min(&min_heap, val, &min_heap_size);
            }
            else if (min_heap_size > max_heap_size)
            {
                int val = extract_min(min_heap, &min_heap_size);
                insert_max(&max_heap, val, &max_heap_size);
            }

            median_sum += (double)max_heap[0];
        }
        
        double mean = median_sum / (double)n;
        printf("%0.2lf\n", mean);
        
        free(min_heap);
        free(max_heap);
    }
    
    return 0;

}
