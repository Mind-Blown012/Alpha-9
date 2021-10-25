#pragma once

#include "macros.hpp"
#include "events/events.hpp"
#include "rendering/window.hpp"
#include "rendering/context.hpp"
#include "GLFW/glfw3.h"

#ifdef A9_PLATFORM_WINDOWS

namespace Alpha9
{
	class A9_API Window : public WindowBase
	{
	public:
		Window(const WindowProperties& props = WindowProperties());
		Window(const Window& rhs);
		Window(Window&& lhs);
		virtual ~Window();

		virtual void Update() override;

		static inline Window* GetMainWindow() { return s_mainWindow; }
		virtual inline void* GetNativeWindow() const override { return m_window; }
		// Events
		void OnWindowClose(Event& e);
		void OnWindowMove(Event& e);
	private:
		void init();
		void shutdown();
	private:
		GLFWwindow* m_window;
		Context* m_context;
		// TODO: Use shared_ptr if possible
		static Window* s_mainWindow; // This will always be the first window created.
	protected:
		WindowProperties m_props;
	};
}
// Logging
std::ostream& operator<<(std::ostream&, const Alpha9::Window&);

#endif