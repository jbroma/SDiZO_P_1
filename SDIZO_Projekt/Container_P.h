#pragma once
#include <string>
class Container_P
{
public:
	Container_P();
	virtual ~Container_P();

	virtual void insert(const int new_num, const int pos);
	virtual void push_front(const int new_num);
	virtual void push_back(const int new_num);
	virtual void remove(const int pos);
	virtual void remove_front();
	virtual void remove_back();

	virtual bool find(const int el);
	virtual void set_num(const int new_num, const int pos);
	virtual int get_size();
	virtual std::string to_string();

	virtual void insert_wrp(const int new_num, const int pos);
	virtual void push_front_wrp(const int new_num, const int no_arg);
	virtual void push_back_wrp(const int new_num, const int no_arg);
	virtual void remove_wrp(const int no_arg, const int pos);
	virtual void remove_front_wrp(const int no_arg, const int no_arg_1);
	virtual void remove_back_wrp(const int no_arg, const int no_arg_1);

};

