#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"

class TextTable
{
public:
	TextTable(char columnAmount, char rowAmount, char* cellsData);
	
	void SetDimensions(short x, short y, short width);

	char GetColumns() { return _columnAmount; };
	char GetRows() { return _rowAmount; };
	
	short GetTableWidth() { return _tableWidth; };
	short GetTableHeight() { return _tableHeight; };

private:
	void RecalculateTable();
	char** SetText(char* totalData);

	char _columnAmount;
	char _rowAmount;

	// x - horizontal coord. of left top point.
	short _x;
	// y - vertical coord. of left top point.
	short _y;

	short _tableWidth;
	short _tableHeight;

	wchar_t** _cellsData;
};

