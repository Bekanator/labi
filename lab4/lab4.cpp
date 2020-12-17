#include <iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION CrS;
LONG arr[5];

void thread01()
{
	while (true)
	{
		EnterCriticalSection(&CrS);
		for (int i = 0; i < 6; i++)
			arr[i] = -150 + rand() % 300;
		LeaveCriticalSection(&CrS);
	}
}

void thread02()
{
	while (true)
	{
		Sleep(1000);
		EnterCriticalSection(&CrS);
		for (int i = 0; i < 6; i++)
		{
			if (arr[i] > 100)
				arr[i] = 0;
			cout << arr[i] << "  ";
		}
		cout << endl;
		LeaveCriticalSection(&CrS);
	}
}

int main()
{
	InitializeCriticalSection(&CrS);
	HANDLE hTh01;
	DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, &IDTh01);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02;
	DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, &IDTh02);
	if (hTh02 == NULL) return GetLastError();

	cin.get();

	DeleteCriticalSection(&CrS);

	TerminateThread(hTh01, 0);
	CloseHandle(hTh01);

	TerminateThread(hTh02, 0);
	CloseHandle(hTh02);
	 
	return 0;
}