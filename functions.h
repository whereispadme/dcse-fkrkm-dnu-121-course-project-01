#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <ctype.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <limits>

using namespace std;

#define UP 72
#define DOWN 80
#define ENTER 13
#define LEFT 75
#define RIGHT 77

struct initials
{
	string lastName;
	string firstName;
	string middleName;
};

struct date
{
	string day;
	string month;
	string year;
};

struct group
{
	string nameGroup;
	string oneTicketPrice;
	string ticketAmount;
	string globalPrice;

	string city;
	date date;
	initials initials;
};

void gotoxy(short x, short y);
void hideCursor(bool show);
int getTrueValue();
void clearStreamInput();

bool actionsMenu(group* (&data), int& _size);

void dataInput(group* (&data), int& size);

void setNameGroup(group* (&data), int index);
void setCity(group* (&data), int index);
void setDate(group* (&data), int index);
void setOneTicketPrice(group* (&data), int index);
void setTicketAmount(group* (&data), int index);
void setInitials(group* (&data), int index);
void setGlobalPrice(group* (&data), int index);

void dataOutput(group* data, int size);

void headTable();
void viewDataObject(group* data, int index);
void endTable();
string reduceDate(group* data, int index);
string reduceInitials(group* data, int index);
string reduceGlobalPrice(group* data, int index);

void sortingMenu(group* (&data), int& _size);
void sortingTicketPrice(group* (&data), int& size);
void sortingCity(group* (&data), int& size);

void deleteMenu(group* (&data), int& _size);
void deleteNumber(group* (&data), int& _size);
void deleteInitials(group* (&data), int& _size);
void deleteAll(group* (&data), int& _size);

void requestsMenu(group* data, int _size);
void requestFirst(group* data, int size);
void requestSecond(group* data, int size);
void requestThird(group* data, int size);
void requestFourth(group* data, int size);
void requestFifth(group* data, int size);

void fileMenu(group* (&data), int& _size);
void dataWriting(group* data, int size);
void dataReading(group* (&data), int& size);
void deleteDataFile();