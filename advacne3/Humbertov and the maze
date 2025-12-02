#include <stdio.h>
#include <stdlib.h>

#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -1
#define myInfinite 2147483647
#define MAXV 100005

struct edge {
    int vertex;
    struct edge *next;
};

struct graph {
    int n_vertex;
    int m_edges;
    struct edge *Adj[MAXV];
};

struct graph* ReadGraph(int vertexes, int edges) {
    int idVertex, idEdge, u, v;
    struct graph *G;
    struct edge *tempEdge;
    
    G = (struct graph*) malloc(sizeof(struct graph));
    G->n_vertex = vertexes;
    G->m_edges = edges;
    
    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;
    
    for (idEdge = 1; idEdge <= G->m_edges; idEdge++) {
        scanf("%d %d", &u, &v);
        
        tempEdge = (struct edge*) malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;
        
        if (u != v) {
            tempEdge = (struct edge*) malloc(sizeof(struct edge));
            tempEdge->vertex = u;
            tempEdge->next = G->Adj[v];
            G->Adj[v] = tempEdge;
        }
    }
    
    return G;
}

struct graph* DeleteGraph(struct graph *G) {
    int idVertex;
    struct edge *ActualEdge, *NextEdge;
    
    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++) {
        ActualEdge = G->Adj[idVertex];
        while (ActualEdge != NULL) {
            NextEdge = ActualEdge->next;
            free(ActualEdge);
            ActualEdge = NextEdge;
        }
    }
    
    free(G);
    return NULL;
}

void BFS(struct graph *G, int s, int color[], int d[], int pi[]) {
    int u, v, Q[MAXV], idHead = 1, idTail = 1;
    struct edge *tempEdge;
    
    for (u = 1; u <= G->n_vertex; u++) {
        color[u] = WHITE;
        d[u] = myInfinite;
        pi[u] = NIL;
    }
    
    color[s] = GRAY;
    d[s] = 0;
    Q[idTail++] = s;
    
    while (idHead < idTail) {
        u = Q[idHead++];
        tempEdge = G->Adj[u];
        
        while (tempEdge != NULL) {
            v = tempEdge->vertex;
            if (color[v] == WHITE) {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                pi[v] = u;
                Q[idTail++] = v;
            }
            tempEdge = tempEdge->next;
        }
        color[u] = BLACK;
    }
}
void solver(struct graph *G, int U, int Se, int Sa, int Di)
{
    int colorU[MAXV], dU[MAXV], piU[MAXV];
    int colorSe[MAXV], dSe[MAXV], piSe[MAXV];
    int colorSa[MAXV], dSa[MAXV], piSa[MAXV];
    int colorDi[MAXV], dDi[MAXV], piDi[MAXV];
    int u, maxDistance = -1;
    
    BFS(G, U, colorU, dU, piU);
    BFS(G, Se, colorSe, dSe, piSe);
    BFS(G, Sa, colorSa, dSa, piSa);
    BFS(G, Di, colorDi, dDi, piDi);

    for(u = 1; u <= G->n_vertex; u++)
    {
        if((dU[Se] == (dU[u] + dSe[u])) &&
           (dU[Sa] == (dU[u] + dSa[u])) &&
           (dU[Di] == (dU[u] + dDi[u])))
        {
            if(maxDistance < dU[u]) 
                maxDistance = dU[u];
        }
    }
    
    printf("%d %d %d %d\n", maxDistance, dU[Se] - maxDistance, dU[Sa] - maxDistance, dU[Di] - maxDistance);  
}

int main() {
    int N, U, Se, Sa, D, C;
    struct graph *G;
    
    while (scanf("%d %d %d %d %d %d", &N, &U, &Se, &Sa, &D, &C) != EOF) {
        G = ReadGraph(N, C);
        solver(G, U, Se, Sa, D);
        G = DeleteGraph(G);
    }
    
    return 0;
}
