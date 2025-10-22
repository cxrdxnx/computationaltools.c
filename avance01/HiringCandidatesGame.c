#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *next;
    struct node *prev;
};

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

struct node* insertElementInCircularDoublyLinkedList(struct node* tail, int element) {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->key = element;

    if (tail == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    newNode->next = tail->next;
    newNode->prev = tail;
    tail->next->prev = newNode;
    tail->next = newNode;
    return newNode;
}

struct node* deleteNode(struct node* tail, struct node* target) {
    if (tail == NULL || target == NULL)
        return tail;

    if (tail == tail->next) {  // un solo nodo
        free(tail);
        return NULL;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;

    if (target == tail)
        tail = target->prev;

    struct node* nextNode = target->next;
    free(target);
    return tail ? tail : nextNode;
}

void freeRemaining(struct node* tail) {
    if (tail == NULL) return;
    struct node* start = tail->next;
    struct node* current = start;
    do {
        struct node* next = current->next;
        free(current);
        current = next;
    } while (current != start);
}

int main() {
    struct node* tail = NULL;
    int n, k, m;

    while (scanf("%d %d %d", &n, &k, &m) == 3) {
        if (n <= 0) break;

        tail = NULL;
        for (int i = 1; i <= n; i++) {
            tail = insertElementInCircularDoublyLinkedList(tail, i);
        }

        int* contratados = malloc(n * sizeof(int));
        int count = 0;

        if (n <= 2) {
            struct node* current = tail->next;
            for (int i = 0; i < n; i++) {
                contratados[count++] = current->key;
                current = current->next;
            }
            qsort(contratados, count, sizeof(int), compare);
            for (int i = 0; i < count; i++) {
                printf("%d%c", contratados[i], i < count - 1 ? ' ' : '\n');
            }
            freeRemaining(tail);
            free(contratados);
            continue;
        }

        struct node* s1 = tail->next;
        struct node* s2 = tail;

        while (n > 2 && tail != NULL) {
            for (int i = 1; i < k; i++) s1 = s1->next;
            for (int i = 1; i < m; i++) s2 = s2->prev;

            if (s1 == s2) {
                contratados[count++] = s1->key;
                struct node* next_s1 = s1->next;
                tail = deleteNode(tail, s1);
                n--;
                s1 = next_s1;
                s2 = s1->prev;
            } else {
                contratados[count++] = s1->key;
                contratados[count++] = s2->key;

                struct node* next_s1 = s1->next;
                struct node* prev_s2 = s2->prev;

                tail = deleteNode(tail, s1);
                n--;
                if (tail != NULL && n > 0) {
                    tail = deleteNode(tail, s2);
                    n--;
                }

                if (n <= 2 || tail == NULL) break;
                s1 = next_s1;
                s2 = prev_s2;
            }
        }

        if (tail != NULL && n > 0) {
            struct node* current = tail->next;
            for (int i = 0; i < n; i++) {
                contratados[count++] = current->key;
                current = current->next;
            }
            freeRemaining(tail);
        }

        qsort(contratados, count, sizeof(int), compare);
        for (int i = 0; i < count; i++) {
            printf("%d%c", contratados[i], i < count - 1 ? ' ' : '\n');
        }

        free(contratados);
    }

    return 0;
}
