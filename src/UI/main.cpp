#include <iostream>
#include "FYPEngine/FYPEngine.h"

using namespace FYPEngine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();	

	core->start();

	return 0;
}