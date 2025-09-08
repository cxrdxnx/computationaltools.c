#include <iostream>
#include <math.h>
#include <vector>

const int INFINITE {2147483647};
const int MAXN {1000};

void merge(std::vector<int> A, int p, int q, int r)
{
	int i{};
	int j{};
	int k{};
	int n1 = q - p;
	int n2 = r - q;
	
	std::vector<int> L[n1 + 2];
	std::vector<int> R[n2 + 2];
	
	for(int i = 1; i <= n1; ++i)
	{
		L[i].push_back(A[p + i - 1]);
	}
	for(int j = 1; j <= n2; ++j)
	{
		R[j].push_back(A[q + j]);
	}
	L[n1 + 1] = INFINITE;
	R[n2 + 1] = INFINITE;
	i = 1;
	j = 1;
	for(int k = p; k <= r; ++k)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i += 1;
		}
		else
		{
			A[k] = R[i];
			j += 1;
		}
	}
}	

int main()
{
	;
}
