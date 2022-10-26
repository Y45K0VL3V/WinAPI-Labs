#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>

#include "..\\MemoryReplacer\\MemoryReplacer.h"
#pragma comment(lib, "..\\x64\\Debug\\MemoryReplacer.lib")

using namespace std;

typedef int Func(const char*, const char*);

const int n = 3;

void main()
{
	string strings[n] = {
	"Some info ...",
	"Login Password",
	"Authorization.",
	};

	for (int i = 0; i < n; ++i)
		cout << strings[i].c_str() << endl;

	Replace(strings[2].c_str(), "Some replace value!!!");

	for (int i = 0; i < n; i++)
		cout << strings[i].c_str() << endl;

	//dll test's

	HMODULE dll = 0;
	if ((dll = LoadLibrary(L"MemoryReplacer"))) {
		Func* _Replace;
		_Replace = (Func*)GetProcAddress(dll, "Replace");
		
		Replace(strings[1].c_str(), "Some replace value!!!");
		for (int i = 0; i < n; i++)
			cout << strings[i].c_str() << endl;

		FreeLibrary(dll);
	}
	else
		cout << "Cant load Dll\n";


	//dll injection
	cout << "Enter PID of the process: " << endl;
	DWORD pid;
	std::cin >> pid;

	HANDLE hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hRemoteProcess != NULL)
	{
		cout << "\nPID finded" << endl;

		LPVOID threadFunction = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");

		string argument("InjectionDll.dll");

		LPVOID argumentAddress = VirtualAllocEx(hRemoteProcess, NULL, argument.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hRemoteProcess, (LPVOID)argumentAddress, argument.c_str(), argument.length() + 1, NULL);

		if (CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)threadFunction, (LPVOID)argumentAddress, 0, NULL))
		{
			cout << "Creating thread" << endl;
			CloseHandle(hRemoteProcess);
		}
		else
			cout << "Cant create thread" << endl;


	}
	else
		cout << "Cant find PID" << endl;

}