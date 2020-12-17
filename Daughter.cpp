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

int main(int argc, char* argv[])
{
	DWORD bytesWritten;
	setlocale(LC_ALL, "rus");
	cout << "Будет редактировать запись номер " << argv[1] << endl;
	HANDLE handle = CreateFile(L"D:\/СppProjects/Lab1/Lab1/Lab1/Source_Planes.txt", GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	SetFilePointer(handle, sizeof(buf) * (atoi(argv[1])), NULL, FILE_BEGIN);
	cout << "введите новый номер: ";
	cin >> buf.flight_number;
	cout << "введите новое время: ";
	cin >> buf.flight_time;
	cin.ignore();
	cout << "введите новый регион: ";
	cin >> buf.flight_region;
	cin.ignore();
	WriteFile(handle, &buf, sizeof(buf), &bytesWritten, 0);
	CloseHandle(handle);
}