#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>

#include "..\\MemoryReplacer\\MemoryReplacer.h"
#pragma comment(lib, "..\\x64\\Debug\\MemoryReplacer.lib")

using namespace std;

typedef int Func();

const int n = 3;

typedef struct ReplacementParams
{
	char data[256];
	char replacement[256];
} ReplacementParams;

void main()
{
	string strings[n] = {
	"Some info ...",
	"Login Password",
	"Authorization.",
	};

	for (int i = 0; i < n; ++i)
		cout << strings[i] << endl;

	params parameters =
	{
		"Login Password",
		"Some replace!!!"
	};

	Replace(&parameters);

	for (int i = 0; i < n; i++)
		cout << strings[i] << endl;

	parameters =
	{
		"Authorization.",
		"short!"
	};

	HMODULE dll = 0;
	if ((dll = LoadLibrary(L"MemoryReplacer"))) {
		Func* _Replace;
		_Replace = (Func*)GetProcAddress(dll, "Replace");
		
		Replace(&parameters);
		for (int i = 0; i < n; i++)
			cout << strings[i] << endl;

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

		string argument("MemoryReplacer.dll");

		LPVOID argumentAddress = VirtualAllocEx(hRemoteProcess, NULL, 30, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hRemoteProcess, (LPVOID)argumentAddress, argument.c_str(), argument.length() + 1, NULL);
		HANDLE thread = CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)threadFunction, (LPVOID)argumentAddress, 0, NULL);
		if (thread)
		{
			WaitForSingleObject(thread, INFINITE);
			CloseHandle(thread);

		}
		else
			cout << "Can't create thread" << endl;

		LPVOID replacerFunction = (LPVOID)GetProcAddress(LoadLibraryA("MemoryReplacer.dll"), "Replace");
		ReplacementParams replacementParamsArgument =
		{
			"Work123123",
			"Hello!"
		};

		argumentAddress = VirtualAllocEx(hRemoteProcess, NULL, sizeof(replacementParamsArgument)+10, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hRemoteProcess, (LPVOID)argumentAddress, &replacementParamsArgument, sizeof(replacementParamsArgument), NULL);
		thread = CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)replacerFunction, (LPVOID)argumentAddress, 0, NULL);
		if (thread)
		{
			WaitForSingleObject(thread, INFINITE);
			CloseHandle(thread);

		}
		else
			cout << "Can't create thread" << endl;

		CloseHandle(hRemoteProcess);
	}
	else
		cout << "Cant find PID" << endl;

}