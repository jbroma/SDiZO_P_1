#include "stdafx.h"
#include "RB_Tree_P.h"


RB_Tree_P::RB_Tree_P()
{
	// Utworzenie wezla straznika
	this->sentinel_node = new RB_Tree_Node();
	sentinel_node->color = false;
	sentinel_node->parent = nullptr;
	sentinel_node->left_son = nullptr;
	sentinel_node->right_son = nullptr;
	root_node = sentinel_node;

	// Ustawienie specjalnych znakow dla rysowania kopca w konsoli
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;
}

RB_Tree_P::RB_Tree_P(int * arr)
{
	// Utworzenie wezla straznika
	this->sentinel_node = new RB_Tree_Node();
	sentinel_node->color = false;
	sentinel_node->parent = sentinel_node;
	sentinel_node->left_son = sentinel_node;
	sentinel_node->right_son = sentinel_node;
	root_node = sentinel_node;

	// Ustawienie specjalnych znakow dla rysowania kopca w konsoli
	cr = cl = cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;

	for (int i = 1; i < arr[0] + 1; i++)
	{
		this->insert(arr[i]);
	}
}


RB_Tree_P::~RB_Tree_P()
{
	while (root_node != sentinel_node)
		properRemove(root_node);
	delete sentinel_node;
}

RB_Tree_P::RB_Tree_Node* RB_Tree_P::findSuccessor(RB_Tree_Node * node)
{
	if (node->right_son != sentinel_node)
		return minValInSubTree(node->right_son);
	RB_Tree_Node * y = node->parent;
	while (y != sentinel_node && node == y->right_son) {
		node = y;
		y = y->parent;
	}
	return y;
}

void RB_Tree_P::rotate_right(RB_Tree_Node * rot_node)
{
	RB_Tree_Node * ls_node, *parent_node;
	ls_node = rot_node->left_son;
	if (ls_node != sentinel_node)
	{
		parent_node = rot_node->parent;
		rot_node->left_son = ls_node->right_son;
		if (rot_node->left_son != sentinel_node) 
			rot_node->left_son->parent = rot_node;

		ls_node->right_son = rot_node;
		ls_node->parent = parent_node;
		rot_node->parent = ls_node;

		if (parent_node != sentinel_node)
		{
			if (parent_node->left_son == rot_node) 
				parent_node->left_son = ls_node; 
			else 
				parent_node->right_son = ls_node;
		}
		else 
			root_node = ls_node;
	}
}

void RB_Tree_P::rotate_left(RB_Tree_Node * rot_node)
{
	RB_Tree_Node * rs_node, *parent_node;				// rs_node - right son node
	rs_node = rot_node->right_son;
	if (rs_node != sentinel_node)
	{
		parent_node = rot_node->parent;
		rot_node->right_son = rs_node->left_son;
		if (rot_node->right_son != sentinel_node) 
			rot_node->right_son->parent = rot_node;

		rs_node->left_son = rot_node;
		rs_node->parent = parent_node;
		rot_node->parent = rs_node;

		if (parent_node != sentinel_node)
		{
			if (parent_node->left_son == rot_node) 
				parent_node->left_son = rs_node; 
			else 
				parent_node->right_son = rs_node;
		}
		else 
			root_node = rs_node;
	}
}

bool RB_Tree_P::find(int el)
{
	RB_Tree_Node * it = search(el);
	if (it != sentinel_node) return true;
	return false;
}

void RB_Tree_P::insert(const int new_value) 
{
	RB_Tree_Node * new_node = new RB_Tree_Node();
	new_node->value = new_value;
	RB_Tree_Node * x = root_node;
	RB_Tree_Node * y = sentinel_node;
	while (x != sentinel_node) {
		y = x;
		if (new_value < x->value)
			x = x->left_son;
		else
			x = x->right_son;
	}
	new_node->parent = y;
	if (y == sentinel_node)
		root_node = new_node;
	else {
		if (new_node->value < y->value)
			y->left_son = new_node;
		else
			y->right_son = new_node;
	}
	new_node->left_son = sentinel_node;
	new_node->right_son = sentinel_node;
	new_node->color = true;
	fixUpInsert(new_node);
}

void RB_Tree_P::fixUpInsert(RB_Tree_Node * node) 
{
	while (node->parent->color == true) {
		if (node->parent == node->parent->parent->left_son) {
			RB_Tree_Node * y = node->parent->parent->right_son;
			if (y->color == true) {
				node->parent->color = false;
				y->color = false;
				node->parent->parent->color = true;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->right_son) {
					node = node->parent;
					rotate_left(node);
				}
				node->parent->color = false;
				node->parent->parent->color = true;
				node->parent->right_son->color = false;
				rotate_right(node->parent->parent);
			}
		}
		else {
			RB_Tree_Node * y = node->parent->parent->left_son;
			if (y->color == true) {
				node->parent->color = false;
				y->color = false;
				node->parent->parent->color = true;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left_son) {
					node = node->parent;
					rotate_right(node);
				}
				node->parent->color = false;
				node->parent->parent->color = true;
				node->parent->left_son->color = false;
				rotate_left(node->parent->parent);
			}
		}
	}
	root_node->color = false;
}

