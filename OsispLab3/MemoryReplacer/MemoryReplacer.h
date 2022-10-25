#pragma once

#ifdef MEMORYREPLACER_EXPORTS
#define MEMORYREPLACER_API __declspec(dllexport)
#else
#define MEMORYREPLACER_API __declspec(dllimport)
#endif

extern "C" MEMORYREPLACER_API void Replace(const char* data, const char* replacement);

