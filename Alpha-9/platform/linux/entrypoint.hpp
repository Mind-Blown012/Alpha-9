#pragma once

extern void Awake();
extern void Start();
extern void Stop();

int main(int argc, char *argv[])
{
	using namespace Alpha9;

	Application *app = new Application;
	Awake();
	app->Start();
	Start();
	app->Stop();
	Stop();
	delete app;
}
// TODO: Cleanup main include files
