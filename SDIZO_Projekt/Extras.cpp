#include "stdafx.h"
#include "Extras.h"
#include "FileOperations.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>

#define AUTO_AMMOUNT 100000
#define AUTO_OP_COUNT 1
#define AUTO_MEASUR_COUNT 100
#define MENU_X 40
#define MENU_Y 10

void gotoXY(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int menu(int coordX, int coordY, std::string title, int n, ...)
{
	std::cin.clear();
	std::cin.sync();
	hideCursor();
	std::string whitespaces = "                                        ";
	for (int i = 0; i < title.length(); i++) {
		whitespaces[(39 - title.length()) / 2 + i] = title[i];
	}
	va_list parametry;
	va_start(parametry, n);
	std::string *wsk;
	wsk = new std::string[n];
	int pozycja = 1, pozycjaOLD = 1;
	bool refresh = true;
	for (int i = 0; i < n; i++)
	{
		wsk[i] = va_arg(parametry, const char *);
	}
	system("cls");
	va_end(parametry);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
	gotoXY(coordX, coordY);
	std::cout << whitespaces;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	for (int i = 1; i <= n; i++)
	{
		gotoXY(coordX, coordY + i);
		std::cout << "[" << i << "] " << wsk[i - 1];
	}
	std::cout << std::endl;

	while (refresh == true)
	{
		refresh = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		gotoXY(coordX, coordY + pozycjaOLD); std::cout << "[" << pozycjaOLD << "] " << wsk[pozycjaOLD - 1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoXY(coordX, coordY + pozycja); std::cout << "[" << pozycja << "] " << wsk[pozycja - 1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		while (refresh == false && (GetConsoleWindow() == GetForegroundWindow()))
		{
			Sleep(10);
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				refresh = true;
				if (pozycja == 1)
				{
					pozycjaOLD = pozycja;
					pozycja = n;
					Sleep(100);
				}

				else
				{
					pozycjaOLD = pozycja;
					pozycja--;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				refresh = true;
				if (pozycja == n)
				{
					pozycjaOLD = pozycja;
					pozycja = 1;
					Sleep(100);
				}
				else
				{
					pozycjaOLD = pozycja;
					pozycja++;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				delete[] wsk;
				gotoXY(1, 1);
				Sleep(200);
				std::cin.ignore(1000, '\n');
				return pozycja;
			}
		}
		if (GetConsoleWindow() != GetForegroundWindow())
			Sleep(200);
	}
	return 0;
}

void testsMenu(int lastChoice)
{
	std::string container;
	switch (lastChoice)
	{
	case 1:
	{
		container = "Array";
		int choice = menu(MENU_X, MENU_Y, "Rodzaj Operacji", 8, "Dodaj na poczatek", "Dodaj na koniec", "Dodaj na pozycji", "Usun na poczatku", "Usun na koncu", "Usun w dowolnym miejscu", "Znajdz liczbe", "Back");
		switch (choice)
		{
		case 1: tests(container, "Dodawanie na poczatek", push_front_pt, 0); break;
		case 2: tests(container, "Dodawanie na koniec", push_back_pt, 0); break;
		case 3: tests(container, "Dodawanie na pozycji", insert_pt, 0); break;
		case 4: tests(container, "Usuwanie na poczatku", remove_front_pt, 0); break;
		case 5: tests(container, "Usuwanie na koncu", remove_back_pt, 0); break;
		case 6: tests(container, "Usuwanie z pozycji", remove_pt, 0); break;
		case 7: tests(container, "Przeszukiwanie (WCS)", nullptr, 0); break;
		case 8: return;
		}
	} break;
	case 2:
	{
		container = "List";
		int choice = menu(MENU_X, MENU_Y, "Rodzaj Operacji", 8, "Dodaj na poczatek", "Dodaj na koniec", "Dodaj na pozycji", "Usun na poczatku", "Usun na koncu", "Usun w dowolnym miejscu", "Znajdz liczbe", "Back");
		switch (choice)
		{
		case 1: tests(container, "Dodawanie na poczatek", push_front_pt, 0); break;
		case 2: tests(container, "Dodawanie na koniec", push_back_pt, 0); break;
		case 3: tests(container, "Dodawanie na pozycji", insert_pt, 0); break;
		case 4: tests(container, "Usuwanie na poczatku", remove_front_pt, 0); break;
		case 5: tests(container, "Usuwanie na koncu" ,remove_back_pt, 0); break;
		case 6: tests(container, "Usuwanie z pozycji", remove_pt, 0); break;
		case 7: tests(container, "Przeszukiwanie (WCS)", nullptr, 0); break;
		case 8: return;
		}
	} break;
	case 3:
	{
		container = "Heap";
		int choice = menu(MENU_X, MENU_Y, "Rodzaj Operacji", 4, "Dodaj do struktury", "Usun z korzenia", "Znajdz liczbe", "Back");
		switch (choice)
		{
		case 1: tests(container, "Dodawanie do struktury", insert_pt, 0); break;
		case 2: tests(container, "Usuwanie z korzenia", remove_front_pt, 0); break;
		case 3: tests(container, "Przeszukiwanie (WCS)", nullptr, 0); break;
		case 4: return;
		}
	} break;
	case 4:
	{
		container = "RBTree";
		int choice = menu(MENU_X, MENU_Y, "Rodzaj Operacji", 4, "Dodaj do struktury", "Usun z korzenia", "Znajdz liczbe", "Back");
		switch (choice)
		{
		case 1: tests(container, "Dodawanie do struktury", insert_pt, 0); break;
		case 2: tests(container, "Usuwanie z korzenia", remove_front_pt, 0); break;
		case 3: tests(container, "Przeszukiwanie (WCS)", nullptr, 0); break;
		case 4: return;
		}
	}
	}
}

int ammountMenu()
{
	int choice = menu(MENU_X, MENU_Y, "Ilosc danych losowych", 10, "\t1 000", "\t5 000", "\t10 000", "\t20 000", "\t40 000", "\t60 000", "\t80 000", "\t100 000", "\t200 000", "\t400 000");
	switch (choice) {
	case 1: return 1000;
	case 2: return 5000;
	case 3: return 10000;
	case 4: return 20000;
	case 5: return 40000;
	case 6: return 60000;
	case 7: return 80000;
	case 8: return 100000;
	case 9: return 200000;
	case 10: return 400000;
	}
	return 0;
}

int countMenu(std::string title)
{
	int choice = menu(MENU_X, MENU_Y, title, 6, "\t1", "\t10", "\t100", "\t1 000", "\t10 000", "\t100 000");
	return std::pow(10,choice);
}

std::string printResults(std::string container, std::string action, int data_size, int op_count, int measur_count, double results[], bool details)
{
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(p);
	double mean_time = 0;
	int good_res_count = 0;
	std::stringstream ss;
	ss << "################################################################################\n\n";
	ss << "Data pomiaru:\t\t" << std::ctime(&t);
	ss << "Typ struktury:\t\t" << container << "\n";
	ss << "Rodzaj operacji:\t" << action << "\n";
	ss << "Wielkosc struktury:\t" << data_size << "\n";
	ss << "Liczba operacji/pomiar:\t" << op_count << "\n";
	ss << "Ilosc pomiarow:\t\t" << measur_count << "\n\n";
	ss << "--------------------------------------------------------------------------------\n";

	for (int i = 0; i < measur_count; i++)
	{
		if (details)
			ss << "Pomiar " << i + 1 << ":\t\t" << results[i] << "\tns\n";
		mean_time += results[i];
	}
	if(details)
		ss << "--------------------------------------------------------------------------------\n";

	ss << "Srednia z pomiarow:\t" << mean_time / measur_count << "\tns\n\n";
	ss << "################################################################################\n";
	return ss.str();
}



void manualMenu()
{
	Sleep(100);
	std::cin.sync();
	int * arr = loadFromFile(inputPrompt("Podaj nazwe pliku wraz z rozszerzeniem"));
	std::cin.sync();
	if (arr)
	{
		int choice = menu(MENU_X, MENU_Y, "Wybierz strukture", 5, "Array", "List", "Binary Heap", "RB Tree", "Exit");
		switch (choice)
		{
		case 1: operationMenu("Array", new Array_P(arr)); break;
		case 2: operationMenu("List", new List_P(arr)); break;
		case 3: operationMenu("Heap", new Binary_Heap_P(arr)); break;
		case 4: operationMenu("RBTree", new RB_Tree_P(arr)); break;
		case 5: return;
		}

	}
	//delete[] arr;
}

std::string inputPrompt(std::string title)
{
	Sleep(100);
	std::cin.sync();
	std::string input;
	std::string whitespaces = "                                        ";
	for (int i = 0; i < title.length(); i++) {
		whitespaces[(39 - title.length()) / 2 + i] = title[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);
	gotoXY(MENU_X, MENU_Y);
	std::cout << whitespaces;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY(MENU_X, MENU_Y + 1);
	std::cin >> input;
	system("cls");
	std::cin.clear();
	return input;
}

void autoMenu()
{
	while (true)
	{
		int menuchoice = menu(40, 10, "Wybierz strukture", 6, "Tablica", "Lista", "Kopiec", "Drzewo Czerwono-Czarne", "AutoTest", "Back");
		system("cls");

		switch (menuchoice)
		{
		case 1: testsMenu(1); break;
		case 2: testsMenu(2); break;
		case 3: testsMenu(3); break;
		case 4: testsMenu(4); break;
		case 5: runAllTests(); break;
		case 6: return;
		}
	}
	
}

void operationMenu(std::string container_type, Container_P * container)
{

	int choice;
	if (container_type == "Array" || container_type == "List")
	{
		while (true)
		{
			Sleep(100);
			try
			{
				choice = menu(MENU_X, MENU_Y, "Wybierz operacje", 10, "Dodaj na poczatek", "Dodaj na koniec", "Dodaj na pozycji", "Usun z poczatku", "Usun z konca", "Usun z pozycji", "Znajdz", "Zmien na pozycji", "Wyswietl strukture", "Exit");
				system("cls");
				switch (choice)
				{

				case 1: container->push_front(std::stoi(inputPrompt("Podaj liczbe do wstawienia"))); break;
				case 2: container->push_back(std::stoi(inputPrompt("Podaj liczbe do wstawienia"))); break;
				case 3: container->insert(std::stoi(inputPrompt("Podaj liczbe do wstawienia")), std::stoi(inputPrompt("Podaj pozycje wstawienia"))); break;
				case 4: container->remove_front(); break;
				case 5: container->remove_back(); break;
				case 6: container->remove(std::stoi(inputPrompt("Podaj pozycje do usuniecia"))); break;
				case 7:
				{
					bool result = container->find(std::stoi(inputPrompt("Podaj liczbe do sprawdzenia")));
					if (result)
					{
						gotoXY(MENU_X, MENU_Y);
						std::cout << "Liczba wystepuje w strukturze";
						gotoXY(MENU_X, MENU_Y + 1);
						system("PAUSE");
					}
					else
					{
						gotoXY(MENU_X, MENU_Y);
						std::cout << "Liczba nie wystepuje w strukturze";
						gotoXY(MENU_X, MENU_Y + 1);
						system("PAUSE");
					}
				} break;
				case 8: container->set_num(std::stoi(inputPrompt("Podaj liczbe do wstawienia")), std::stoi(inputPrompt("Podaj pozycje wstawienia"))); break;
				case 9: std::cout << container->to_string(); system("PAUSE"); break;
				case 10: delete container; return;
				}
			}
			catch (std::invalid_argument e)
			{
				gotoXY(MENU_X, MENU_Y);
				std::cout << "Wprowadzono niepoprawne dane\n";
				gotoXY(MENU_X, MENU_Y + 1);
				std::cout << e.what();
				gotoXY(MENU_X, MENU_Y + 2);
				system("PAUSE");
			}
			catch (std::length_error e)
			{
				gotoXY(MENU_X, MENU_Y);
				std::cout << "Wprowadzono niepoprawne dane\n";
				gotoXY(MENU_X, MENU_Y + 1);
				std::cout << e.what();
				gotoXY(MENU_X, MENU_Y + 2);
				system("PAUSE");
			}
		}
	}
	else
	{
		while (true)
		{
			std::cin.sync();
			std::cin.clear();
			Sleep(100);
			try
			{
				choice = menu(MENU_X, MENU_Y, "Wybierz operacje", 6, "Dodaj", "Usun korzen", "Usun wybrany element(RBT)", "Znajdz", "Wyswietl strukture", "Exit");
				system("cls");
				switch (choice)
				{
				case 1: container->insert_wrp(std::stoi(inputPrompt("Podaj liczbe do wstawienia")),0); break;
				case 2: container->remove_front_wrp(0,0); break;
				case 3: container->remove_wrp(std::stoi(inputPrompt("Podaj liczbe do usuniecia")), 0); break;
				case 4:
				{
					bool result = container->find(std::stoi(inputPrompt("Podaj liczbe do sprawdzenia")));
					if (result)
					{
						gotoXY(MENU_X, MENU_Y);
						std::cout << "Liczba wystepuje w strukturze";
						gotoXY(MENU_X, MENU_Y + 1);
						system("PAUSE");
					}
					else
					{
						gotoXY(MENU_X, MENU_Y);
						std::cout << "Liczba nie wystepuje w strukturze";
						gotoXY(MENU_X, MENU_Y + 1);
						system("PAUSE");
					}
				} break;
				case 5: std::cout << container->to_string(); system("PAUSE"); break;
				case 6: delete container; return;
				}
			}
			catch (std::invalid_argument e)
			{
				gotoXY(MENU_X, MENU_Y);
				std::cout << "Wprowadzono niepoprawne dane\n";
				gotoXY(MENU_X, MENU_Y + 1);
				std::cout << e.what();
				gotoXY(MENU_X, MENU_Y + 2);
				system("PAUSE");
			}
			catch (std::length_error e)
			{
				gotoXY(MENU_X, MENU_Y);
				std::cout << "Wprowadzono niepoprawne dane\n";
				gotoXY(MENU_X, MENU_Y + 1);
				std::cout << e.what();
				gotoXY(MENU_X, MENU_Y + 2);
				system("PAUSE");
			}
		}
	}
}

void tests(std::string container_name, std::string op_name, op_pt operation, int ammount_val, bool details)
{
	typedef std::chrono::high_resolution_clock clock;
	typedef std::uniform_int_distribution<> dist;
	
	Container_P * container_pt;
	std::random_device rd;
	std::mt19937 gen(rd());
	dist dist_pos, dist_number(-10000000, 10000000);												
	clock::time_point start_time, end_time;
	std::chrono::duration<double, std::nano> duration;
	double * results;
	int gen_pos, gen_number, ammount = ammount_val, op_count=AUTO_OP_COUNT, measur_count=AUTO_MEASUR_COUNT;
																		
	if (details) {
		ammount = ammountMenu();																	// wybor jak wielka bedzie struktura do ktorej bedziemy dodawac element na poczatku
		op_count = countMenu("Liczba operacji w kazdym pomiarze");
		measur_count = countMenu("Liczba pomiarow");												// wybor ile pomiarow bedziemy przeprowadzac
	}
	gotoXY(0, 0);
	printf("%s %s %d    ", container_name.c_str(), op_name.c_str(), ammount);
	results = new double[measur_count]();															// inicjalizacja zerami nowej tablicy dla wynikow pomiarow 																				// wyczyszczenie ekranu
	for (int i = 0; i < measur_count; i++)															// petla pomiarow							
	{
		gotoXY(0, 1);
		printf("%02d %%", (i*100/measur_count));
		container_pt = Container_P_Factory::Get()->CreateContainer(container_name);					// dla kazdego pomiaru tworzymy nowa tablice
		
		for (int i = 0; i < ammount; i++) {															// wypelniamy tablice losowymi liczbami od INT_MIN do INT_MAX
			gen_number = dist_number(gen);															// wylosowanie liczby
			container_pt->push_front_wrp(gen_number, 0);											// dodanie wylosowanej liczby do tablicy
		}

		if (operation) {
			for (int j = 0; j < op_count; j++)
			{
				//dist_pos = dist(0, container_pt->get_size() - 1);
				gen_pos = (container_pt->get_size())/2 -1;
				gen_number = dist_number(gen);
				start_time = clock::now();
				(*container_pt.*operation)(gen_number, gen_pos);
				end_time = clock::now();
				duration = end_time - start_time;
				results[i] += duration.count();
			}
		}
		else
		{	
			for (int j = 0; j < op_count; j++)														
			{
				start_time = clock::now();
				container_pt->find(20000000);
				end_time = clock::now();
				duration = end_time - start_time;
				results[i] += duration.count();
			}
		}
		results[i] = results[i] / op_count;
		delete container_pt;
	}
	if (details)
	{
		system("cls");
		std::cout << "Pomyslnie ukonczono pomiar\n\n";
		std::cout << printResults(container_name, op_name, ammount, op_count, measur_count, results, details);
		system("PAUSE");
		std::cin.clear();
		std::cin.sync();
	}
	else
	{
		saveToFile(printResults(container_name, op_name, ammount, op_count, measur_count, results, details));
	}
	delete[] results;
}



void runAllTests()
{

	std::string container;
	int arr[] = { 5000,10000,20000,40000,60000,80000,100000 };
	/*
	container = "Array";
	tests(container, "Dodawanie na poczatek", push_front_pt, 0);
	tests(container, "Dodawanie na koniec", push_back_pt, 0);
	tests(container, "Dodawanie na pozycji", insert_pt, 0);
	
	tests(container, "Usuwanie na poczatku", remove_front_pt, 0);
	tests(container, "Usuwanie na koncu", remove_back_pt, 0);
	tests(container, "Usuwanie z pozycji", remove_pt, 0);
	tests(container, "Przeszukiwanie (WCS)", nullptr, 0);*/

	//container = "List";
	//for (int i = 0; i < 7; i++) {
	//	/*tests(container, "Dodawanie na poczatek", push_front_pt, arr[i], 0);
	//	tests(container, "Dodawanie na koniec", push_back_pt, arr[i], 0);
	//	tests(container, "Dodawanie na pozycji", insert_pt, arr[i], 0);*/
	//	tests(container, "Usuwanie na poczatku", remove_front_pt, arr[i], 0);
	//	tests(container, "Usuwanie na koncu", remove_back_pt, arr[i], 0);
	//	/*tests(container, "Usuwanie z pozycji", remove_pt, arr[i], 0);*/
	//	/*tests(container, "Przeszukiwanie (WCS)", nullptr, arr[i], 0);*/
	//}
	

	container = "Heap";
	for (int i = 0; i < 7; i++) {
		tests(container, "Dodawanie na poczatek", push_front_pt, arr[i], 0);
		tests(container, "Usuwanie na poczatku", remove_front_pt, arr[i], 0);
		tests(container, "Przeszukiwanie (WCS)", nullptr, arr[i], 0);
	}

	/*container = "RBTree";
	for (int i = 0; i < 7; i++) {
		tests(container, "Dodawanie do struktury", push_front_pt, arr[i], 0);
		tests(container, "Usuwanie z korzenia", remove_front_pt, arr[i], 0);
		tests(container, "Przeszukiwanie (WCS)", nullptr, arr[i], 0);
	}*/

	system("cls");
	std::cout << "All tests done! Results in 'testy.txt'";
	std::getchar();
}
