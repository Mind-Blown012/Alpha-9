#pragma once

#include "core.hpp"
#include "event.hpp"

// WindowClose, WindowMove, WindowFocus, WindowResize, WindowMaximize

#if defined(A9_PLATFORM_WINDOWS)
#include <GLFW/glfw3.h>
	using WindowPtr = GLFWwindow *;
#elif defined(A9_PLATFORM_LINUX)
#include <GLFW/glfw3.h>
	using WindowPtr = GLFWwindow *;
#else
	#error "Only windows and linux are currently supported!"
#endif // PLATFORMS

// TODO: decide whether it would be better for every internal class to have OnEvent() method
namespace Alpha9
{

	class A9_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(const WindowPtr window)
			: m_window(window)
		{}
		WindowCloseEvent(const WindowCloseEvent &e)
			: m_window(e.GetWindow())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }

		EVENT_CLASS_TYPE(WindowCloseEvent)
	private:
		const WindowPtr m_window;
	};
	
	class A9_API WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(const WindowPtr window, unsigned int x, unsigned int y)
			: m_window(window)
			, m_x(x)
			, m_y(y)
		{}
		WindowMoveEvent(const WindowMoveEvent &e)
			: m_window(e.GetWindow())
			, m_x(e.GetX())
			, m_y(e.GetY())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline unsigned int GetX() const { return m_x; }
		inline unsigned int GetY() const { return m_y; }

		EVENT_CLASS_TYPE(WindowMoveEvent)
	private:
		const WindowPtr m_window;
		const unsigned int m_x, m_y;
	};

	class A9_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(const WindowPtr window, const bool isFocused)
			: m_window(window)
			, m_isFocused(isFocused)
		{}
		WindowFocusEvent(const WindowFocusEvent &e)
			: m_window(e.GetWindow())
			, m_isFocused(e.IsFocused())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline const bool IsFocused() const { return m_isFocused; }

		EVENT_CLASS_TYPE(WindowFocusEvent)
	private:
		const WindowPtr m_window;
		const bool m_isFocused;
	};

	class A9_API WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(const WindowPtr window, const bool isMaximized)
			: m_window(window)
			, m_isMaximized(m_isMaximized)
		{}
		WindowMaximizeEvent(const WindowMaximizeEvent &e)
			: m_window(e.GetWindow())
			, m_isMaximized(e.IsMaximized())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline const bool IsMaximized() const { return m_isMaximized; }

		EVENT_CLASS_TYPE(WindowMaximizeEvent)
	private:
		const WindowPtr m_window;
		const bool m_isMaximized;
	};
	// TODO: put Maximize event in window Resize event
	class A9_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(const WindowPtr window, float width, float height)
			: m_window(window)
			, m_width(width)
			, m_height(height)
		{}
		WindowResizeEvent(const WindowResizeEvent &e)
			: m_window(e.GetWindow())
			, m_width(e.GetWidth())
			, m_height(e.GetHeight())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline float GetWidth() const { return m_width; }
		inline float GetHeight() const { return m_height; }

		EVENT_CLASS_TYPE(WindowResizeEvent)
	private:
		const WindowPtr m_window;
		const float m_width, m_height;
	};
}