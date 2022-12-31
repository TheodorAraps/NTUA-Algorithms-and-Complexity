#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
//offer structure
struct offer 
{
	int number;
	int cost;
};

int main()
{
	int N, M, answer = -1;
	char type[2];
	scanf("%d %d", &N, &M);
	struct offer temp;
	// save input in a vector base on the type of the product offered
	std::vector<offer> A1, A2, A3, B1, B2, B3, C1, C2, C3;
	
	for (int i = 0; i < M; i++)
	{
		scanf("%s %d %d", &type, &temp.number, &temp.cost);
		switch (type[0])
		{
			case '1':
				switch (type[1])
				{
					case 'A':
						A1.push_back(temp);
						break;
					case 'B':
						B1.push_back(temp);
						break;
					case 'C':
						C1.push_back(temp);
						break;
				}
				break;
			case '2':
				switch (type[1])
				{
					case 'A':
						A2.push_back(temp);
						break;
					case 'B':
						B2.push_back(temp);
						break;
					case 'C':
						C2.push_back(temp);
						break;
				}
				break;
			case '3':
				switch (type[1])
				{
					case 'A':
						A3.push_back(temp);
						break;
					case 'B':
						B3.push_back(temp);
						break;
					case 'C':
						C3.push_back(temp);
						break;
				}
				break;
		}
	}
	// for (auto i = 0; i < A1.size(); i++)
	// 	printf("%d %d\n", A1[i].number, A1[i].cost);
}