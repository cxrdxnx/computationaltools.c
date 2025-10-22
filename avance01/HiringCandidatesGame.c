#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

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
        tail = newNode;
    } else {
        newNode->next = tail->next;
        newNode->next->prev = newNode;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    return tail;
}

struct node* deleteNode(struct node* tail, struct node* target) {
    if (tail == NULL || target == NULL)
        return tail;

    if (tail == tail->next) {  // solo un nodo
        free(tail);
        return NULL;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;

    if (target == tail)
        tail = target->prev;

    free(target);
    return tail;
}

int main() {
    struct node* tail;
    int n, k, m;
    int index, i;

    while (scanf("%d %d %d", &n, &k, &m) == 3) {
        if (n <= 0) break;

        tail = NULL;
        for (index = 1; index <= n; index++) {
            tail = insertElementInCircularDoublyLinkedList(tail, index);
        }

        int contratados[10000];
        int count = 0;

    
        if (n <= 2) {
            struct node* current = tail->next;
            for (i = 0; i < n; i++) {
                contratados[count++] = current->key;
                current = current->next;
            }
            qsort(contratados, count, sizeof(int), compare);
            for (i = 0; i < count; i++) {
                printf("%d", contratados[i]);
                if (i < count - 1) printf(" ");
            }
            printf("\n");
            continue;
        }

        struct node* s1 = tail->next;
        struct node* s2 = tail;

        while (n > 2) {
            for (i = 1; i < k; i++) s1 = s1->next;
            for (i = 1; i < m; i++) s2 = s2->prev;

            if (s1 == s2) {
                contratados[count++] = s1->key;

                struct node* next_s1 = s1->next;
                struct node* prev_s2 = s2->prev;

                tail = deleteNode(tail, s1);
                n--;

                s1 = next_s1;
                s2 = prev_s2;

                if (s1 == s2 && n > 1) s1 = s1->next;
            } else {
                int key1 = s1->key;
                int key2 = s2->key;

                struct node* safe_next;
                struct node* safe_prev;

                if (s1->next == s2) {
                    safe_next = s2->next;
                    safe_prev = s1->prev;
                } else if (s2->prev == s1) {
                    safe_next = s1->next;
                    safe_prev = s2->prev->prev;
                } else {
                    safe_next = s1->next;
                    safe_prev = s2->prev;

                    if (safe_next->key == key2) safe_next = safe_next->next;
                    if (safe_prev->key == key1) safe_prev = safe_prev->prev;
                }

                struct node* temp_s1 = s1;
                struct node* temp_s2 = s2;

                tail = deleteNode(tail, temp_s1);
                n--;

                if (tail != NULL && n > 0) {
                    tail = deleteNode(tail, temp_s2);
                    n--;
                }

                if (n <= 2) break;

                if (tail != NULL && n > 0) {
                    s1 = safe_next;
                    s2 = safe_prev;

                    if (s1 == s2 && n > 1) s1 = s1->next;
                }
            }
        }

        if (n > 0) {
            struct node* current = tail->next;
            for (i = 0; i < n; i++) {
                contratados[count++] = current->key;
                current = current->next;
            }
        }

        qsort(contratados, count, sizeof(int), compare);

        for (i = 0; i < count; i++) {
            printf("%d", contratados[i]);
            if (i < count - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
