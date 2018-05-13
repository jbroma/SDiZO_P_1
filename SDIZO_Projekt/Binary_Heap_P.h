#pragma once
#pragma warning(disable:4996)
#define D_SCL_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include "Container_P.h"
class Binary_Heap_P : public Container_P
{
public:
	Binary_Heap_P();
	Binary_Heap_P(int * arr);
	~Binary_Heap_P();

	void insert(const int new_num);
	void remove_front();
	bool find(const int new_num);
	int get_size();
	std::string to_string();

	// insert wrapper - dla obslugi manualnej
	void insert_wrp(const int new_num, const int no_arg);
	// remove wrapper - dla obslugi manualnej
	void remove_wrp(const int no_arg, const int no_arg1);

	void push_front_wrp(const int val, const int no_arg);
	static Container_P * create()
	{
		return new Binary_Heap_P();
	}

private:
	int * array;
	int size = 0;

	// Elementy dla wyswietlenia kopca w postaci drzewa
	std::string cl;
	std::string cr;
	std::string cp;

	void displayHeap(std::string sp, std::string sn, int v, std::stringstream &ss);

};

