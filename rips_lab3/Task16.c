/*#include <windows.h>
#include <process.h>
#include <stdio.h>
int p = 2; // ���������� �������� �������
int n = 1000000;
double pi = 0.; // ��������� ����������������� ������
CRITICAL_SECTION cs;
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
	// ����������� ������
	EnterCriticalSection(&cs);
	pi += h * sum;
	LeaveCriticalSection(&cs);
	DWORD dwEndTime = GetTickCount() - dwStartTime;
	printf("time3 = %d", dwEndTime);
	return 0;
}
int main()
{
	HANDLE hThreads [2];
	int k;
	InitializeCriticalSection(&cs);
	// �������� �������� �������
	for (k = 0; k<p; ++k)
	{
		hThreads[k] = (HANDLE)_beginthreadex(NULL, 0,
			ThreadFunction, (LPVOID)k, 0, NULL);
		if (hThreads[k] == NULL) // ��������� ������
		{
			printf("Create Thread %d Error=%d\n", k, GetLastError());
			return -1;
		}
	}
	// �������� ���������� �������� �������
	WaitForMultipleObjects(p, hThreads, TRUE, INFINITE);
	for (k = 0; k<p; ++k)
		CloseHandle(hThreads[k]);
	// ������������ ��������, ������� ����������� �������
	DeleteCriticalSection(&cs);
	printf("PI = %.16f\n", pi);
	system("pause");

	return 0;
}*/