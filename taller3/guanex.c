#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# define myNegativeInfinite -9223372036854775807
# define myPositiveInfinite 9223372036854775807
#define MAXT 1000000

int Parent ( int i)
{
return i / 2;
}
int Left (int i)
{
return 2 * i;
}
int Right ( int i)
{
return 2 * i + 1;
}
void MinHeapify ( long long Q[] , int i, int heapSize )
{
int l, r, least ;
long long temp ;
l = Left (i);
r = Right (i);
if ((l <= heapSize ) && (Q[l] < Q[i]) )
least = l;
else
least = i;
if ((r <= heapSize ) && (Q[r] < Q[ least ]) )
least = r;
if( least != i)
{
temp = Q[i];
Q[i] = Q[ least ];
Q[ least ] = temp ;
MinHeapify (Q, least , heapSize );
}
}
long long MinPQ_Minimum ( long long Q [], int heapSize )
{
if(heapSize < 1)
return myNegativeInfinite;
return Q [1];
}
long long MinPQ_Extract ( long long Q[] , int * heapSize )
{
long long min = myNegativeInfinite ;
if (* heapSize < 1)
return myNegativeInfinite;
else
{
min = Q [1];
Q [1] = Q[* heapSize ];
(* heapSize ) --;
MinHeapify (Q, 1, * heapSize );
}
return min ;
}
void MinPQ_DecreaseKey ( long long Q[] , int i, long long key )
{
long long temp ;
if( key > Q[i])
return;
else
{
Q[i] = key ;
while ((i > 1) && (Q[ Parent (i)] > Q[i]) )
{
temp = Q[i];
Q[i] = Q[ Parent (i) ];
Q[ Parent (i)] = temp ;
i = Parent (i);
}
}
}
void MinPQ_Insert (long long Q[] , long long key , int * heapSize )
{
if(*heapSize >= MAXT) return;
(* heapSize ) ++;
Q[* heapSize ] = key ;
int i = *heapSize;
long long temp;
while ((i > 1) && (Q[ Parent (i)] > Q[i]) )
{
temp = Q[i];
Q[i] = Q[ Parent (i) ];
Q[ Parent (i)] = temp ;
i = Parent (i);
}
}
int main ()
{
int n, operation , heapSize = 0;
long long element , Q[ MAXT + 1] ;
scanf("%d", &n);
for(int i = 0; i < n; i++)
{
scanf("%d", &operation);
if( operation == 1)
{
scanf (" %lld", & element );
MinPQ_Insert (Q, element , & heapSize );
}
else if( operation == 2)
{
MinPQ_Extract (Q, & heapSize );
}
else if( operation == 3)
{
long long min = MinPQ_Minimum(Q, heapSize);
if(min == myNegativeInfinite)
printf("Empty!\n");
else
printf("%lld\n", min);
}
}
return 0;
}
