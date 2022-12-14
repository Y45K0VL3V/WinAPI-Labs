#include "TextTable.h"

TextTable::TextTable()
{
}

TextTable::TextTable(char columnAmount, char rowAmount, HANDLE cellsDataFile)
{
	_columnAmount = columnAmount;
	_rowAmount = rowAmount;
	_cellsInitData = ParseFile(cellsDataFile);
}

char** TextTable::ParseFile(HANDLE file)
{
	short cellsAmount = _columnAmount * _rowAmount;
	
	char** result = (char**)calloc(cellsAmount, sizeof(char*));
	for (int i = 0; i < cellsAmount; i++)
		result[i] = (char*)calloc(255, sizeof(char));


	for (int i = 0; i < cellsAmount; i++)
	{
		DWORD dwByte;
		DWORD bytesToReadAmount = rand() % 254;
		ReadFile(file, result[i], bytesToReadAmount, &dwByte, NULL);
		result[i][dwByte] = 0;	
	}

	return result;
}

