// Program: LuaScroll
// Author: Alexander Casal
// Description: Test LuaScroll

// Memory Leak Detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Includes
#include "luascroll.h"
#include <iostream>

int main()
{
	try
	{
		LSE::LuaScroll apples("apples.lua");
		std::cout << "Number: " << apples.at<int>("boxes.capacity.number") << std::endl;

		bool isGlobal = apples.at<bool>("globalvar");
		if (isGlobal)
		{
			std::cout << "We got a global variable...\n";
		}
	}
	catch (LSE::LuaException e)
	{
		std::cout << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
	std::cin.ignore();
	return 0;
}