#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// binary search for LIS
int bin_search_lis(int *aux, int hi, int value)
{
	int lo = -1;
	while (hi - lo > 1)
	{
		int mid = lo + (hi - lo) / 2;
		if (aux[mid] >= value)
			hi = mid;
		else
			lo = mid;
	}

	return hi;
}

// binary search for LDS
int bin_search_lds(int *aux, int hi, int value)
{
	int lo = -1;
	while (hi - lo > 1)
	{
		int mid = lo + (hi - lo) / 2;
		if (aux[mid] <= value)
			hi = mid;
		else
			lo = mid;
	}

	return hi;
}

int main()
{
	int N, K;
	scanf("%d %d", &N, &K);
	/* auxlis, auxlds: auxilary arrays to keep the last element of all possible increasing/decreasing
	/* subsequences found so far, of length equal to the corresponding index
	/* lis_sf, lds_sf: lis, lds found So Far */
	/* lis_ii, lds_ii: lis, lds Including Index value (p[i]) */
	int p[N], auxlis[N + 1], auxlds[N + 1], lis_sf[N + 1][2], lds_sf[N + 1][2], lis_ii[N], lds_ii[N], length = 1;

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &p[i]);
		auxlis[i] = 0;
		auxlds[i] = 0;
	}

	// Least Increasing Subsequence O(NlogN)
	auxlis[0] = p[0];
	for (int i = 0; i < N; i++)
	{
		// if value is smaller than every other value found so far, start a new subsequence with length 1
		if (p[i] < auxlis[0])
		{
			auxlis[0] = p[i];
			lis_ii[i] = 1;
		}
		// extend largest subsequence
		else if (p[i] > auxlis[length - 1])
		{
			auxlis[length++] = p[i];
			lis_ii[i] = length;
		}
		// replace old end point with new end point of smaller value and with same length
		else
		{
			int index = bin_search_lis(auxlis, length - 1, p[i]);
			auxlis[index] = p[i];
			lis_ii[i] = index + 1;
		}

		lis_sf[i][0] = auxlis[length - 1];
		lis_sf[i][1] = length;
	}

	// Least Decreasing Subsequence O(NlogN)
	length = 1;
	auxlds[0] = p[N - 1] + K;
	for (int i = N - 1; i >= 0; i--)
	{
		// if value is larger than every other value found so far, start a new subsequence with length 1
		if (p[i] + K > auxlds[0])
		{
			auxlds[0] = p[i] + K;
			lds_ii[i] = 1;
		}
		// extend largest subsequence
		else if (p[i] + K < auxlds[length - 1])
		{
			auxlds[length++] = p[i] + K;
			lds_ii[i] = length;
		}
		// replace old end point with new end point of larger value and with same length
		else
		{
			int index = bin_search_lds(auxlds, length - 1, p[i] + K);
			auxlds[index] = p[i] + K;
			lds_ii[i] = index + 1;
		}

		lds_sf[i][0] = auxlds[length - 1];
		lds_sf[i][1] = length;
	}

	int answer = MAX(lis_sf[N - 1][1], lds_sf[N - 1][1]);
	for (int i = 0; i < N - 1; i++)
	{
		//compare best found so far
		if (lds_sf[i + 1][0] > lis_sf[i][0])
			answer = MAX(lis_sf[i][1] + lds_sf[i + 1][1], answer);
		//compare best with end point p[i]
		if (p[i + 1] + K > p[i])
			answer = MAX(lis_ii[i] + lds_ii[i + 1], answer);
	}
	printf("%d\n", answer);
}