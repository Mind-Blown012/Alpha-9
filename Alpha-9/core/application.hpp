#pragma once

#include "core.hpp"

namespace Alpha9
{
	class EventManager;
	class WindowBase;

	class A9_API Application final
	{
	public:
		// Methods
		Application(void (*AwakeFunc)(), void (*StartFunc)(), void (*StopFunc)());
		~Application(void);

		void Run();
	private:
		// Methods
		void start(void);
		void stop(void);
		void cleanup(void);
	private:
		friend A9_API Application &GetMainApplication(void);
		friend A9_API EventManager &GetEventManager(void);
		friend A9_API WindowBase &GetMainWindow(void);
	private:
		// Variables
		void (*m_awakeFunc)(), (*m_startFunc)(), (*m_stopFunc)();


		bool m_isRunning = false;

		static std::unique_ptr<Application> s_instance;
		static std::unique_ptr<EventManager> s_eventManager;
		static std::unique_ptr<WindowBase> s_mainWindow;
	};
}