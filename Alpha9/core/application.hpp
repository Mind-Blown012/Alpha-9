#pragma once

#include <memory>

#include "macros.hpp"
#include "game_base.hpp"
#include "windows/windows_window.hpp"

// TODO: Make __debugbreak() cross-platform

extern int main(int, char**);

namespace Alpha9
{
	/* Singleton class A9_API representing the whole game-engine
	* application.
	*/
	class A9_API Application final
	{
	public:
		static Application &Instance(void);


		friend int ::main(int, char**);
		// Events
		void Update(float);
	private:
		Application();
		~Application();
	private:
		void init(void);
		virtual void Run(Game*);
		void cleanup(void);

		bool m_isRunning = false;
	};

	Application& GetMainApplication(void);
	EventManager& GetEventManager(void);
}