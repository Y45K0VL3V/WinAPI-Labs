#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"

class TextTable
{
public:
	TextTable();
	TextTable(char columnAmount, char rowAmount, HANDLE cellsDataFile);

	char GetColumns() { return _columnAmount; };
	char GetRows() { return _rowAmount; };

	char** GetInitData() { return _cellsInitData; };

private:
	char _columnAmount;
	char _rowAmount;

	char** _cellsInitData;

	char** ParseFile(HANDLE file);
};

