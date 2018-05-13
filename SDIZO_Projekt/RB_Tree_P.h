#pragma once
#include "Container_P.h"
#include <string>
#include <sstream>
class RB_Tree_P : public Container_P
{
private:
	class RB_Tree_Node
	{
	public:
		RB_Tree_Node * parent;
		RB_Tree_Node * left_son;
		RB_Tree_Node * right_son;
		
		// color=false - Czarne , color=true - Czerwone
		bool color;	
		int value;
	};
	RB_Tree_Node * sentinel_node;
	RB_Tree_Node * root_node;

	// Elementy dla wyswietlenia kopca w postaci drzewa
	std::string cl;
	std::string cr;
	std::string cp;

	void displayRBTree(std::string sp, std::string sn, RB_Tree_Node * node, std::stringstream & ss);
	
	// Wyszukiwanie nastepnika
	RB_Tree_Node* findSuccessor(RB_Tree_Node * node);

	// Rotacja w prawo
	void rotate_right(RB_Tree_Node * rot_node);
	// Rotacja w lewo
	void rotate_left(RB_Tree_Node * rot_node);
	
	// Funkcja naprawy drzewa przy wstawianiu
	void fixUpInsert(RB_Tree_Node * node);
	
	// Funkcja dla znalezienia elementu do usuniecia
	RB_Tree_Node * search(const int value);

	// Wlasciwa funkcja usuwania
	void properRemove(RB_Tree_Node * node);

	// Funkcja naprawy drzewa przy usuwaniu
	void fixUpRemove(RB_Tree_Node * node);

	RB_Tree_P::RB_Tree_Node* minValInSubTree(RB_Tree_Node * node);

public:
	RB_Tree_P();
	RB_Tree_P(int * arr);
	~RB_Tree_P();
	
	bool find(const int el);
	void insert(const int new_value);
	void remove(const int value);
	void change_node(const int old_value, const int new_value);
	std::string to_string();

	// insert wrapper dla obslugi manualnej - dodaje nowy wezel do struktury
	void insert_wrp(const int new_num, const int no_arg);
	// push_front wrapper - wywoluje insert - dla testow
	void push_front_wrp(const int new_num, const int no_arg);
	// remove front wrapper dla obslugi manualnej - usuwa korzen
	void remove_front_wrp(const int no_arg, const int no_arg1);
	void remove_wrp(const int value, const int no_arg);
	// funkcja usuwania korzenia
	void remove_front();

	static Container_P * create()
	{
		return new RB_Tree_P();
	}
	
};

