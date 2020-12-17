#include <iostream>
#include <typeinfo>
#include <windows.h>
using namespace std;

char tmp_str[100];

struct plane {
	int flight_number;
	char flight_time[12];
	char flight_region[12];
};


int menu();
void CreateNewFile(HANDLE&);
void WriteToFile(HANDLE&, DWORD);
plane ReadFromFile(HANDLE&);
plane ReadFromSource(HANDLE&);
void DumpFile(HANDLE&);
int main()
{
	HANDLE myFile = NULL;
	DWORD n = NULL;
	while (true) {
		switch (menu()) {
		case 1:CreateNewFile(myFile); system("cls"); break;
		case 2:WriteToFile(myFile, n); system("cls"); break;
		case 3:ReadFromFile(myFile); break;
		case 4:DumpFile(myFile); break;
		case 5:ReadFromSource(myFile); break;
		case 6:CloseHandle(myFile); system("cls"); return 1;
		default: break;
		}
	}
	system("cls");
}


int menu() {
	cout << "Choose ur Destiny!" << endl;
	cout << "1 - Open/create file" << endl;
	cout << "2 - Write information in ur book" << endl;
	cout << "3 - Read information from ur book" << endl;
	cout << "4 - Dump to the new file" << endl;
	cout << "5 - Read from source File" << endl;
	cout << "6 - Get Out" << endl;
	int n; cout << "Destiny: ";  cin >> n;
	return n;
}

void CreateNewFile(HANDLE& myFile) {
	LPCWSTR filename = L"Source_Planes.txt";
	myFile = CreateFile(
		filename, GENERIC_READ | GENERIC_WRITE,
		NULL,
		NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (myFile == INVALID_HANDLE_VALUE) {
		cout << "Error" << endl;
		CloseHandle(myFile);
	}
}


void WriteToFile(HANDLE& myFile, DWORD n) {
	plane flight_1;
	cout << "Enter ur Flight number: "; cin >> flight_1.flight_number;
	cout << "Enter ur Flight region: "; cin >> flight_1.flight_region;
	cout << "Enter ur Flight time: "; cin >> flight_1.flight_time;
	string s = flight_1.flight_time;
	system("pause");
	WriteFile(myFile, &flight_1, sizeof(flight_1), &n, NULL);
}

plane ReadFromSource(HANDLE& myFile) {
	system("cls");
	SetFilePointer(myFile, 0, 0, FILE_BEGIN);
	plane tmp_struct;
	DWORD n;
	while (ReadFile(myFile, &tmp_struct, sizeof(tmp_struct), &n, NULL) && n != 0)
		cout << tmp_struct.flight_number << " " << tmp_struct.flight_time << " " << tmp_struct.flight_region << endl;
	system("pause");
	system("cls");
	return tmp_struct;
}


plane ReadFromFile(HANDLE& myFile) {
	system("cls");
	string scin;
	cout << "Enter ur Destination Point: ";
	cin >> tmp_str;
	SetFilePointer(myFile, 0, 0, FILE_BEGIN);
	plane tmp_struct;
	DWORD n;
	while (ReadFile(myFile, &tmp_struct, sizeof(tmp_struct), &n, NULL) && n != 0) {
		if (!strcmp(tmp_struct.flight_region, tmp_str)) {
			cout << tmp_struct.flight_number << " " << tmp_struct.flight_time << endl;
		}
	}
	system("pause");
	system("cls");
	return tmp_struct;
}


void DumpFile(HANDLE& myFile) {
	DWORD tmp_byte = NULL;
	LPCWSTR tmp_filename = L"Planes_Sorted.txt";
	HANDLE tmpFile = CreateFile(
		tmp_filename, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	plane tmp_struct;
	DWORD n;
	while (ReadFile(myFile, &tmp_struct, sizeof(tmp_struct), &n, NULL) && n != 0) {
		if (!strcmp(tmp_struct.flight_region, tmp_str)) {
			WriteFile(tmpFile, &tmp_struct, sizeof(tmp_struct), &tmp_byte, NULL);
		}
	}
	system("cls");
}