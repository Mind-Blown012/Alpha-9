#pragma once

#include "graphics/window_base.hpp"
#include "core.hpp"
#include "events/event.hpp"
#include <GLFW/glfw3.h>

namespace Alpha9
{
	class A9_API Window : public WindowBase
	{
	public:
		Window(const WindowProperties& properties);
		virtual ~Window();

		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;

		virtual void Update();

		virtual void *GetNativeWindow() const;
		// Events
		void OnWindowClose(WindowCloseEvent &e);
		void OnWindowMove(WindowMoveEvent &e);
		void OnWindowFocus(WindowFocusEvent &e);
		void OnWindowResize(WindowResizeEvent &e);
		void OnWindowMaximize(WindowMaximizeEvent &e);
	private:
		void init(const WindowProperties& props);
		WindowProperties m_data;
		GLFWwindow *m_window;
		static bool s_isGLFWinitalized;
	};
}