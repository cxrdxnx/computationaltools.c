#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    char data;
    struct node* next;
};

// Acepta punteros a la cabeza y a la cola para poder modificarlos.
void insert_at_end(struct node** head, struct node** tail, char character)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = character;
    new_node->next = NULL;

    if (*head == NULL) { // Si la lista está vacía
        *head = new_node;
        *tail = new_node;
    } else { // Si la lista ya tiene nodos
        (*tail)->next = new_node; // Enlaza la cola actual al nuevo nodo
        *tail = new_node;       // Actualiza la cola para que sea el nuevo nodo
    }
}

void remove_excluded_chars(struct node** head, const bool exclusion_map[256])
{
    struct node* current = *head;
    struct node* previous = NULL;
    while (current != NULL)
    {
        if (exclusion_map[(unsigned char)current->data])
        {
            struct node* node_to_delete = current;
            if (previous == NULL) // Eliminando la cabeza
            {
                *head = current->next;
                current = *head;
            }
            else // Eliminando en medio o al final
            {
                previous->next = current->next;
                current = previous->next;
            }
            free(node_to_delete);
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

void remove_consecutive_duplicates(struct node** head)
{
    struct node* current = *head;
    struct node* previous = NULL;
    while (current != NULL)
    {
        if (previous != NULL && previous->data == current->data)
        {
            struct node* node_to_delete = current;
            previous->next = current->next;
            current = previous->next;
            free(node_to_delete);
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

void trim_whitespace(struct node** head)
{
    // Eliminar espacios al principio
    while (*head != NULL && (*head)->data == ' ')
    {
        struct node* node_to_delete = *head;
        *head = (*head)->next;
        free(node_to_delete);
    }

    if (*head == NULL) return; // La lista quedó vacía

    // Eliminar espacios al final
    struct node* current = *head;
    struct node* last_non_space = NULL;
    while (current != NULL)
    {
        if (current->data != ' ')
        {
            last_non_space = current;
        }
        current = current->next;
    }

    if (last_non_space != NULL && last_non_space->next != NULL)
    {
        current = last_non_space->next;
        last_non_space->next = NULL; // Cortar la lista

        // Liberar los nodos cortados
        while (current != NULL)
        {
            struct node* node_to_delete = current;
            current = current->next;
            free(node_to_delete);
        }
    }
}

void print_and_free_list(struct node* head)
{
    struct node* current = head;
    while (current != NULL)
    {
        printf("%c", current->data);
        struct node* node_to_delete = current;
        current = current->next;
        free(node_to_delete); // Liberamos la memoria mientras imprimimos
    }
    printf("\n");
}

int main()
{
    // Construir la lista enlazada
    struct node* message_head = NULL;
    struct node* message_tail = NULL;
    char character;
    while (scanf("%c", &character) == 1 && character != '\n') 
    {
        insert_at_end(&message_head, &message_tail, character);
    }

    // Leer la lista de exclusión y crear el mapa de búsqueda (O(1))
    scanf(" %*c");
    char exclusion_list[37];
    int exclusion_count = 0;
    char exclude_character;
    while(scanf("%c", &exclude_character) == 1 && exclude_character != ']')
    {
        exclusion_list[exclusion_count++] = exclude_character;
    }
    exclusion_list[exclusion_count] = '\0';

    bool exclusion_map[256] = {false};
    for (int i = 0; exclusion_list[i] != '\0'; ++i)
    {
        exclusion_map[(unsigned char)exclusion_list[i]] = true;
    }

    // Aplicar los filtros en secuencia
    remove_excluded_chars(&message_head, exclusion_map);
    remove_consecutive_duplicates(&message_head);
    trim_whitespace(&message_head);
    
    print_and_free_list(message_head);
    
    return 0;
}