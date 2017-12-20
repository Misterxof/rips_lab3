#include <windows.h>
#include <process.h>
#include <stdio.h>
#define p 2 // ���������� �������� �������
//int n = 10000000;
//int n = 100000000;
int n = 1000000000;
// ��� ���������, ������������� ������� ������
struct SThreadParam
{
	int k;
	double sum;
};
DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	struct SThreadParam* param = (struct SThreadParam*)pvParam;
	int i, start;
	double h, sum, x;
	h = 1. / n;
	sum = 0.;
	start = param->k;
	for (i = start; i<n; i += p)
	{
		x = h * i;
		sum += 4. / (1. + x*x);
	}
	// � ���������� ���������� �� ������� ����� ����������
	param->sum = h * sum;
	return 0;
}
int main()
{
	HANDLE hThreads[p]; // ������ ������������ �������
						// ������ ���������� ��������� �������
	struct SThreadParam params[2];
	int k;
	double sum;

	LARGE_INTEGER liFrequency, liStartTime, liFinishTime;
	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&liStartTime);
	// �������� �������� �������
	for (k = 0; k<p; ++k)
	{
		params[k].k = k;
		hThreads[k] = (HANDLE)_beginthreadex(NULL, 0,
			ThreadFunction, (LPVOID)&(params[k]), 0, NULL);
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
	sum = 0.;
	for (k = 0; k<p; ++k)
		sum += params[k].sum;

	QueryPerformanceCounter(&liFinishTime);
	double dElapsedTime = 1000.0 * (liFinishTime.QuadPart - liStartTime.QuadPart) / liFrequency.QuadPart;
	printf("%f\n", dElapsedTime);

	printf("PI = %.16f\n", sum);
	system("pause");
	return 0;
}