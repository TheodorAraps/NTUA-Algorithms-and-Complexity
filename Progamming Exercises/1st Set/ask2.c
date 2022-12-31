#include <stdio.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

int main()
{
	int N, K;
	scanf("%i %i", &N, &K);
	int p[N], Ksum_lengths[K], sum = 0, min_length = N + 1;
	for (int i = 0; i < N; i++)
	{
		scanf("%i", &p[i]);
		if (p[i] == K)
		{
			printf("1\n");
			return 0;
		}
	}

	//initialisation of Ksum_lengths[K] array, which will hold the lowest length found so far at the right side of y, 
	//with sum equal to the index
	for (int i = 0; i < K; i++)
	{
		Ksum_lengths[i] = 0;
	}
	Ksum_lengths[p[N - 1]] = 1;
	//traverse p[N] backwards
	for (int y = N - 2; y >= 0; y--) //O(N)
	{
		sum = p[y];
		int x = y - 1;
		if (x == y - 1 && sum > 0 && Ksum_lengths[K - sum] > 0)
		{
			min_length = min(min_length, Ksum_lengths[K - sum] + 1);
		}
		//we compare current min with the total length of all the subbarrays (with total sum equal to S) at left side of index y
		//with the minimum length of the subbarray (with total sum equal to K-S) found so far at the right side of index y
		while (x >= 0 && sum + p[x] <= K) //O(N)
		{
			//update minimum length found
			sum += p[x];
			if (sum == K)
			{
				min_length = min(min_length, y - x + 1);
			}
			else if (sum > 0 && Ksum_lengths[K - sum] > 0)
			{
				min_length = min(min_length, Ksum_lengths[K - sum] + y - x + 1);
			}
			x--;
		}
		//update Ksum_lengths for the next y
		int ysum = 0, i = y;
		while (i < N && ysum + p[i] < K) //O(N)
		{
			ysum += p[i];
			if (i - y + 1 < Ksum_lengths[ysum] || Ksum_lengths[ysum] == 0)
			{
				Ksum_lengths[ysum] = i - y + 1;
			}
			i++;
		}
	}
	if (min_length == N + 1) printf("-1\n");
	else printf("%d\n", min_length);
	//total complexity: O(N*(N+N)) = O(N^2)
	return 0;
}