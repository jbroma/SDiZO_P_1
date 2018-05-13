#include "stdafx.h"
#include "Container_P.h"


Container_P::Container_P()
{
}


Container_P::~Container_P()
{
}

void Container_P::insert(const int new_num, const int pos)
{
}

void Container_P::push_front(const int new_num)
{
}

void Container_P::push_back(const int new_num)
{
}

void Container_P::remove(const int pos)
{
}

void Container_P::remove_front()
{
}

void Container_P::remove_back()
{
}

bool Container_P::find(const int el)
{
	return false;
}

void Container_P::set_num(const int new_num, const int pos)
{
}

int Container_P::get_size()
{
	return 0;
}

std::string Container_P::to_string()
{
	return std::string();
}

void Container_P::insert_wrp(const int new_num, const int pos)
{
	return this->insert(new_num, pos);
}

void Container_P::push_front_wrp(const int new_num, const int no_arg)
{
	return this->push_front(new_num);
}

void Container_P::push_back_wrp(const int new_num, const int no_arg)
{
	return this->push_back(new_num);
}

void Container_P::remove_wrp(const int no_arg, const int pos)
{
	return this->remove(pos);
}

void Container_P::remove_front_wrp(const int no_arg, const int no_arg_1)
{
	return this->remove_front();
}

void Container_P::remove_back_wrp(const int no_arg, const int no_arg_1)
{
	return this->remove_back();
}