RB_Tree_P::RB_Tree_Node * RB_Tree_P::search(const int value)
{
	RB_Tree_Node * x = root_node;
	while (x != sentinel_node && value != x->value) {
		if (value < x->value)
			x = x->left_son;
		else
			x = x->right_son;
	}
	return x;
}

void RB_Tree_P::properRemove(RB_Tree_Node * node)
{
	RB_Tree_Node * x = sentinel_node;
	RB_Tree_Node * y = sentinel_node;
	if (node->left_son == sentinel_node || node->right_son == sentinel_node)
		y = node;
	else
		y = findSuccessor(node);
	if (y->left_son != sentinel_node)
		x = y->left_son;
	else
		x = y->right_son;
	x->parent = y->parent;
	if (y->parent == sentinel_node)
		root_node = x;
	else {
		if (y == y->parent->left_son)
			y->parent->left_son = x;
		else
			y->parent->right_son = x;
	}
	if (y != node)
		node->value = y->value;
	if (y->color == false)
		fixUpRemove(x);
	delete y;
}

void RB_Tree_P::fixUpRemove(RB_Tree_Node * node)
{
	while (node != root_node && node->color == false) 
	{
		RB_Tree_Node * x = 0;
		if (node->parent->left_son == node) 
		{
			x = node->parent->right_son;
			if (x->color == true) 
			{
				x->color = false;
				node->parent->color = true;
				rotate_left(node->parent);
				x = node->parent->right_son;
			}
			if (x->left_son->color == false && x->right_son->color == false) 
			{
				x->color = true;
				node = node->parent;
			}
			else 
			{
				if (x->right_son->color == false) 
				{
					x->left_son->color = false;
					x->color = true;
					rotate_right(x);
					x = node->parent->right_son;
				}
				x->color = node->parent->color;
				node->parent->color = false;
				x->right_son->color = false;
				rotate_left(node->parent);
				node = root_node;
			}
		}
		else 
		{
			x = node->parent->left_son;
			if (x->color == true) 
			{
				x->color = false;
				node->parent->color = true;
				rotate_right(node->parent);
				x = node->parent->left_son;
			}
			if (x->right_son->color == false && x->left_son->color == false) 
			{
				x->color = true;
				node = node->parent;
			}
			else 
			{
				if (x->left_son->color == false) 
				{
					x->right_son->color = false;
					x->color = true;
					rotate_left(x);
					x = node->parent->left_son;
				}
				x->color = node->parent->color;
				node->parent->color = false;
				x->left_son->color = false;
				rotate_right(node->parent);
				node = root_node;
			}
		}
	}
	node->color = false;
}

RB_Tree_P::RB_Tree_Node* RB_Tree_P::minValInSubTree(RB_Tree_Node * node)
{
	if (node != sentinel_node)
		while (node->left_son != sentinel_node) node = node->left_son;
	return node;
}

void RB_Tree_P::remove(const int value)
{
	RB_Tree_Node * x = search(value);
	if (x != sentinel_node)
		properRemove(x);
	else throw std::invalid_argument("Brak elementu w drzewie");
}

void RB_Tree_P::change_node(const int old_value, const int new_value)
{
	RB_Tree_Node * x = search(old_value);
	if (x != sentinel_node)
	{
		properRemove(x);
		insert(new_value);
	}
	else throw std::invalid_argument("Nie ma takiego elementu w drzewie");
}

std::string RB_Tree_P::to_string()
{
	std::stringstream ss;
	this->displayRBTree("", "", root_node, ss);
	return ss.str();
}

void RB_Tree_P::insert_wrp(const int new_num, const int no_arg)
{
	this->insert(new_num);
}

void RB_Tree_P::push_front_wrp(const int new_num, const int no_arg)
{
	insert(new_num);
}

void RB_Tree_P::remove_front_wrp(const int no_arg, const int no_arg1)
{
	remove_front();
}

void RB_Tree_P::remove_wrp(const int value, const int no_arg)
{
	remove(value);
}

void RB_Tree_P::remove_front()
{
	properRemove(root_node);
}

void RB_Tree_P::displayRBTree(std::string sp, std::string sn, RB_Tree_Node * node, std::stringstream & ss)
{
	// ALGORYTM WYPISYWANIA ZACZERPNIETY ZOSTAL ZE STRONY http://eduinf.waw.pl/inf
	std::string str;
	if (node != sentinel_node)
	{
		str = sp;
		if (sn == this->cr) str[str.length() - 2] = ' ';
		displayRBTree(str + this->cp, this->cr, node->right_son, ss);

		str = str.substr(0, sp.length() - 2);
		ss << str << sn;
		if(node->color)
			ss << "R:" << node->value << std::endl;
		else ss << "B:" << node->value << std::endl;

		str = sp;
		if (sn == this->cl) str[str.length() - 2] = ' ';
		displayRBTree(str + this->cp, this->cl, node->left_son, ss);
	}
}


