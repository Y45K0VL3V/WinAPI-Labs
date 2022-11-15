#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void main()
{
	string localString = "Work123123Work123123";
	string anotherString = "Work123123 Hello";
	while (1)
	{
		cout << localString << endl;
		cout << anotherString << endl;
		_getch();
	}
}