#include <stdio.h>
#include <stdlib.h>

//function based on which we will sort c_sort[N][2]
int cmp1(const void *a, const void *b)
{
	const int * const ia = a, *const ib = b;
	return ia[0] < ib[0] ? -1 : ia[0] > ib[0];
}
//function based on which we will sort portals[M][3]
int cmp2(const void *a, const void *b)
{
	const int * const ia = a, *const ib = b;
	return ia[2] > ib[2] ? -1 : ia[2] < ib[2];
}
//find method (with compression)
int find(int u, int* parent)
{
	if (u == parent[u - 1])
		return u;
	return parent[u - 1] = find(parent[u - 1], parent);
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
//union method (by rank)
void union_univ(int a, int b, int* parent, int* rank)
{
	a = find(a, parent);
	b = find(b, parent);
	if (a != b)
	{
		if (rank[a - 1] < rank[b - 1])
		{
			swap(&a, &b);
		}
		parent[b - 1] = a;
		if (rank[a - 1] == rank[b - 1])
		{
			rank[a - 1]++;
		}
	}
}
//check if the last unified universes have a Morty that belongs to the other universe
void check_connection(int* check, int port1, int port2, int c1, int c2)
{
	if (c1 == port2)
	{
		check[port2 - 1] = 0;
	}
	if (c2 == port1)
	{
		check[port1 - 1] = 0;
	}
}

int main()
{
	int N, M;
	scanf("%i %i", &N, &M);
	int c[N], c_sort[N][2], portals[M][3], parent[N], rank[N], check[N], iter = 0;
	//with c_sort we will check if there is a path connecting the universe i with the universe in which Morty of i is
	for (int i = 0; i < N; i++)
	{
		scanf("%i", &c[i]);
		c_sort[i][1] = i + 1;
		c_sort[i][0] = c[i];
		//check all Morties that are not in the right universe
		if (c[i] != i + 1)
		{
			check[i] = 1;
		}
		else
			check[i] = 0;
		//parent node intiallization
		parent[i] = i + 1;
		rank[i] = 0;
	}
	for (int i = 0; i < M; i++)
	{
		scanf("%i %i %i", &portals[i][0], &portals[i][1], &portals[i][2]);
	}
	qsort(c_sort, sizeof c_sort / sizeof *c_sort, sizeof *c_sort, cmp1);
	qsort(portals, sizeof portals / sizeof *portals, sizeof *portals, cmp2);
	//check portals from biggest width to lowest
	for (int u = 0; u < M; u++)
	{
		//find next universe that doesn't have the right Morty
		while (iter < N && check[iter] == 0)
		{
			iter++;
		}
		if (iter < N && find(iter + 1, parent) == find(c_sort[iter][1], parent))
		{
			check[iter] = 0;
			u--;
			continue;
		}
		//if iter == N it means every Morty can return to his universe
		if (iter == N)
		{
			printf("%d\n", portals[u - 1][2]);
			return 0;
		}
		if (check[portals[u][0] - 1] == 1 || check[portals[u][1] - 1] == 1)
		{
			check_connection(check, portals[u][0], portals[u][1], c[portals[u][0] - 1], c[portals[u][1] - 1]);
		}
		union_univ(portals[u][0], portals[u][1], parent, rank);
	}
	printf("%d\n", portals[M - 1][2]);
	return 0;
}