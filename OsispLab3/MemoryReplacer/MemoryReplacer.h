#pragma once

#ifdef MEMORYREPLACER_EXPORTS
#define MEMORYREPLACER_API __declspec(dllexport)
#else
#define MEMORYREPLACER_API __declspec(dllimport)
#endif

typedef struct params
{
	char data[256];
	char replacement[256];
} params;

extern "C" MEMORYREPLACER_API void Replace(params* params);
