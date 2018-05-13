#include "stdafx.h"
#include "TimeTests.h"

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
	int gen_pos, gen_number, ammount = ammount_val, op_count = AUTO_OP_COUNT, measur_count = AUTO_MEASUR_COUNT;

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
		printf("%02d %%", (i * 100 / measur_count));
		container_pt = Container_P_Factory::Get()->CreateContainer(container_name);					// dla kazdego pomiaru tworzymy nowa tablice

		for (int i = 0; i < ammount; i++) {															// wypelniamy tablice losowymi liczbami od INT_MIN do INT_MAX
			gen_number = dist_number(gen);															// wylosowanie liczby
			container_pt->push_front_wrp(gen_number, 0);											// dodanie wylosowanej liczby do tablicy
		}

		if (operation) {
			for (int j = 0; j < op_count; j++)
			{
				//dist_pos = dist(0, container_pt->get_size() - 1);
				gen_pos = (container_pt->get_size()) / 2 - 1;
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

void testsMenu(int prev_choice)
{
	std::string container;

	if (prev_choice == 1 || prev_choice == 2)
	{
		if (prev_choice == 1)
			container = "Array";
		else container = "List";

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
	}
	else
	{
		if (prev_choice == 3)
			container = "Heap";
		else container = "RBTree";

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

void runAllTests()
{
	std::string container;
	int arr[] = { 5000,10000,20000,40000,60000,80000,100000 };
	
	container = "Array";
	for (int i = 0; i < 7; i++)
	{
		tests(container, "Dodawanie na poczatek", push_front_pt, 0);
		tests(container, "Dodawanie na koniec", push_back_pt, 0);
		tests(container, "Dodawanie na pozycji", insert_pt, 0);
		tests(container, "Usuwanie na poczatku", remove_front_pt, 0);
		tests(container, "Usuwanie na koncu", remove_back_pt, 0);
		tests(container, "Usuwanie z pozycji", remove_pt, 0);
		tests(container, "Przeszukiwanie (WCS)", nullptr, 0);
	}
	
	container = "list";
	for (int i = 0; i < 7; i++) {
		tests(container, "Dodawanie na poczatek", push_front_pt, arr[i], 0);
		tests(container, "Dodawanie na koniec", push_back_pt, arr[i], 0);
		tests(container, "Dodawanie na pozycji", insert_pt, arr[i], 0);
		tests(container, "Usuwanie na poczatku", remove_front_pt, arr[i], 0);
		tests(container, "Usuwanie na koncu", remove_back_pt, arr[i], 0);
		tests(container, "Usuwanie z pozycji", remove_pt, arr[i], 0);
		tests(container, "Przeszukiwanie (WCS)", nullptr, arr[i], 0);
	}

	container = "Heap";
	for (int i = 0; i < 7; i++) {
		tests(container, "Dodawanie na poczatek", push_front_pt, arr[i], 0);
		tests(container, "Usuwanie na poczatku", remove_front_pt, arr[i], 0);
		tests(container, "Przeszukiwanie (WCS)", nullptr, arr[i], 0);
	}

	container = "RBTree";
	for (int i = 0; i < 7; i++) {
		tests(container, "Dodawanie do struktury", push_front_pt, arr[i], 0);
		tests(container, "Usuwanie z korzenia", remove_front_pt, arr[i], 0);
		tests(container, "Przeszukiwanie (WCS)", nullptr, arr[i], 0);
	}

	system("cls");
	std::cout << "All tests done! Results in 'tests.txt'";
	std::getchar();
}

std::string printResults(std::string container, std::string action, int data_size, int op_count, int measur_count, double results[], bool details)
{
	//Get current timestamp
	typedef std::chrono::system_clock sys_clock;
	sys_clock::time_point p = sys_clock::now();
	std::time_t t = sys_clock::to_time_t(p);
	std::string time_stamp = std::ctime(&t);

	double mean_time = 0;
	int good_res_count = 0;
	std::stringstream ss;
	ss << "################################################################################\n\n";
	ss << "Data pomiaru:\t\t" << time_stamp;
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
	if (details)
		ss << "--------------------------------------------------------------------------------\n";

	ss << "Srednia z pomiarow:\t" << mean_time / measur_count << "\tns\n\n";
	ss << "################################################################################\n";
	return ss.str();
}