#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace std;
#define p 2
const int n = 10000;
//const int n = 15000;
//const int n = 20000;
int matrix[n][n], vector[n], multiplication_result[n]{};
int len;
void initializeMatrix() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 100;
		}
	}
}

unsigned int WINAPI ThreadFunction(LPVOID pvParam) {
	int nParam = (int)pvParam;
	int i, j, start;
	start = nParam;
	int end = min(start + len, n);
	for (i = start; i < end; i++) {
		for (j = 0; j < n; j++) {
			multiplication_result[i] += matrix[i][j] * vector[j];
		}
	}

	return 0;
}

int main() {
	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	QueryPerformanceFrequency(&liFrequency); // получаем частоту
	HANDLE hThreads[p];
	int k;
	len = n / p + n % p;
	srand(time(NULL));
	initializeMatrix();
	for (int i = 0; i < n; i++) {
		vector[i] = rand() % 100;
	}
	QueryPerformanceCounter(&liStartTime); // получаем стартовое время

	for (k = 0; k < p; k++)
	{
		hThreads[k] = (HANDLE)_beginthreadex(NULL, 0,
			ThreadFunction, (LPVOID)(k * len), 0, NULL);
		if (hThreads[k] == NULL) 
		{
			printf("Create Thread %d Error=%d\n", k, GetLastError());
			return -1;
		}
	}
	WaitForMultipleObjects(p, hThreads, TRUE, INFINITE);
	QueryPerformanceCounter(&liFinishTime); // получаем финишное время
	for (k = 0; k < p; ++k)
		CloseHandle(hThreads[k]);
	double dElapsedTime = 1000.0 * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("%f\n", dElapsedTime);
	//printResult();
	system("pause");
	return 0;
}