#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXW 1000  
#define MAXH 1000
#define NIL -1
#define BLACK 0
#define GRAY 1
#define WHITE 2
#define myInfinite 2147483647

struct cell {
    int coord_x;
    int coord_y;
};


char Maze[MAXH + 1][MAXW + 1];
int color[MAXH + 1][MAXW + 1];
int d[MAXH + 1][MAXW + 1];
int f[MAXH + 1][MAXW + 1];
int regionID[MAXH + 1][MAXW + 1];
struct cell pi[MAXH + 1][MAXW + 1];

void ReadMaze(int H, int W)
{
    int idRow, idColumn;
    char line[MAXW + 1];

    for(idRow = 1; idRow <= H; idRow++)
    {
        scanf("%s", line);
        for(idColumn = 1; idColumn <= W; idColumn++)
            Maze[idRow][idColumn] = line[idColumn - 1];
    }
}

void assignMovements(struct cell arrayMov[])
{
    arrayMov[0].coord_x = 0;
    arrayMov[0].coord_y = 0;
    arrayMov[1].coord_x = 0;
    arrayMov[1].coord_y = -1;
    arrayMov[2].coord_x = 0;
    arrayMov[2].coord_y = 1;
    arrayMov[3].coord_x = -1;
    arrayMov[3].coord_y = 0;
    arrayMov[4].coord_x = 1;
    arrayMov[4].coord_y = 0;
}

void BFS_Maze(int W, int H, struct cell s)
{
    int idHead = 1, idTail = 1;
    int idRow, idColumn;
    int idMovement;

    struct cell NilFather, Q[(MAXH * MAXW) + 5], u, v, movements[5];

    assignMovements(movements);

    NilFather.coord_x = NIL;
    NilFather.coord_y = NIL;

    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            color[idRow][idColumn] = WHITE;
            d[idRow][idColumn] = myInfinite;
            pi[idRow][idColumn] = NilFather;
        }
    }

    color[s.coord_y][s.coord_x] = GRAY;
    d[s.coord_y][s.coord_x] = 0;
    pi[s.coord_y][s.coord_x] = NilFather;

    Q[idTail] = s;
    idTail++;

    while(idHead < idTail)
    {
        u = Q[idHead];
        idHead++;

        for(idMovement = 1; idMovement <= 4; idMovement++)
        {
            v.coord_x = u.coord_x + movements[idMovement].coord_x;
            v.coord_y = u.coord_y + movements[idMovement].coord_y;

            if((v.coord_x >= 1 && v.coord_x <= W) &&
               (v.coord_y >= 1 && v.coord_y <= H) &&
               (Maze[v.coord_y][v.coord_x] == '.') &&
               (color[v.coord_y][v.coord_x] == WHITE))
            {
                color[v.coord_y][v.coord_x] = GRAY;
                d[v.coord_y][v.coord_x] = d[u.coord_y][u.coord_x] + 1;
                pi[v.coord_y][v.coord_x] = u;

                Q[idTail] = v;
                idTail++;
            }
        }
        color[u.coord_y][u.coord_x] = BLACK;
    }
}


int DFS_Visit_Maze(int H, int W, struct cell U, int *time,
                   struct cell arrayMov[],
                   int currentRegionID)
{
    int idAdj;
    int celdasSize = 1;
    struct cell V;

    color[U.coord_y][U.coord_x] = GRAY;
    regionID[U.coord_y][U.coord_x] = currentRegionID;

    *time = *time + 1;
    d[U.coord_y][U.coord_x] = *time;

    for(idAdj = 1; idAdj <= 4; idAdj++)
    {
        V.coord_x = U.coord_x + arrayMov[idAdj].coord_x;
        V.coord_y = U.coord_y + arrayMov[idAdj].coord_y;

        if((V.coord_x >= 1) && (V.coord_x <= W) &&
           (V.coord_y >= 1) && (V.coord_y <= H) &&
           (color[V.coord_y][V.coord_x] == WHITE) &&
           (Maze[V.coord_y][V.coord_x] == '.'))
        {
            pi[V.coord_y][V.coord_x] = U;

            celdasSize += DFS_Visit_Maze(H, W, V, time,
                                         arrayMov, currentRegionID);
        }
    }

    color[U.coord_y][U.coord_x] = BLACK;
    *time = *time + 1;
    f[U.coord_y][U.coord_x] = *time;

    return celdasSize;
}


int solverBFS(int H, int W, int targetRegion,
              struct cell startCell)
{
    int i, j;

    BFS_Maze(W, H, startCell);

    struct cell farthest1 = startCell;
    int maxDist1 = 0;

    for(i = 1; i <= H; i++)
    {
        for(j = 1; j <= W; j++)
        {
            if(regionID[i][j] == targetRegion &&
               d[i][j] > maxDist1 &&
               d[i][j] != myInfinite)
            {
                maxDist1 = d[i][j];
                farthest1.coord_x = j;
                farthest1.coord_y = i;
            }
        }
    }

    BFS_Maze(W, H, farthest1);

    int maxDist2 = 0;

    for(i = 1; i <= H; i++)
    {
        for(j = 1; j <= W; j++)
        {
            if(regionID[i][j] == targetRegion &&
               d[i][j] > maxDist2 &&
               d[i][j] != myInfinite)
            {
                maxDist2 = d[i][j];
            }
        }
    }

    return maxDist2;
}


void DFS_Maze(int H, int W, int idCase)
{
    int idRow, idColumn;
    int time = 0;

    struct cell NILFather, U, arrayMov[5];

    NILFather.coord_x = NIL;
    NILFather.coord_y = NIL;

    assignMovements(arrayMov);

    for(idRow = 1; idRow <= H; idRow++)
        for(idColumn = 1; idColumn <= W; idColumn++)
            regionID[idRow][idColumn] = -1;

    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            color[idRow][idColumn] = WHITE;
            pi[idRow][idColumn] = NILFather;
            d[idRow][idColumn] = myInfinite;
            f[idRow][idColumn] = myInfinite;
        }
    }

    int numRegiones = 0;
    int maxSize = 0;
    int maxRegionID = -1;
    struct cell maxRegionStart;

    for(idRow = 1; idRow <= H; idRow++)
    {
        for(idColumn = 1; idColumn <= W; idColumn++)
        {
            U.coord_x = idColumn;
            U.coord_y = idRow;

            if((Maze[U.coord_y][U.coord_x] == '.') &&
               (color[U.coord_y][U.coord_x] == WHITE))
            {
                int size;

                numRegiones++;

                size = DFS_Visit_Maze(H, W, U, &time,
                                      arrayMov, numRegiones - 1);

                if(size > maxSize)
                {
                    maxSize = size;
                    maxRegionID = numRegiones - 1;
                    maxRegionStart = U;
                }
            }
        }
    }

    int D = 0;

    if(maxSize > 1)
        D = solverBFS(H, W, maxRegionID, maxRegionStart);

    printf("Case %d: %d %d %d\n", idCase, numRegiones, maxSize, D);
}

int main()
{
    int totalCases, idCase, H, W;

    scanf("%d", &totalCases);

    for(idCase = 1; idCase <= totalCases; idCase++)
    {
        scanf("%d %d", &H, &W);
        ReadMaze(H, W);
        DFS_Maze(H, W, idCase);
    }

    return 0;
}
