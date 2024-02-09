#include "functions.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void hideCursor(bool show)
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = show;
	info.dwSize = 20;
	SetConsoleCursorInfo(hStdOut, &info);
}

void clearStreamInput() {

	cin.ignore(cin.rdbuf()->in_avail());

}

int getTrueValue()
{
	int value;

	while (!(cin >> value) || (value <= 0)) {
		clearStreamInput();
		cout << "Ошибка! Введите корректное значение:";
	}

	return value;
}

bool actionsMenu(group* (&data), int& _size)
{
	hideCursor(false);

	short x;
	short y;

	string mainMenu[] = { "Просмотр данных", "Добавление данных", "Меню сортировки", "Меню запросов", "Меню удаления", "Меню работы с файлом", "Выход из программы" };

	int activeMenu = 0;
	char key;

	while (true) {

		x = 10;
		y = 3;

		for (int i = 0; i < size(mainMenu); ++i) {

			if (i == activeMenu) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << mainMenu[i];

		}

		key = _getch();
		if (key == -32) key = _getch();

		switch (key) {

		case UP: {
			if (activeMenu > 0) {
				--activeMenu;
			}
			break;
		}

		case DOWN: {
			if (activeMenu < size(mainMenu) - 1) {
				++activeMenu;
			}
			break;
		}

		case ENTER: {
			switch (activeMenu) {
			case 0: {

				dataOutput(data, _size);
				break;
			}

			case 1: {

				dataInput(data, _size);
				break;
			}

			case 2: {

				sortingMenu(data, _size);
				break;
			}

			case 3: {

				requestsMenu(data, _size);
				break;
			}

			case 4: {

				deleteMenu(data, _size);
				break;
			}

			case 5: {

				fileMenu(data, _size);
				break;
			}
			case 6: {

				system("cls");
				cout << "Завершение работы программы..." << endl << endl;
				system("pause");
				return false;
			}
			}
		}
		}

	}
}

void dataInput(group* (&data), int& size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	string nameGroup;
	string oneTicketPrice;
	string ticketAmount;
	string globalPrice;

	string city;
	date date;
	initials initials;

	hideCursor(true);
	cout << "Введите количество выступлений, о которых желаете добавить информацию:";
	size = getTrueValue();
	hideCursor(false);

	data = new group[size];

	for (int i = 0; i < size; ++i) {
		system("cls");
		cout << "Данные о " << i + 1 << " выступлении:" << endl << endl;

		setNameGroup(data, i);

		setCity(data, i);
		setDate(data, i);
		setOneTicketPrice(data, i);
		setTicketAmount(data, i);
		setInitials(data, i);
		setGlobalPrice(data, i);

		cout << endl << endl << endl;
		hideCursor(false);
		system("pause");
	}

	system("cls");
}

