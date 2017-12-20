#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <ctime>

#define EXECUTIONS_NUMBER 100

int main()
{
	int n;
	time_t startTime, endTime;

	int operationCount[4] = { 1000, 3000, 5000, 10000 };

	for (int k = 0; k < 4; k++)
	{
		srand(time(0));
		n = operationCount[k];
		double ** matrix = new double*[n];
		double * vector = new double[n];
		double * result = new double[n];

		for (int i = 0; i < n; i++)
		{
			matrix[i] = new double[n];
			result[i] = 0;

			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = rand() % 100 + 1;
			}
		}

		for (int i = 0; i < n; i++)
		{
			vector[i] = rand() % 100 + 1;
		}

		startTime = clock();

		for (int d = 0; d < EXECUTIONS_NUMBER; d++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					result[i] += matrix[i][j] * vector[j];
				}
			}
		}

		endTime = clock();

		printf("n = %d; Ticks: %d\n", n, endTime - startTime);
		printf("Time: %lf\n\n", ((endTime - startTime) / (double)CLOCKS_PER_SEC / (double)EXECUTIONS_NUMBER));

		delete[] result;
		delete[] vector;

		for (int i = 0; i < n; i++)
		{
			delete[] matrix[i];
		}

		delete[] matrix;
	}
	return 0;
}
