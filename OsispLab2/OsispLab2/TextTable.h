#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"

class TextTable
{
public:
	TextTable(char columnAmount, char rowAmount, HANDLE cellsDataFile);

	char GetColumns() { return _columnAmount; };
	char GetRows() { return _rowAmount; };

	wchar_t** GetInitData() { return _cellsInitData; };

private:
	char _columnAmount;
	char _rowAmount;

	wchar_t** _cellsInitData;

	wchar_t** ParseFile(HANDLE file);
};

