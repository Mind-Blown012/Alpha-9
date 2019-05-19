#pragma once

#include <iostream>

extern void Awake();
extern void Start();
extern void Stop();

int main(int argc, char *argv[])
{
	using namespace Alpha9;

	Logger::Init();
	A9_CORE_INFO("Logger initalized.");

	Application *app = new Application(Awake, Start, Stop);
	app->Run();
	delete app;
	Logger::Stop();
	return 0;
}