#include <stdio.h>
#include <stdlib.h>   // malloc y free
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define max(a,b) ((a) > (b) ? (a) : (b)) 

struct node {
    int key;
    struct node *next;
    struct node *prev;
};

struct node* insertElementInCircularDoublyLinkedList(struct node* tail, int element) {
    struct node* newNode;
    newNode = (struct node*) malloc(sizeof(struct node));
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

struct node* deleteElementOfCircularDoublyLinkedList(struct node* tail, int element) {
    struct node* actualNode;
    int flag = FALSE;

    if (tail == NULL) {
        printf("The circular doubly linked list is empty.\n");
    } else {
        actualNode = tail->next;
        while ((actualNode != tail) && (flag == FALSE)) {
            if (actualNode->key == element) {
                flag = TRUE;
                break;
            } else {
                actualNode = actualNode->next;
            }
        }
        if (flag == FALSE) {
            if (tail->key == element) {
                flag = TRUE;
                actualNode = tail;
            }
        }
        if (tail == tail->next) {
            if (flag == TRUE) {
                free(tail);
                tail = NULL;
            } else {
                printf("The %d is not in the circular doubly linked list.\n", element);
            }
        } else {
            if (flag == FALSE) {
                printf("The %d is not in the circular doubly linked list.\n", element);
            } else {
                actualNode->next->prev = actualNode->prev;
                actualNode->prev->next = actualNode->next;
                if (actualNode == tail) {
                    tail = tail->prev;
                }
                free(actualNode);
            }
        }
    }
    return tail;
}

void printFromFirstToLastCircularDoublyLinkedList(struct node* tail) {
    struct node* actualNode;
    if (tail == NULL) {
        printf("NULL\n");
    } else {
        actualNode = tail->next;
        while (actualNode != tail) {
            printf("%d -> ", actualNode->key);
            actualNode = actualNode->next;
        }
        printf("%d ...\n", tail->key);
    }
}

void printFromLastToFirstCircularDoublyLinkedList(struct node* tail) {
    struct node* actualNode;
    if (tail == NULL) {
        printf("NULL\n");
    } else {
        actualNode = tail;
        while (actualNode != tail->next) {
            printf("%d -> ", actualNode->key);
            actualNode = actualNode->prev;
        }
        printf("%d ...\n", tail->next->key);
    }
}








int main() {
    struct node* tail;
    int n, k, m;
    int index, i, j;
    
    while (scanf("%d %d %d", &n, &k, &m)  == 3  && (n >0) ) {
        tail = NULL;
        
        for (index = 1; index <= n; index++) {
            tail = insertElementInCircularDoublyLinkedList(tail, index);
        }

        struct node* s1 = tail->next;  
        struct node* s2 = tail;        

        int contratados[10000];
        int count = 0;

        while (n >= max(k, m)) {
     
            for (i = 1; i < k; i++) 
                s1 = s1->next;
            
            
            for (i = 1; i < m; i++) 
                s2 = s2->prev;
            
            if (s1 == s2) {
                
                contratados[count++] = s1->key;
                
                struct node* next_s1 = s1->next;
                struct node* prev_s2 = s2->prev;
                
                tail = deleteElementOfCircularDoublyLinkedList(tail, s1->key);
                n--;
                 
                s1 = next_s1;
                s2 = prev_s2;
                
               
                if (s1 == s2 && n > 1) {
                    s1 = s1->next;
                }
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
                
                tail = deleteElementOfCircularDoublyLinkedList(tail, key1);
                if (tail != NULL) {
                    tail = deleteElementOfCircularDoublyLinkedList(tail, key2);
                }
                n -= 2;
                
                   if (n <= max(k, m)) {
        break;
    }
    
                if (tail != NULL && n > 0) {
                    s1 = safe_next;
                    s2 = safe_prev;
                    
                    if (s1 == s2 && n > 1) {
                        s1 = s1->next;
                    }
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
        

        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (contratados[i] > contratados[j]) {
                    int temp = contratados[i];
                    contratados[i] = contratados[j];
                    contratados[j] = temp;
                }
            }
        }
        
        for (i = 0; i < count; i++) {
            printf("%d", contratados[i]);
            if (i < count - 1) printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}

