#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -1
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

char names[MAXV][50];   
int tolerances[MAXV];

struct graph *DeleteGraph(struct graph *G) {
    if (!G) return NULL;
    for (int i = 1; i <= G->n_vertex; i++) {
        struct edge *curr = G->Adj[i];
        while (curr) {
            struct edge *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(G);
    return NULL;
}

// DFS_Visit modificado para hallar el ID del estudiante con mayor tolerancia en componente conexo
int DFS_Visit(struct graph *G, int u, int color[]) 
{
    color[u] = GRAY;
    int winnerID = u;

    struct edge *temp = G->Adj[u];
    while (temp != NULL) 
    {
        int v = temp->vertex;
        if (color[v] == WHITE) 
        {
            int contenderID = DFS_Visit(G, v, color);
            if (tolerances[contenderID] > tolerances[winnerID]) 
            {
                winnerID = contenderID;
            }
        }
        temp = temp->next;
    }
    color[u] = BLACK;
    return winnerID;
}

struct graph *ReadErnestoGraph(int n, int m) 
{
    struct graph *G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = n;
    G->m_edges = m;
    for (int i = 1; i <= n; i++) G->Adj[i] = NULL;

    map<string, int> nameToID; 

    // poblar arreglos paralelos (nombres y tolerancias)
    char tempName[50];
    int tempTol;

    for (int i = 1; i <= n; i++) 
    {
        scanf("%s %d", tempName, &tempTol);
        
        strcpy(names[i], tempName);
        tolerances[i] = tempTol;
        
        nameToID[string(tempName)] = i;
    }

    char uName[50], vName[50];
    for (int i = 1; i <= m; i++) 
    {
        scanf("%s %s", uName, vName);
        
        int u = nameToID[uName];
        int v = nameToID[vName];

        // conexion u-v
        struct edge *e1 = (struct edge *) malloc(sizeof(struct edge));
        e1->vertex = v; 
        e1->next = G->Adj[u]; 
        G->Adj[u] = e1;

        // conexion v-u (la amistad es en ambas direcciones)
        struct edge *e2 = (struct edge *) malloc(sizeof(struct edge));
        e2->vertex = u; 
        e2->next = G->Adj[v]; 
        G->Adj[v] = e2;
    }

    return G;
}

void solver(struct graph *G, int current_case) {
    int color[MAXV];
    for (int i = 1; i <= G->n_vertex; i++) color[i] = WHITE;

    vector<string> winners;

    // obtener el estudiante de mayor tolerancia en cada "isla"
    for (int i = 1; i <= G->n_vertex; i++) 
    {
        if (color[i] == WHITE) 
        {
            int bestID = DFS_Visit(G, i, color);
            winners.push_back(names[bestID]); // VERIFICAR SI BASTA ASI
        }
    }

    // imprimir nombres ganadores ordenados alfabeticamente
    sort(winners.begin(), winners.end());

    printf("Case %d:\n", current_case);
    for (string &s : winners) 
    {
        cout << s << '\n';
    }
}

int main() {
    int test_cases;
    scanf("%d", &test_cases);
    
    int current_case = 1;
    while (test_cases--) {
        int N, M;
        scanf("%d %d", &N, &M);

        struct graph *G = ReadErnestoGraph(N, M);
        solver(G, current_case);
        DeleteGraph(G);
        
        current_case++;
    }
    return 0;
}