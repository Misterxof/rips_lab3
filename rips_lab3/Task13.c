/*#include <windows.h>
#include <process.h>
#include <stdio.h>
#define p 2 // количество дочерних потоков
double pi[p];
int n = 1000000;
DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	DWORD dwStartTime = GetTickCount();
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
	DWORD dwEndTime = GetTickCount() - dwStartTime;
	printf("time = %d", dwEndTime);

	return 0;

}
int main()
{
	HANDLE hThreads[p];
	int k;
	double sum;
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
	printf("PI = %.16f\n", sum);
	return 0;
}*/