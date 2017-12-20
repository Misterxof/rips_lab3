#include <windows.h>
#include <process.h>
#include <stdio.h>

#define p 2 // количество дочерних потоков
double pi[p];
//int n = 10000000;
//int n = 100000000;
int n = 1000000000;

DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	int nParam = (int)pvParam;
	int i, start;
	double h, sum, x;
	h = 1. / n;
	sum = 0.;
	start = nParam;
	for (i = start; i<n; i += p)
	{
		x = h * i;
		sum += 4. / (1. + x*x);
	}
	pi[nParam] = h * sum;

	return 0;

}

int main()
{
	HANDLE hThreads[p];
	int k;
	double sum;

	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&liStartTime);

	// создание дочерних потоков
	for (k = 0; k<p; ++k)
	{
		hThreads[k] = (HANDLE)_beginthreadex(NULL, 0,
			ThreadFunction, (LPVOID)k, 0, NULL);
		if (hThreads[k] == NULL) // обработка ошибки
		{
			printf("Create Thread %d Error=%d\n", k, GetLastError());
			return -1;
		}
	}
	// ожидание завершения дочерних потоков
	WaitForMultipleObjects(p, hThreads, TRUE, INFINITE);
	for (k = 0; k<p; ++k)
		CloseHandle(hThreads[k]);
	sum = 0.;
	for (k = 0; k<p; ++k)
		sum += pi[k];

	QueryPerformanceCounter(&liFinishTime);
	double dElapsedTime = 1000.0 * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("%f\n", dElapsedTime);

	printf("PI = %.16f\n", sum);
	system("pause");
	return 0;
}