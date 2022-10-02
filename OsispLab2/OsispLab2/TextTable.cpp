#include "TextTable.h"

TextTable::TextTable(char columnAmount, char rowAmount, HANDLE cellsDataFile)
{
	_columnAmount = columnAmount;
	_rowAmount = rowAmount;
	_cellsInitData = ParseFile(cellsDataFile);
}

wchar_t** TextTable::ParseFile(HANDLE file)
{
	short cellsAmount = _columnAmount * _rowAmount;
	wchar_t** result = (wchar_t**)calloc(cellsAmount * 255, sizeof(wchar_t));
	for (int i = 0; i < cellsAmount; i++)
	{
		DWORD dwByte;
		DWORD bytesToReadAmount = rand() % 254;
		ReadFile(file, result[i], bytesToReadAmount, &dwByte, NULL);
		result[i][dwByte] = 0;

		/*size_t dataLength = strlen(cellsData) + 1;
		mbstowcs(*_cellsData, *SetText(cellsData), dataLength);*/
	}

	return result;
}

