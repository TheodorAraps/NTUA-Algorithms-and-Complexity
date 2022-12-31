#include <stdio.h>
#include <set>

int main()
{
	int N, D = 10001;
	unsigned long Q, distances[1000], queries[10001];
	std::set<std::pair<unsigned long, int>> tuple_list;
	bool answers[10001];

	scanf("%d %lu", &N, &Q);

	for (unsigned long i = 0; i < 10001; i++)
	{
		queries[i] = -1;
	}

	queries[0] = 0;
	tuple_list.insert(std::make_pair(queries[0], 0));

	for (int i = 0; i < N; i++)
	{
		unsigned long dist;
		scanf("%lu", &dist);
		distances[i] = dist;
		if (dist < D)
			D = dist;
	}

	//we implement dijkstra's logic'
	while (!tuple_list.empty())
	{
		std::pair<unsigned long, int> head = *tuple_list.begin();
		int dist_sum = head.first;
		unsigned long currentv = head.second;
		tuple_list.erase(head);

		for (int i = 0; i < N; i++)
		{
			int new_cost = dist_sum + distances[i];
			int new_vetrice = (currentv + distances[i]) % D;
			if (new_cost < queries[new_vetrice] || queries[new_vetrice] == -1)
			{
				tuple_list.erase(std::make_pair(queries[new_vetrice], new_vetrice));
				queries[new_vetrice] = new_cost;
				tuple_list.insert(std::make_pair(queries[new_vetrice], new_vetrice));
			}
		}
	}

	for (int i = 0; i < Q; i++)
	{
		unsigned long query;
		scanf("%lu", &query);
		answers[i] = queries[query % D] > query ? 0 : 1;
	}

	for (int i = 0; i < Q; i++)
	{
		answers[i] ? printf("YES\n") : printf("NO\n");
	}
}