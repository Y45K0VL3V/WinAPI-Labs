#include "TextTable.h"

TextTable::TextTable(char columnAmount, char rowAmount, char* cellsData)
{
	_columnAmount = columnAmount;
	_rowAmount = rowAmount;

	size_t dataLength = strlen(cellsData) + 1;
	mbstowcs(*_cellsData, *SetText(cellsData), dataLength);
}

void TextTable::SetDimensions(short x, short y, short width)
{
	_x = x;
	_y = y;
	_tableWidth = width;
}

////TODO: Processing one long data in multiple strings (total amount = rows*columns). Process by /n?
char** TextTable::SetText(char* totalData)
{
	return &totalData;
}

