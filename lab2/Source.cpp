#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
using namespace std;

struct plane
{
	int flight_number;
	char flight_time[12];
	char flight_region[12];
}buf;

int main()
{
	DWORD bytesWritten;
	setlocale(LC_ALL, "rus");
	LPCWSTR filename = L"D:\/ÑppProjects/Lab1/Lab1/Lab1/Source_Planes.txt";
	HANDLE handle = CreateFile(filename, GENERIC_READ, NULL, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	while (ReadFile(handle, &buf, sizeof(buf), &bytesWritten, NULL) && bytesWritten != 0)
	{
		cout << buf.flight_number << endl << buf.flight_time << endl << buf.flight_region << endl;
		cout << "---------end of struct\n\n";
	}
	cout << "Ââåäèòå íîìåð ñòðóêòóðû, êîòîðóþ õîòèòå èçìåíèòü: ";
	int number;
	cin >> number;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	char appName[60] = "D:\/ÑppProjects/Daughter/Debug/Daughter.exe ";
	char* arg = new char[3];
	strcat((char*)appName, _itoa(number, arg, 10));
	CloseHandle(handle);
	if (!CreateProcess(NULL,
		(LPWSTR)"D:\/ÑppProjects/Daughter/Debug/Daughter.exe ",
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)){
		cout << "Oøèáêà çàïóñêà ïðîöåññà" << endl;
	};
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}