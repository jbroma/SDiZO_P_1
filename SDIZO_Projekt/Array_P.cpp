#include "stdafx.h"
#include "Array_P.h"


Array_P::Array_P()
{
	this->array = new int[1];
}

Array_P::Array_P(int * arr)
{
	this->array = new int[arr[0]];
	for (int i = 0; i < arr[0]; i++)
	{
		this->array[i] = arr[i+1];
	}
	this->size = arr[0];
}

Array_P::~Array_P()
{
	delete[] this->array;
}

void Array_P::insert(const int new_num, const int pos)
{	// Warunki sprawdzaj?ce czy operacja nie jest to?sama z poprzednimi funkcjami
	if (pos == 0)
	{
		this->push_front(new_num);
		return;
	}
	if (pos == this->size) {
		this->push_back(new_num);
		return;
	}
	if (pos < 0 || pos > this->size)
		throw std::invalid_argument("Nie mozna wstawic elementu na zadanej pozycji");
	int * newArray = new int[this->size + 1];															// nowa, wieksza tablica															
	memcpy(&newArray[0], &this->array[0], pos * sizeof(int));
	newArray[pos] = new_num;																			// dodanie do tablicy nowego elementu
	memcpy(&newArray[pos+1], &this->array[pos], (this->size - pos)* sizeof(int));
	delete[] this->array;																				// zniszczenie starej tablicy i zwolnienie miejsca
	this->array = newArray;																				// ustawienie wskaznika na nowa tablice
	this->size++;																						// zaktualizowanie rozmiaru tablicy
}

void Array_P::push_front(const int new_num)
{
	int * newArray = new int[this->size + 1];
	newArray[0] = new_num;
	memcpy(&newArray[1], &this->array[0], this->size * sizeof(int));
	delete[] this->array;
	this->array = newArray;
	this->size++;

}

void Array_P::push_back(const int new_num)
{
	int * newArray = new int[this->size + 1];
	memcpy(&newArray[0], &this->array[0], this->size * sizeof(int));
	newArray[size] = new_num;
	delete[] this->array;
	this->array = newArray;
	this->size++;
}

void Array_P::remove(const int pos)
{
	if (pos == 0)
	{
		this->remove_front();
		return;
	}
	if (pos == this->size - 1) {
		this->remove_back();
		return;
	}
	if (pos < 0 || pos >= this->size)
		throw std::invalid_argument("Nie mozna usunac elementu na zadanej pozycji");
	int * newArray = new int[size - 1];																	// nowa, wieksza tablica
	memcpy(&newArray[0], &this->array[0], pos * sizeof(int));
	memcpy(&newArray[pos], &this->array[pos + 1], (this->size - pos -1) * sizeof(int));
	delete[] this->array;																				// zniszczenie starej tablicy i zwolnienie miejsca
	this->array = newArray;																				// ustawienie wskaznika na nowa tablice
	this->size--;																						// zaktualizowanie rozmiaru tablicy
}

void Array_P::remove_front()
{
	if (this->size <= 0)
		throw std::length_error("Brak elementow w strukturze");
	int * newArray = new int[this->size - 1];
	memcpy(&newArray[0], &this->array[1], (this->size - 1) * sizeof(int));
	delete[] this->array;
	this->array = newArray;
	this->size--;
}

void Array_P::remove_back()
{
	if (this->size <= 0)
		throw std::length_error("Brak elementow w strukturze");
	int * newArray = new int[this->size - 1];
	memcpy(&newArray[0], &this->array[0], (this->size - 1) * sizeof(int));
	delete[] this->array;
	this->array = newArray;
	this->size--;
}

bool Array_P::find(const int num)
{
	if (this->size == 0) return false;
	for (int i = 0; i < size; i++) {
		if (this->array[i] == num)
			return true;
	}
	return false;
}

void Array_P::set_num(const int new_num, const int pos)
{
	if (pos < 0 || pos >= this->size)
		throw std::invalid_argument("Nie mozna zmienic elementu na zadanej pozycji (out of range)");
	this->array[pos] = new_num;
}

int Array_P::get_size()
{
	return this->size;
}

std::string Array_P::to_string()
{
	std::stringstream ss;
	for (int i = 0; i < this->size; i++)
		ss << this->array[i] << " ";
	ss << "\n";
	return ss.str();
}


