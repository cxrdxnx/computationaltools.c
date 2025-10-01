#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXT 100000

typedef struct {
    long long time;
    char name[16];
    long long period;
    int priority;
} Medicine;

int Parent(int i) {
    return i / 2;
}

int Left(int i) {
    return 2 * i;
}

int Right(int i) {
    return 2 * i + 1;
}

void MinHeapify(Medicine Q[], int i, int heapSize) {
    int l, r, least;
    Medicine temp;
    l = Left(i);
    r = Right(i);
    
    if ((l <= heapSize) && (Q[l].time < Q[i].time))
        least = l;
    else if ((l <= heapSize) && (Q[l].time == Q[i].time) && (Q[l].priority < Q[i].priority))
        least = l;
    else
        least = i;
        
    if ((r <= heapSize) && (Q[r].time < Q[least].time))
        least = r;
    else if ((r <= heapSize) && (Q[r].time == Q[least].time) && (Q[r].priority < Q[least].priority))
        least = r;
    
    if (least != i) {
        temp = Q[i];
        Q[i] = Q[least];
        Q[least] = temp;
        MinHeapify(Q, least, heapSize);
    }
}

Medicine MinPQ_Extract(Medicine Q[], int *heapSize) {
    Medicine min;
    min.time = -1;
    
    if (*heapSize < 1)
        return min;
    
    min = Q[1];
    Q[1] = Q[*heapSize];
    (*heapSize)--;
    MinHeapify(Q, 1, *heapSize);
    return min;
}

void MinPQ_Insert(Medicine Q[], Medicine med, int *heapSize) {
    (*heapSize)++;
    int i = *heapSize;
    Medicine temp;
    
    Q[i] = med;
    
    while ((i > 1) && ((Q[Parent(i)].time > Q[i].time) || 
                       (Q[Parent(i)].time == Q[i].time && Q[Parent(i)].priority > Q[i].priority))) {
        temp = Q[i];
        Q[i] = Q[Parent(i)];
        Q[Parent(i)] = temp;
        i = Parent(i);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        
        Medicine Q[MAXT + 2];
        int heapSize = 0;
        
        for (int i = 0; i < n; i++) {
            Medicine med;
            scanf("%s %lld", med.name, &med.period);
            med.time = med.period;
            med.priority = i;
            
            MinPQ_Insert(Q, med, &heapSize);
        }
        
        for (int i = 0; i < k; i++) {
            Medicine current = MinPQ_Extract(Q, &heapSize);
            
            printf("%lld %s\n", current.time, current.name);
            
            current.time += current.period;
            MinPQ_Insert(Q, current, &heapSize);
        }
    }
    
    return 0;
}
