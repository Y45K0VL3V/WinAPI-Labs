#include "pch.h"
#include "MemoryReplacer.h"
#include <Windows.h>
#include <iostream>

void Replace(params* params)
{
	HANDLE hProcess = GetCurrentProcess();
	if (hProcess)
	{
		size_t len = strlen(params->data);
		size_t replacementLength = strlen(params->replacement);
		SYSTEM_INFO si;
		MEMORY_BASIC_INFORMATION info;
		GetSystemInfo(&si);
		char* p = 0;
		SIZE_T lpRead = 0;
		while (p < si.lpMaximumApplicationAddress)
		{
			if (VirtualQueryEx(hProcess, p, &info, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION))
			{
				if ((info.State == MEM_COMMIT) && info.AllocationProtect == PAGE_READWRITE)
				{
					p = (char*)info.BaseAddress;
					BYTE* lpData = (BYTE*)malloc(info.RegionSize);
					if (ReadProcessMemory(hProcess, p, lpData, info.RegionSize, &lpRead))
					{
						for (size_t i = 0; i < (lpRead - len); ++i)
						{
							if (memcmp(params->data, &lpData[i], len) == 0)
							{
								char* ref = p + i;
								if (ref == params->data) continue;
								if (len <= replacementLength)
								{
									for (int j = 0; j < len; j++) {
										ref[j] = params->replacement[j];
									}
								}
								else
								{
									for (int j = 0; j < len; j++) {
										ref[j] = j < replacementLength ? params->replacement[j] : '\0';
									}
								}
							}
						}
					}
					free(lpData);
				}
			}
			p += info.RegionSize;
		}
		CloseHandle(hProcess);
		std::cout << "Replaced" << std::endl;
	}
}
