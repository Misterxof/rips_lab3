#include <windows.h>
#include <process.h>
#include <stdio.h>

int p = 2; // количество дочерних потоков
//int n = 10000000;
//int n = 100000000;
int n = 1000000000;
double pi = 0.; // требуется взаимоисключающий доступ
CRITICAL_SECTION cs;
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
	// монопольный доступ
	EnterCriticalSection(&cs);
	pi += h * sum;
	LeaveCriticalSection(&cs);
	return 0;
}
int main()
{
	HANDLE hThreads[2];
	int k;
	InitializeCriticalSection(&cs);

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
	// освобождение ресурсов, занятых критической секцией
	DeleteCriticalSection(&cs);

	QueryPerformanceCounter(&liFinishTime);
	double dElapsedTime = 1000.0 * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("%f\n", dElapsedTime);

	printf("PI = %.16f\n", pi);
	system("pause");

	return 0;
}