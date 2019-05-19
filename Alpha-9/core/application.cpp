#include "a9pch.hpp"

#include "application.hpp"
#include "graphics/window_base.hpp"
#include "events/event.hpp"

#include <glad/glad.h>

namespace Alpha9
{
	std::unique_ptr<Application> Application::s_instance = nullptr;
	std::unique_ptr<WindowBase> Application::s_mainWindow = nullptr;
	std::unique_ptr<EventManager> Application::s_eventManager = nullptr;

	Application::Application(void(*AwakeFunc)(), void(*StartFunc)(), void(*StopFunc)())
		: m_awakeFunc(AwakeFunc)
		, m_startFunc(StartFunc)
		, m_stopFunc(StopFunc)
	{
		A9_CORE_ASSERT(!s_instance, "Error: cannot create multiple applications!");
		
		s_instance = std::make_unique<Application>(*this);
		s_mainWindow = std::unique_ptr<WindowBase>(WindowBase::Create());
		s_eventManager = std::make_unique<EventManager>();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		m_awakeFunc();
		start();
		// Main Application loop
		while (m_isRunning)
		{
			// Resolve all events
			s_eventManager->Resolve();
			glClearColor(0.133333f, 0.545f, 0.133333f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			s_mainWindow->Update();
		}
	}

	void Application::start()
	{
		m_isRunning = true;
		m_startFunc();
		BIND_EVENT(WindowCloseEvent, [this](Event &e) -> void {
			this->stop();
		});
	}
	void Application::stop()
	{
		m_isRunning = false;
		m_stopFunc();
		cleanup();
	}
	void Application::cleanup()
	{
		glfwTerminate();
		glfwSetErrorCallback(NULL);
	}

	A9_API Application &GetMainApplication()
	{
		return *Application::s_instance;
	}
	A9_API EventManager &GetEventManager()
	{
		return *Application::s_eventManager;
	}
	A9_API WindowBase &GetMainWindow()
	{
		return *Application::s_mainWindow;
	}
}
