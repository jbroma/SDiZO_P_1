#include "stdafx.h"
#include "Binary_Heap_P.h"
#include <iostream>


Binary_Heap_P::Binary_Heap_P()
{
	this->array = new int[1];
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;

}

Binary_Heap_P::Binary_Heap_P(int * arr)
{
	this->array = new int[arr[0]];
	for (int i = 1; i < arr[0] + 1; i++)
	{
		this->insert(arr[i]);
	}
	
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;
}


Binary_Heap_P::~Binary_Heap_P()
{
	while (this->size)
	{
		this->remove_front();
	}
}

void Binary_Heap_P::insert(const int new_num)
{
	int * newArray = new int[this->size + 1];
	//std::copy(this->array, this->array + size, newArray);
	memcpy(&newArray[0], &this->array[0], this->size * sizeof(int));
	delete[] this->array;
	this->array = newArray;
	
	int newElemPos = this->size;
	int parentPos = (newElemPos - 1) / 2;
	while (newElemPos > 0 && this->array[parentPos] < new_num)
	{
		this->array[newElemPos] = this->array[parentPos];
		newElemPos = parentPos;
		parentPos = (newElemPos - 1) / 2;
	}
	array[newElemPos] = new_num;
	this->size++;
}


void Binary_Heap_P::remove_front()
{
	if (this->size == 0)
		throw std::invalid_argument("Kopiec jest pusty");
	int lastElement = this->array[this->size - 1];
	int i = 0;
	int j = 1;
	while (j < this->size)
	{
		if (j + 1 < this->size && this->array[j + 1] > this->array[j])
			j++;
		if (lastElement >= this->array[j])
			break;
		this->array[i] = this->array[j];
		i = j;
		j = 2 * j + 1;
	}
	this->array[i] = lastElement;
	this->size--;

	int * newArray = new int[this->size];
	//std::copy(this->array, this->array + size, newArray);
	memcpy(&newArray[0], &this->array[0], this->size * sizeof(int));
	delete[] this->array;
	this->array = newArray;
}

bool Binary_Heap_P::find(const int new_num)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->array[i] == new_num)
			return true;
	}
	return false;
}

int Binary_Heap_P::get_size()
{
	return this->size;
}

std::string Binary_Heap_P::to_string()
{
	std::stringstream ss;
	this->displayHeap("", "", 0, ss);
	return ss.str();
}

void Binary_Heap_P::insert_wrp(const int new_num, const int no_arg)
{
	this->insert(new_num);
}

void Binary_Heap_P::remove_wrp(const int no_arg, const int no_arg1)
{
	return;
}

void Binary_Heap_P::push_front_wrp(const int val, const int no_arg)
{
	this->insert(val);
}

void Binary_Heap_P::displayHeap(std::string sp, std::string sn, int v, std::stringstream &ss)
{
	std::string str;

	if (v < this->size)
	{
		str = sp;
		if (sn == this->cr) 
			str[str.length() - 2] = ' ';
		displayHeap(str + this->cp, this->cr, 2 * v + 2, ss);

		str = str.substr(0, sp.length() - 2);

		ss << str << sn << this->array[v] << std::endl;

		str = sp;
		if (sn == this->cl) 
			str[str.length() - 2] = ' ';
		displayHeap(str + this->cp, this->cl, 2 * v + 1, ss);
	}
}