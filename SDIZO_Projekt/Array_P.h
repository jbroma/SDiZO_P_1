#pragma once
#pragma warning(disable:4996)
#define D_SCL_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include "Container_P.h"
class Array_P : public Container_P
{
public:
	Array_P();
	Array_P(int * arr);
	~Array_P();
	void insert(const int new_num, const int pos);
	void push_front(const int new_num);
	void push_back(const int new_num);
	void remove(const int pos);
	void remove_front();
	void remove_back();
	
	bool find(const int);
	void set_num(const int new_num, const int pos);
	int get_size();
	std::string to_string();

	static Container_P * create()
	{
		return new Array_P();
	}

private:
	int * array;
	int size = 0;

};

