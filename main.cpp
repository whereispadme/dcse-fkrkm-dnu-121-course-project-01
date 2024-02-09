#include "functions.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const TCHAR* Title = TEXT("КущевськийАндрій, ПЗ-19-1");
	SetConsoleTitle(Title);

	int size = 0;
	group* data = new group[size];

	while (actionsMenu(data, size) != false)

		delete[] data;

	return 0;
}