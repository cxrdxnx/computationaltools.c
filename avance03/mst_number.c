#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#define MAXV 10005
#define myInfinite LLONG_MAX
#define NIL -1

struct edge
{
    int vertex;
    long long weight;
    struct edge *next;
};

struct graph
{
    int n_vertex;
    int n_edges;
    struct edge *Adj[MAXV];
};

struct nodePQ
{
    int vertex;
    long long distance; 
};

int Parent(int i) { return i >> 1; }
int Left(int i) { return i << 1; }
int Right(int i) { return (i << 1) + 1; }

void MinHeapify(struct nodePQ Q[], int i, int heapSize, int positionVertex[])
{
    int l, r, least, tempPosition;
    struct nodePQ tempNode;
    l = Left(i);
    r = Right(i);

    if((l <= heapSize) && (Q[l].distance < Q[i].distance))
        least = l;
    else
        least = i;

    if((r <= heapSize) && (Q[r].distance < Q[least].distance))
        least = r;

    if(least != i)
    {
        tempPosition = positionVertex[Q[i].vertex];
        tempNode = Q[i];

        positionVertex[Q[i].vertex] = positionVertex[Q[least].vertex];
        Q[i] = Q[least];

        positionVertex[Q[least].vertex] = tempPosition;
        Q[least] = tempNode;

        MinHeapify(Q, least, heapSize, positionVertex);
    }
}

int MinPQ_Extract(struct nodePQ Q[], int *heapSize, int positionVertex[])
{
    int myMin = -1; // Ajustado a -1 para control de errores

    if(*heapSize >= 1)
    {
        myMin = Q[1].vertex;

        positionVertex[Q[*heapSize].vertex] = 1;
        Q[1] = Q[*heapSize];

        *heapSize = *heapSize - 1;
        MinHeapify(Q, 1, *heapSize, positionVertex);
    }
    return myMin;
}

void MinPQ_DecreaseKey(struct nodePQ Q[], int i, long long key, int positionVertex[])
{
    int tempPosition;
    struct nodePQ tempNode;

    if(key < Q[i].distance)
    {
        Q[i].distance = key;

        while((i > 1) && (Q[Parent(i)].distance > Q[i].distance))
        {
            tempPosition = positionVertex[Q[i].vertex];
            tempNode = Q[i];

            positionVertex[Q[i].vertex] = positionVertex[Q[Parent(i)].vertex];
            Q[i] = Q[Parent(i)];

            positionVertex[Q[Parent(i)].vertex] = tempPosition;
            Q[Parent(i)] = tempNode;

            i = Parent(i);
        }
    }
}

void MinPQ_Insert(struct nodePQ Q[], long long key, int vertex, int *heapSize, int positionVertex[])
{
    *heapSize = *heapSize + 1;
    Q[*heapSize].distance = myInfinite;
    Q[*heapSize].vertex = vertex;
    positionVertex[vertex] = *heapSize;
    MinPQ_DecreaseKey(Q, *heapSize, key, positionVertex);
}

struct graph *ReadGraph(int vertexes, int edges)
{
    int idVertex, idEdge, u, v;
    long long w; // Peso Long Long
    struct graph *G;
    struct edge *tempEdge;
    
    G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = vertexes;
    G->n_edges = edges;
    
    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;
        
    for (idEdge = 1; idEdge <= G->n_edges; idEdge++)
    {
        scanf("%d %d %lld", &u, &v, &w);
        
        tempEdge = (struct edge *) malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->weight = w;
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;
        
        if (u != v)
        {
            tempEdge = (struct edge *) malloc(sizeof(struct edge));
            tempEdge->vertex = u;
            tempEdge->weight = w;
            tempEdge->next = G->Adj[v];
            G->Adj[v] = tempEdge;
        }
    }
    return G;
}

struct graph *DeleteGraph(struct graph *G)
{
    int idVertex;
    struct edge *ActualEdge, *NextEdge;
    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
    {
        ActualEdge = G->Adj[idVertex];
        while (ActualEdge != NULL)
        {
            NextEdge = ActualEdge->next;
            free(ActualEdge);
            ActualEdge = NextEdge;
        }
    }
    free(G);
    return NULL;
}

int Prim(struct graph *G, long long d[], int pi[], int s)
{
    struct nodePQ Q[MAXV];
    int positionVertex[MAXV];
    int heapSize = 0;

    int u, v;
    long long w;
    int treeVertexNum = 0;
    struct edge *tempEdge;

    // Inicializar y llenar heap
    for (int i = 1; i <= G->n_vertex; i++)
    {
        d[i] = myInfinite;
        pi[i] = NIL;

        if (i == s)
        {
            d[s] = 0;
            MinPQ_Insert(Q, 0, s, &heapSize, positionVertex);
        } else
        {
            MinPQ_Insert(Q, myInfinite, i, &heapSize, positionVertex);
        }
    }
    
    while (heapSize > 0)
    {
        u = MinPQ_Extract(Q, &heapSize, positionVertex);
        positionVertex[u] = 0; // Marcar como extraído
        
        if (d[u] == myInfinite) break; // Grafo inconexo
        
        treeVertexNum++; // Contar nodo conectado
        
        tempEdge = G->Adj[u];
        while (tempEdge != NULL)
        {
            v = tempEdge->vertex;
            w = tempEdge->weight;
            
            if ((positionVertex[v] != 0) && (d[v] > w))
            {
                d[v] = w;
                pi[v] = u;
                MinPQ_DecreaseKey(Q, positionVertex[v], w, positionVertex);
            }
            tempEdge = tempEdge->next;
        }
    }
    return treeVertexNum;
}

void deleteEdges(struct graph *G, int pi[], long long d[])
{
    for (int u = 1; u <= G->n_vertex; u++)
    {
        struct edge *current = G->Adj[u];
        struct edge *previous = NULL;

        while(current != NULL)
        {
            int v = current->vertex;
            bool tocaEliminar = false;
            
            bool esHijo = (pi[u] == v && current->weight == d[u]);
            bool esPadre = (pi[v] == u && current->weight == d[v]);

            if (esHijo || esPadre) tocaEliminar = true;

            if (tocaEliminar)
            {
                struct edge *eliminar = current;
                if (previous == NULL) { // Cabeza
                    G->Adj[u] = current->next;
                    current = G->Adj[u];
                } else { // intermedio o ultimo
                    previous->next = current->next;
                    current = current->next;
                }
                free(eliminar);
            }
            else {
                previous = current;
                current = current->next;
            }
        }
    }
}

void solver(struct graph *G)
{
    int MSTNumber = 0;
    long long treeWeights[MAXV]; 
    
    long long d[MAXV]; 
    int pi[MAXV];

    while (true)
    {
        int connected = Prim(G, d, pi, 1);
        
        if (connected < G->n_vertex) break; 
        
        long long weightMST = 0;
        for (int idVertex = 1; idVertex <= G->n_vertex; idVertex++) {
            weightMST += d[idVertex];
        }

        treeWeights[MSTNumber] = weightMST;
        MSTNumber++;
        
        deleteEdges(G, pi, d);
    }
    
    printf("%d\n", MSTNumber);
    for (int i = 0; i < MSTNumber; i++)
    {
        printf("%lld\n", treeWeights[i]);
    }
}

int main()
{
    int vertexes, edges;
    struct graph *G;
    
    while (scanf("%d %d", &vertexes, &edges) != EOF)
    {
        G = ReadGraph(vertexes, edges);
        solver(G);
        G = DeleteGraph(G);
    }
    return 0;
}