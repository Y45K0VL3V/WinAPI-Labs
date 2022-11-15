#include "pch.h"
#include "MemoryReplacer.h"
#include <Windows.h>
#include <vector>
#include <iostream>

void Replace(params* params)
{
	HANDLE process = GetCurrentProcess();
	size_t len = strlen(params->data);
	size_t replacementLength = strlen(params->replacement);

	if (process)
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		MEMORY_BASIC_INFORMATION info;
		std::vector<char> chunk;
		char* p = 0;
		while (p < si.lpMaximumApplicationAddress)
		{
			if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
			{
				if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE)
				{
					p = (char*)info.BaseAddress;
					chunk.resize(info.RegionSize);
					SIZE_T bytesRead;

					try {
						if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
						{
							for (size_t i = 0; i <= (bytesRead - len); i++)
							{
								if (memcmp(params->data, &chunk[i], len) == 0)
								{
									if (len <= replacementLength)
									{
										char* ref = (char*)p + i;
										for (int j = 0; j < len; j++) {
											ref[j] = params->replacement[j];
										}
									}
									else
									{
										char* ref = (char*)p + i;
										for (int j = 0; j < len; j++) {
											ref[j] = j < replacementLength ? params->replacement[j] : '\0';
										}
									}
								}
							}
						}
					}
					catch (std::bad_alloc& e) {
					}
				}
				p += info.RegionSize;
			}
		}
	}
}