void setNameGroup(group* (&data), int index)
{
	cout << endl << "--Группа--";

	string groupName[] =
	{
		"Rammstein",
		"Skillet",
		"Алёна-Алёна",
		"Виски",
		"AC/DC"
	};

	char key = 0;
	int activeMenu = 0;

	short x, y;

	while (key != 13) {

		x = 2, y = 4;

		for (int i = 0; i < size(groupName); ++i) {

			if (activeMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << groupName[i];

		}

		key = _getch();
		if (key == -32) key = _getch();

		switch (key) {
		case UP: {
			if (activeMenu > 0) {
				--activeMenu;
			}
			break;
		}

		case DOWN: {
			if (activeMenu < size(groupName) - 1) {
				++activeMenu;
			}
			break;
		}

		case ENTER: {
			switch (activeMenu) {
			case 0: {
				data[index].nameGroup = "Rammstein";
				break;
			}

			case 1: {
				data[index].nameGroup = "Skillet";
				break;
			}

			case 2: {
				data[index].nameGroup = "Алёна-Алёна";
				break;
			}

			case 3: {
				data[index].nameGroup = "Виски";
				break;
			}

			case 4: {
				data[index].nameGroup = "AC/DC";
				break;
			}
			}
		}
		}
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void setCity(group* (&data), int index)
{
	string city;

	cout << endl << endl;
	cout << endl << "--Город--" << endl;
	hideCursor(true);

	cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "Введите город выступления:";

	getline(cin, city);

	data[index].city = city;
}

void setDate(group* (&data), int index)
{
	short year;
	short month;
	short day;

	cout << endl << endl << "--Дата--" << endl;

	cout << endl << "Введите год:";
	while (!(cin >> year) || (year < 2016) || (year > 2026)) {

		clearStreamInput();
		cout << "Ошибка! Введите корректное значение:";

	}

	cout << endl << "Введите месяц:";
	while (!(cin >> month) || (month <= 0) || (month > 12)) {

		clearStreamInput();
		cout << "Ошибка! Введите корректное значение:";

	}

	cout << endl << "Введите день:";
	while (!(cin >> day) || (day <= 0)) {

		clearStreamInput();
		cout << "Ошибка! Введите корректное значение:";

	}

	data[index].date.year = to_string(year);
	data[index].date.month = to_string(month);
	data[index].date.day = to_string(day);
}

void setOneTicketPrice(group* (&data), int index)
{
	double oneTicketPrice = 0;

	cout << endl << endl << "--Цена билета--" << endl;
	cout << endl << "Введите стоимость одного билета:";
	while (!(cin >> oneTicketPrice) || (oneTicketPrice <= 0)) {

		clearStreamInput();
		cout << "Ошибка! Введите корректное значение:";

	}

	data[index].oneTicketPrice = to_string(oneTicketPrice);

}

void setTicketAmount(group* (&data), int index)
{
	int ticketAmount = 0;

	cout << endl;
	cout << endl << "--Количество--" << endl;
	cout << endl << "Введите количество билетов:";
	while (!(cin >> ticketAmount) || (ticketAmount <= 0)) {

		clearStreamInput();
		cout << "Ошибка! Введите корректное значение:";

	}

	data[index].ticketAmount = to_string(ticketAmount);
}

void setInitials(group* (&data), int index)
{
	clearStreamInput();

	string str1;
	string str2;
	string str3;

	cout << endl;
	cout << endl << "--ФИО покупателя--" << endl;
	cout << endl << "Введите фамилию:";
	getline(cin, str1);
	data[index].initials.lastName = str1;

	cout << endl << "Введите имя:";
	getline(cin, str2);
	data[index].initials.firstName = str2;

	cout << endl << "Введите отчество:";
	getline(cin, str3);
	data[index].initials.middleName = str3;
}

void setGlobalPrice(group* (&data), int index)
{
	double d_globalPrice = stod(data[index].oneTicketPrice) * stod(data[index].ticketAmount);

	d_globalPrice = round(d_globalPrice * 10000) / 10000;

	data[index].globalPrice = to_string(d_globalPrice);

	cout << endl << endl << "--Общая стоимость покупки:" << data[index].globalPrice; cout << "--";
}

void dataOutput(group* data, int size)
{
	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (size == 0) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Данные отсутствуют!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	headTable();

	for (int i = 0; i < size; ++i) {

		viewDataObject(data, i);

	}

	endTable();
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << endl << endl;
	system("pause");
	system("cls");
}

void headTable()
{

	cout << "+--------------------------------------------------------------------------------------------------------------------------------+" << endl;
	cout << "| # |     Название     |   Город         |  Дата         |    Стоимость   |    Количество   |    ФИО           |    Общая        |" << endl;
	cout << "|   |     группы       |   выступления   |  выступления  |    билета      |    билетов      |    покупателя    |    стоимость    |" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------------------------------+" << endl;
}

void viewDataObject(group* data, int index)
{
	string temp;

	cout << "| ";
	printf("%-2u", index + 1);

	cout << "|";
	printf("%-18s", data[index].nameGroup.c_str());

	cout << "|";
	printf("%-17s", data[index].city.c_str());

	cout << "|";
	temp = reduceDate(data, index);
	printf("%-15s", temp.c_str());

	cout << "|";
	printf("%-16s", data[index].oneTicketPrice.c_str());

	cout << "|";
	printf("%-17s", data[index].ticketAmount.c_str());

	cout << "|";
	temp = reduceInitials(data, index);
	printf("%-18s", temp.c_str());

	cout << "|";
	temp = reduceGlobalPrice(data, index);
	printf("%-17s", temp.c_str());

	cout << "|";

	cout << endl;
}

void endTable()
{
	cout << "+--------------------------------------------------------------------------------------------------------------------------------+";
}

string reduceDate(group* data, int index)
{
	string reduceString;

	reduceString = data[index].date.day + "." + data[index].date.month + "." + data[index].date.year;

	return reduceString;
}

string reduceInitials(group* data, int index)
{
	string reduceString;

	reduceString = data[index].initials.lastName + " " + data[index].initials.firstName[0] + "." + data[index].initials.middleName[0];

	return reduceString;
}

string reduceGlobalPrice(group* data, int index)
{
	string reduceString;

	double tempValue = stod(data[index].globalPrice);

	tempValue = round(tempValue * 10000) / 10000;

	reduceString = to_string(tempValue);

	return reduceString;
}

void sortingMenu(group* (&data), int& _size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (_size == 0) {
		cout << "Данные отсутствуют!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	string fileMenu[] =
	{
		"Сортировать по стоимости билета",
		"Cортировать по городу выступления",
		"Выход в главное меню"
	};

	int activeMenu = 0;
	int key = 0;
	short x;
	short y;

	while (true) {

		x = 10, y = 3;

		for (int i = 0; i < size(fileMenu); ++i) {

			if (activeMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << fileMenu[i];

		}

		key = _getch();

		switch (key) {

		case UP: {
			if (activeMenu > 0) {
				--activeMenu;
			}
			break;
		}

		case DOWN: {
			if (activeMenu < size(fileMenu) - 1) {
				++activeMenu;
			}
			break;
		}

		case ENTER: {
			switch (activeMenu) {

			case 0: {
				sortingTicketPrice(data, _size);
				break;
			}
			case 1: {
				sortingCity(data, _size);
				break;
			}
			case 2: {
				system("cls");
				return;
			}
			}

			break;
		}

		}

	}
}

void sortingTicketPrice(group* (&data), int& size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "*Сортировка элементов по стоимости билета*" << endl;
	cout << endl << "Таблица до сортировки:" << endl;

	headTable();
	for (int i = 0; i < size; ++i) {

		viewDataObject(data, i);

	}
	endTable();

	group temp;

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (data[j].oneTicketPrice > data[j + 1].oneTicketPrice) {

				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;

			}
		}
	}

	cout << endl << endl << "Таблица после сортировки:" << endl;

	headTable();
	for (int i = 0; i < size; ++i) {
		viewDataObject(data, i);
	}
	endTable();

	cout << endl << endl;
	system("pause");
	system("cls");
}

void sortingCity(group* (&data), int& size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "*Сортировка элементов по месту выступления*" << endl;
	cout << endl << "Таблица до сортировки:" << endl;

	headTable();
	for (int i = 0; i < size; ++i) {

		viewDataObject(data, i);

	}
	endTable();

	group temp;

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (data[j].city > data[j + 1].city) {

				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;

			}
		}
	}

	cout << endl << endl << "Таблица после сортировки:" << endl;

	headTable();
	for (int i = 0; i < size; ++i) {
		viewDataObject(data, i);
	}
	endTable();

	cout << endl << endl;
	system("pause");
	system("cls");
}

void requestsMenu(group* data, int _size)
{
	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (_size == 0) {
		cout << "Данные отсутствуют!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	int activeMenu = 0;

	string requestMenu[] = {
		"ФИО покупателей с наибольшей суммой покупки",
		"Процентное соотношение кол-ва проданых билетов по групам от общего кол-ва продаж",
		"Средняя стоимость одного билета по всем групам",
		"Общая стоимость билетов по городу",
		"Поиск самого дешевого по стоимости билета(1 ед.) по выбранной группe",
		"Выход в главное меню"
	};

	char key;

	while (true) {

		int x = 10, y = 3;

		for (int i = 0; i < size(requestMenu); ++i) {

			if (i == activeMenu) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << requestMenu[i];

		}

		key = _getch();
		if (key == -32) key = _getch();

		switch (key) {

		case UP: {

			if (activeMenu > 0)
				--activeMenu;
			break;
		}
		case DOWN: {

			if (activeMenu < size(requestMenu) - 1)
				++activeMenu;
			break;
		}

		case ENTER: {
			switch (activeMenu) {

			case 0: {

				requestFirst(data, _size);
				break;
			}

			case 1: {

				requestSecond(data, _size);
				break;
			}

			case 2: {

				requestThird(data, _size);
				break;
			}

			case 3: {

				requestFourth(data, _size);
				break;
			}

			case 4: {

				requestFifth(data, _size);
				break;
			}

			case 5: {
				system("cls");
				return;
			}
			}
		}
		}
	}
}

void requestFirst(group* data, int size)
{

	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	double maxGlobalPrice = stod(data[0].globalPrice);

	for (int i = 0; i < size; ++i) {

		if (stod(data[i].globalPrice) > maxGlobalPrice) {
			maxGlobalPrice = stod(data[i].globalPrice);
		}

	}

	cout << "--ФИО покупателей с наибольшей суммой покупки--" << endl << endl;

	headTable();
	for (int i = 0; i < size; ++i) {
		if (stod(data[i].globalPrice) == maxGlobalPrice) {
			viewDataObject(data, i);
		}
	}
	endTable();

	cout << endl << endl;
	system("pause");
	system("cls");
}

void requestSecond(group* data, int size)
{
	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "--Процентное соотношение кол-ва проданых билетов по групам от общего кол-ва продаж--" << endl;

	double RammsteinAmount = 0;
	double SkilletAmount = 0;
	double AlyonaAmount = 0;
	double ViskiAnount = 0;
	double AcDcAmount = 0;

	for (int i = 0; i < size; ++i) {

		if (data[i].nameGroup == "Rammstein") {
			++RammsteinAmount;
		}

		if (data[i].nameGroup == "Skillet") {
			++SkilletAmount;
		}

		if (data[i].nameGroup == "Алёна-Алёна") {
			++AlyonaAmount;
		}

		if (data[i].nameGroup == "Виски") {
			++ViskiAnount;
		}

		if (data[i].nameGroup == "AC/DC") {
			++AcDcAmount;
		}

	}

	cout << endl << "Rammstein:" << (RammsteinAmount / size) * 100 << "%";

	cout << endl << "Skillet:" << (SkilletAmount / size) * 100 << "%";

	cout << endl << "Алёна-Алёна:" << (AlyonaAmount / size) * 100 << "%";

	cout << endl << "Виски:" << (ViskiAnount / size) * 100 << "%";

	cout << endl << "AC/DC:" << (AcDcAmount / size) * 100 << "%";

	cout << endl << endl;
	system("pause");
	system("cls");
}

void requestThird(group* data, int size)
{
	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	double sum = 0;

	for (int i = 0; i < size; ++i) {

		sum += stod(data[i].oneTicketPrice);

	}

	double average = sum / size;

	cout << "Средняя стоимость одного билета по всем группам:" << average;

	cout << endl << endl;
	system("pause");
	system("cls");
}

void requestFourth(group* data, int size)
{
	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Введите город:";
	cin.ignore(cin.rdbuf()->in_avail());
	string city;
	getline(cin, city);

	double sum = 0;

	int cityAmount = 0;

	for (int i = 0; i < size; ++i) {
		if (data[i].city == city) {
			sum += stod(data[i].globalPrice);
			++cityAmount;
		}
	}

	if (cityAmount == 0) {
		cout << endl << "Не было найдено выступлений в городе " << city << "!";
	}
	else {
		cout << endl << "Общая сумма продаж по городу " << city << ":" << sum;
	}


	cout << endl << endl;
	system("pause");
	system("cls");
}

void requestFifth(group* data, int size)
{
	system("cls");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	int choice;
	string group;

	cout << "[1] Rammstein" << endl;
	cout << "[2] Skillet" << endl;
	cout << "[3] Алёна-Алёна" << endl;
	cout << "[4] Виски" << endl;
	cout << "[5] AC/DC" << endl;
	cout << "Выберите группу, по которой желаете узнать все самые дешевые билеты:";

	while (!(cin >> choice) || ((choice > 5) || (choice <= 0))) {
		clearStreamInput();
		cout << "Ошибка! Выберите пункт из списка:";
	}

	switch (choice) {

	case 1: {

		group = "Rammstein";
		break;
	}

	case 2: {

		group = "Skillet";
		break;
	}

	case 3: {

		group = "Алёна-Алёна";
		break;
	}

	case 4: {

		group = "Виски";
		break;
	}

	case 5: {

		group = "AC/DC";
		break;
	}
	}

	double min = 0;

	for (int i = 0; i < size; ++i) {
		if (data[i].nameGroup == group) {
			min = stod(data[i].oneTicketPrice);
			break;
		}
	}

	for (int i = 0; i < size; ++i) {
		if (data[i].nameGroup == group) {
			if (stod(data[i].oneTicketPrice) < min) {
				min = stod(data[i].oneTicketPrice);
			}
		}
	}

	cout << endl << "Все самые дешевые билеты по группе " << group << ":" << endl;
	headTable();
	for (int i = 0; i < size; ++i) {
		if (data[i].nameGroup == group) {
			if (stod(data[i].oneTicketPrice) == min) {

				viewDataObject(data, i);

			}
		}
	}

	endTable();

	cout << endl << endl;
	system("pause");
	system("cls");
}

void deleteMenu(group* (&data), int& _size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (_size == 0) {
		cout << "Данные отсутствуют!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	string fileMenu[] =
	{
		"Удаление элементов по номеру",
		"Удаление элементов по фамилии",
		"Удалить все элементы",
		"Выход в главное меню"
	};

	int activeMenu = 0;
	int key = 0;
	short x;
	short y;

	while (true) {

		x = 10, y = 3;

		for (int i = 0; i < size(fileMenu); ++i) {

			if (activeMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << fileMenu[i];

		}

		key = _getch();

		switch (key) {

		case UP: {
			if (activeMenu > 0) {
				--activeMenu;
			}
			break;
		}

		case DOWN: {
			if (activeMenu < size(fileMenu) - 1) {
				++activeMenu;
			}
			break;
		}

		case ENTER: {
			switch (activeMenu) {

			case 0: {
				deleteNumber(data, _size);
				break;
			}
			case 1: {
				deleteInitials(data, _size);
				break;
			}
			case 2: {
				deleteAll(data, _size);
				break;
			}
			case 3: {
				system("cls");
				return;
			}
			}

			break;
		}

		}

	}
}

void deleteNumber(group* (&data), int& _size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Подтвердите удаление элемента по порядковому номеру";

	string deleteAllMenu[] =
	{
		"Подтвердить",
		"Отклонить"
	};

	short x;
	short y;
	int actionMenu = 0;
	int key;
	while (true) {

		x = 0, y = 1;

		for (int i = 0; i < size(deleteAllMenu); ++i) {
			if (actionMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << deleteAllMenu[i];

		}

		key = _getch();
		switch (key) {
		case UP: {
			if (actionMenu > 0) {
				--actionMenu;
			}
			break;
		}
		case DOWN: {
			if (actionMenu < size(deleteAllMenu) - 1) {
				++actionMenu;
			}
			break;
		}
		case ENTER: {
			switch (actionMenu) {
			case 0: {

				system("cls");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

				cout << "*Удаление элементов по порядковому номеру покупателя*" << endl;
				cout << endl << "Таблица до удаления:" << endl;

				headTable();
				for (int i = 0; i < _size; ++i) {

					viewDataObject(data, i);

				}
				endTable();

				hideCursor(true);
				cout << endl << endl << endl << "Введите номер элемента, который желаете удалить:";
				int index;
				while (!(cin >> index) || (index <= 0) || (index > _size)) {
					clearStreamInput();
					cout << "Ошибка! Введите корректное значение:";
				}

				--index;

				group* temp = new group[_size];

				for (int i = 0; i < _size; ++i) {

					temp[i] = data[i];

				}

				_size = _size - 1;

				data = new group[_size];

				for (int i = 0, q = 0; i < _size; ++q, ++i) {

					if (i != index) {
						data[q] = temp[i];
					}

				}

				delete[] temp;

				hideCursor(false);
				cout << endl << endl << "Таблица после удаления:" << endl;

				headTable();
				for (int i = 0; i < _size; ++i) {
					viewDataObject(data, i);
				}
				endTable();

				cout << endl << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
			case 1: {

				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << endl << endl << "Возврат в меню работы с удалением...";

				cout << endl << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
				  break;
			}
		}
		}
	}
}

void deleteInitials(group* (&data), int& _size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Подтвердите удаление элементов по фамилии покупателя";

	string deleteAllMenu[] =
	{
		"Подтвердить",
		"Отклонить"
	};

	short x;
	short y;
	int actionMenu = 0;
	int key;
	while (true) {

		x = 0, y = 1;

		for (int i = 0; i < size(deleteAllMenu); ++i) {
			if (actionMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << deleteAllMenu[i];

		}

		key = _getch();
		switch (key) {
		case UP: {
			if (actionMenu > 0) {
				--actionMenu;
			}
			break;
		}
		case DOWN: {
			if (actionMenu < size(deleteAllMenu) - 1) {
				++actionMenu;
			}
			break;
		}
		case ENTER: {
			switch (actionMenu) {
			case 0: {

				system("cls");
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

				cout << "*Удаление элементов по фамилиии покупателя(-ей)*" << endl;
				cout << endl << "Таблица до удаления:" << endl;

				headTable();
				for (int i = 0; i < _size; ++i) {

					viewDataObject(data, i);

				}
				endTable();

				hideCursor(true);

				clearStreamInput();

				cout << endl << endl << endl << "Введите фамилию покупателя(-ей), для которых желаете произвести удаление:";
				string lastName;
				getline(cin, lastName);

				int findAmount = 0;

				for (int i = 0; i < _size; ++i) {
					if (data[i].initials.lastName == lastName) {
						++findAmount;
					}
				}

				group* temp = new group[_size];

				for (int i = 0; i < _size; ++i) {
					temp[i] = data[i];
				}

				_size = _size - findAmount;
				data = new group[_size];

				for (int i = 0; i < _size; ++i) {
					if (data[i].initials.lastName != lastName) {
						data[i] = temp[i];
					}
				}

				hideCursor(false);
				cout << endl << endl << "Таблица после удаления:" << endl;

				headTable();
				for (int i = 0; i < _size; ++i) {
					viewDataObject(data, i);
				}
				endTable();

				cout << endl << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
			case 1: {

				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << endl << endl << "Возврат в меню работы с удалением...";

				cout << endl << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
				  break;
			}
		}
		}
	}
}

void deleteAll(group* (&data), int& _size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Желаете удалите все элементы из таблицы?";

	string deleteAllMenu[] =
	{
		"Подтвердить",
		"Отклонить"
	};

	short x;
	short y;
	int actionMenu = 0;
	int key;
	while (true) {

		x = 0, y = 1;

		for (int i = 0; i < size(deleteAllMenu); ++i) {
			if (actionMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << deleteAllMenu[i];

		}

		key = _getch();
		switch (key) {
		case UP: {
			if (actionMenu > 0) {
				--actionMenu;
			}
			break;
		}
		case DOWN: {
			if (actionMenu < size(deleteAllMenu) - 1) {
				++actionMenu;
			}
			break;
		}
		case ENTER: {
			switch (actionMenu) {
			case 0: {

				_size = 0;
				delete[] data;
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << endl << endl << "Удаление...";

				cout << endl << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
			case 1: {

				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << endl << endl << "Возврат в меню работы с удалением...";

				cout << endl << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
				  break;
			}
		}
		}
	}
}

void fileMenu(group* (&data), int& _size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	int choice = 0;

	string fileMenu[] =
	{
		"Запись текущих данных в файл",
		"Чтение данных из файла",
		"Удалить данные из файла",
		"Выход в главное меню"
	};

	int activeMenu = 0;
	int key = 0;
	short x;
	short y;

	while (true) {

		x = 10, y = 3;

		for (int i = 0; i < size(fileMenu); ++i) {

			if (activeMenu == i) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			gotoxy(x, ++y);
			cout << fileMenu[i];

		}

		key = _getch();

		switch (key) {

		case UP: {
			if (activeMenu > 0) {
				--activeMenu;
			}
			break;
		}

		case DOWN: {
			if (activeMenu < size(fileMenu) - 1) {
				++activeMenu;
			}
			break;
		}

		case ENTER: {
			switch (activeMenu) {

			case 0: {
				dataWriting(data, _size);
				break;
			}
			case 1: {
				dataReading(data, _size);
				break;
			}
			case 2: {
				deleteDataFile();
				break;
			}
			case 3: {
				system("cls");
				return;
			}
			}

			break;
		}

		}

	}
}

void dataWriting(group* data, int size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Введите название файла для записи текущих данных:";
	string path;
	getline(cin, path);

	ofstream write(path, ios::out);

	write << size << endl;

	for (int i = 0; i < size; ++i) {

		write << data[i].nameGroup << endl;
		write << data[i].city << endl;

		write << data[i].date.day << " ";
		write << data[i].date.month << " ";
		write << data[i].date.year << endl;

		write << data[i].oneTicketPrice << endl;
		write << data[i].ticketAmount << endl;

		write << data[i].initials.lastName << " ";
		write << data[i].initials.firstName[0] << " ";
		write << data[i].initials.middleName[0] << endl;

		write << data[i].globalPrice << endl << endl;

	}

	write.close();

	cout << endl << "Запись...";

	cout << endl << endl;
	system("pause");
	system("cls");
	return;
}

void dataReading(group* (&data), int& size)
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Введите название файла для чтения текущих данных:";
	string path;
	getline(cin, path);

	ifstream read(path);

	if (read) {
		read >> size;

		data = new group[size];

		for (int i = 0; i < size; ++i) {

			read >> data[i].nameGroup;
			read >> data[i].city;

			read >> data[i].date.day;
			read >> data[i].date.month;
			read >> data[i].date.year;

			read >> data[i].oneTicketPrice;
			read >> data[i].ticketAmount;

			read >> data[i].initials.lastName;
			read >> data[i].initials.firstName;
			read >> data[i].initials.middleName;

			read >> data[i].globalPrice;

		}

		read.close();

		cout << endl << "Чтение...";

		cout << endl << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		read.close();

		cout << endl << "Ошибка открытия файла! Возврат в меню работы с файлом";

		cout << endl << endl;
		system("pause");
		system("cls");
		return;
	}
}

void deleteDataFile()
{
	system("cls");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "Введите название файла для очистки его содержимого:";
	string path;
	getline(cin, path);

	ofstream del(path);

	if (!del) {
		cout << endl << "Ошибка удаления данных из файла!";
		del.close();
		cout << endl << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		string deleteFileMenu[] =
		{
			"Подтвердить",
			"Отклонить"
		};

		short x;
		short y;
		int actionMenu = 0;
		int key;
		while (true) {

			x = 0, y = 1;

			for (int i = 0; i < size(deleteFileMenu); ++i) {
				if (actionMenu == i) {
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else {
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
				}

				gotoxy(x, ++y);
				cout << deleteFileMenu[i];

			}

			key = _getch();
			switch (key) {
			case UP: {
				if (actionMenu > 0) {
					--actionMenu;
				}
				break;
			}
			case DOWN: {
				if (actionMenu < size(deleteFileMenu) - 1) {
					++actionMenu;
				}
				break;
			}
			case ENTER: {
				switch (actionMenu) {
				case 0: {

					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					cout << endl << endl << "Удаление...";

					del.open(path, std::ofstream::out | std::ofstream::trunc);
					del.close();

					cout << endl << endl;
					system("pause");
					system("cls");
					return;
					break;
				}
				case 1: {

					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					cout << endl << endl << "Возврат в меню работы с файлом...";

					cout << endl << endl;
					system("pause");
					system("cls");
					return;
					break;
				}
				}
				break;
			}
			}
		}
	}
}