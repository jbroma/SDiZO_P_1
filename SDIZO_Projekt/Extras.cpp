#include "stdafx.h"
#include "Extras.h"

int ammountMenu()
{
	int choice = menu(MENU_X, MENU_Y, "Ilosc danych losowych", 10, "\t1 000", "\t2000", "\t4 000", "\t8 000", "\t16 000", "\t32 000", "\t64 000", "\t128 000", "\t256 000", "\t512 000");
	return 1000 * std::pow(2, choice - 1);
}

int countMenu(std::string title)
{
	int choice = menu(MENU_X, MENU_Y, title, 6, "\t1", "\t10", "\t100", "\t1 000", "\t10 000", "\t100 000");
	return std::pow(10, choice - 1);
}

void manualMenu()
{
	Sleep(100);
	std::cin.sync();
	int * arr = loadFromFile(inputPrompt("Podaj nazwe pliku wraz z rozszerzeniem"));
	std::cin.sync();
	if(arr)
	{
		int choice = menu(MENU_X, MENU_Y, "Wybierz strukture", 5, "Array", "List", "Binary Heap", "RB Tree", "Exit");
		switch (choice)
		{
		case 1: manualOperationMenu("Array", new Array_P(arr)); break;
		case 2: manualOperationMenu("List", new List_P(arr)); break;
		case 3: manualOperationMenu("Heap", new Binary_Heap_P(arr)); break;
		case 4: manualOperationMenu("RBTree", new RB_Tree_P(arr)); break;
		case 5: return;
		}
	}
	delete[] arr;
}

void testStructureMenu()
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

void manualOperationMenu(std::string container_type, Container_P * container)
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
			catch (std::logic_error &e)
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
			catch (std::logic_error &e)
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


