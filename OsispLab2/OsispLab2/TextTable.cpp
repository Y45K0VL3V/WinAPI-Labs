#include "TextTable.h"

TextTable::TextTable(char columnAmount, char rowAmount)
{
	_columnAmount = columnAmount;
	_rowAmount = rowAmount;
	//_textBoxList = (HWND*)calloc(rowAmount * columnAmount, sizeof(HWND));
}

