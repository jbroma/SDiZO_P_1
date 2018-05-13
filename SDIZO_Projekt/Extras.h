#pragma once
#include "Container_P.h"
#include "Container_P_Factory.h"
#include "Array_P.h"
#include "List_P.h"
#include "Binary_Heap_P.h"
#include "RB_Tree_P.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

typedef void (Container_P::*op_pt)(const int, const int);

// wskazniki na funkcje odpowiednich operacji
const op_pt push_front_pt = &Container_P::push_front_wrp;
const op_pt push_back_pt = &Container_P::push_back_wrp;
const op_pt insert_pt = &Container_P::insert_wrp;
const op_pt remove_front_pt = &Container_P::remove_front_wrp;
const op_pt remove_back_pt = &Container_P::remove_back_wrp;
const op_pt remove_pt = &Container_P::remove_wrp;

void gotoXY(int x, int y);
void hideCursor();
int menu(int x, int y, std::string title, int count, ...);

void testsMenu(int);
int ammountMenu();
//int position_menu();
int countMenu(std::string title);
void tests(std::string container, std::string op_name,  op_pt operation, int ammount_val, bool details = 1);
std::string printResults(std::string container, std::string action, int data_size, int op_count, int measur_count, double results[], bool details);

void manualMenu();
std::string inputPrompt(std::string title);
void autoMenu();
void operationMenu(std::string container_type, Container_P * container);
void runAllTests();


