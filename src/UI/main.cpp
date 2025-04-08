#include <iostream>
#include "FYPEngine/FYPEngine.h"

using namespace FYPEngine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	std::shared_ptr<Entity> ent1 = core->addEntity();
	ent1->setTexture("C:/Users/harry/Documents/FYP2025/EngineSource/FYPEngine/build/Debug/image.bmp");
	core->start();

	return 0;
}