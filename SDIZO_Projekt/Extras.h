#pragma once
#include "Container_P.h"
#include "Container_P_Factory.h"
#include "Array_P.h"
#include "List_P.h"
#include "Binary_Heap_P.h"
#include "RB_Tree_P.h"
#include "FileOperations.h"
#include "ConsoleNav.h"
#include "TimeTests.h"
#include <string>
#include <iostream>
#include <sstream>

int ammountMenu();
int countMenu(std::string title);
void manualMenu();
void testStructureMenu();
void manualOperationMenu(std::string container_type, Container_P * container);



