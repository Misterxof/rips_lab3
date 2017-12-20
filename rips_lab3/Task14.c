#include <windows.h>
#include <process.h>
#include <stdio.h>
#define p 2 // ���������� �������� �������
int n = 1000000;
// ��� ���������, ������������� ������� ������
struct SThreadParam
{
	int k;
	double sum;
};
DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	DWORD dwStartTime = GetTickCount();
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

	DWORD dwEndTime = GetTickCount() - dwStartTime;
	printf("time = %d", dwEndTime);
	return 0;
}
int main()
{
	HANDLE hThreads[p]; // ������ ������������ �������
						// ������ ���������� ��������� �������
	struct SThreadParam params [2];
	int k;
	double sum;
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
	printf("PI = %.16f\n", sum);
	system("pause");
	return 0;
}