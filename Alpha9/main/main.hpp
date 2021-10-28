#pragma once

#include <iostream>
#include "application.hpp"
#include "logger/logger.hpp"
#include "game_base.hpp"
#include "time.hpp"

// TODO: Pre-compiled header files

int main(int argc, char* argv[])
{
	using namespace Alpha9;
	
	Time::Init();

	Game* g = CreateGame();
	g->Awake();
	GetMainApplication().Run(g);

	std::cout << "Press any key to continue...";
	while (!std::cin.get());

	return 0;
}