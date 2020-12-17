#include <iostream>
#include <windows.h>
#include "time.h"
using namespace std;



DWORD WINAPI thread1_F(LPVOID mass)
{
	HANDLE thread_mutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	WaitForSingleObject(thread_mutex, INFINITE);
	cout << "загрузился поток 1" << endl;
	srand(time(0));
	Sleep(1000);
	for (int i = 0; i < 10; i++)
	{
		*((int*)mass + i) = rand() % 200;
	}

	cout << "исходный массив: ";

	for (int i = 0; i < 10; i++)
	{
		cout << *((int*)mass + i) << "  ";
	}
	cout << endl;
	ReleaseMutex(thread_mutex);
	return 1;
}


DWORD WINAPI thread2_F(LPVOID mass)
{
	HANDLE thread_mutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	cout << "загрузился поток 2" << endl;
	WaitForSingleObject(thread_mutex, INFINITE);
	for (int i = 0; i < 10; i++) {
		if (*((int*)mass+i) > 100)
		{
			*((int*)mass + i) = 0;
		}
	}

	cout << "измененный массив: ";

	for (int i = 0; i < 10; i++)
	{
		cout << *((int*)mass + i) << "  ";
	}
	cout << endl << endl;
	ReleaseMutex(thread_mutex);
	return 1;
}


int main()
{
	HANDLE Mutex;
	setlocale(LC_ALL, "rus");
	int mass[10];
	Mutex = CreateMutex(NULL, FALSE, L"Mutex");
	HANDLE thread1 = CreateThread(NULL, 0, thread1_F, (void*)mass, NULL, 0);
	HANDLE thread2 = CreateThread(NULL, 0, thread2_F, (void*)mass, NULL, 0);
	HANDLE Threads[2] = { thread1, thread2 };
	WaitForMultipleObjects(2, Threads, TRUE, INFINITE);
	CloseHandle(Mutex);
	for (int i = 0; i < 2; i++)
	{
		CloseHandle(Threads[i]);
	}
	return 1;
}