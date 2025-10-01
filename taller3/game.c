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

void max_heapify(int arr[], int index, int size)
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

void build_max_heap(int arr[], int size)
{
    for (int i = parent(size - 1); i >= 0; --i)
    {
        max_heapify(arr, i, size);
    }
}

void min_heapify(int arr[], int index, int size)
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

void build_min_heap(int arr[], int size)
{
    for (int i = parent(size - 1); i >= 0; --i)
    {
        min_heapify(arr, i, size);
    }
}

int extract_max(int max_heap[], int *heap_size)
{
    int max_val = max_heap[0];
    max_heap[0] = max_heap[(*heap_size) - 1];
    (*heap_size)--;
    max_heapify(max_heap, 0, *heap_size);
    return max_val;
} 

int extract_min(int min_heap[], int *heap_size)
{
    int min_val = min_heap[0];
    min_heap[0] = min_heap[(*heap_size) - 1];
    (*heap_size)--;
    min_heapify(min_heap, 0, *heap_size);
    return min_val;
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

int main()
{
    int test_cases = 0;
    scanf("%d", &test_cases);

    while (test_cases--)
    {
        int n = 0;
        scanf("%d", &n);

        // cargar las listas de emma y otto.
        int *emma = (int *)malloc(n * sizeof(int));
        int emma_size = n;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &emma[i]);
        }

        int *otto = (int *)malloc(n * sizeof(int));
        int otto_size = n;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &otto[i]);
        }

        build_max_heap(emma, emma_size);
        build_min_heap(otto, otto_size);
        
        // jugar hasta que al menos una lista este vacia.
        int turn = 0;
        while (emma_size > 0 && otto_size > 0)
        {
            int emma_max = extract_max(emma, &emma_size);
            int otto_min = extract_min(otto, &otto_size);
            int sum = emma_max + otto_min;

            if (sum % 2 != 0)
            {
                insert_min(&otto, sum, &otto_size);
            }
            else
            {
                insert_max(&emma, (sum / 2), &emma_size);
            }

            turn++;
        }

        if (emma_size == 0)
        {
            printf("%d %s\n", turn, "Otto");
        }
        else if (otto_size == 0)
        {
            printf("%d %s\n", turn, "Emma");
        }

        free(emma);
        free(otto);
    }
}
