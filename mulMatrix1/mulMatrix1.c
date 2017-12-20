#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
using namespace std;

const int n = 5000;
int matrix[n][n], vector[n], multiplication_result[n]{};

void initializeMatrix() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 100;
		}
	}
}
int main() {
	srand(time(NULL));
	initializeMatrix();
	for (int i = 0; i < n; i++) {
		vector[i] = rand() % 100;
	}

	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&liStartTime);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			multiplication_result[i] += matrix[i][j] * vector[j];
		}
	}
	QueryPerformanceCounter(&liFinishTime);
	double dElapsedTime = 1000.0 * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("%f\n", dElapsedTime);
	system("pause");
	return 0;
}