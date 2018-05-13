#pragma once
#include "Container_P.h"
#include "Container_P_Factory.h"
#include "ConsoleNav.h"
#include "FileOperations.h"
#include "Extras.h"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <random>

#define AUTO_AMMOUNT 100000		//Default value of a data structure size
#define AUTO_OP_COUNT 1			//Default value of how many times a certain function is to be performed on a single instance of a data structure
#define AUTO_MEASUR_COUNT 100	//Default value of how many times to repeat a certain test

typedef void (Container_P::*op_pt)(const int, const int);
//Pointers to corresponding functions of a data structure
const op_pt push_front_pt = &Container_P::push_front_wrp;
const op_pt push_back_pt = &Container_P::push_back_wrp;
const op_pt insert_pt = &Container_P::insert_wrp;
const op_pt remove_front_pt = &Container_P::remove_front_wrp;
const op_pt remove_back_pt = &Container_P::remove_back_wrp;
const op_pt remove_pt = &Container_P::remove_wrp;


void tests(std::string container, std::string op_name, op_pt operation, int ammount_val, bool details = 1);
void testsMenu(int prev_choice);
void runAllTests();
std::string printResults(std::string container, std::string action, int data_size, int op_count, int measur_count, double results[], bool details);