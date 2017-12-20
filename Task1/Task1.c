#include <Windows.h>
#include <process.h>
#include <stdio.h>

//int n = 10000000;
//int n = 100000000;
int n = 1000000000;

int main() {
	
	int i, start;
	double h, sum, x;
	h = 1. / n;
	sum = 0.;
	start = 0;

	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&liStartTime);

	for (i = start; i < n; i++) {
		x = h * i;
		sum += 4. / (1. + x * x);
	}
	double pi = h * sum;

	QueryPerformanceCounter(&liFinishTime);
	double dElapsedTime = 1000.0 * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("%f\n", dElapsedTime);

	printf("Pi = = %.16f\n", pi);
	system("pause");
	return 0;
}