#pragma once

#include "macros.hpp"
#include "events.hpp"

// KeyDown, KeyUp

namespace Alpha9
{
	/**********KeyDown**********/
	class A9_API KeyDownEvent : public Event
	{
	public:
		KeyDownEvent(const WindowPtr window, const int& keyCode)
			: m_window(window)
			, m_keyCode(keyCode)
		{}
		KeyDownEvent(const KeyDownEvent& e)
			: m_window(e.GetWindow())
			, m_keyCode(e.GetKeyCode())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline const int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_TYPE(KeyDownEvent)
	private:
		const WindowPtr m_window;
		const int m_keyCode;
	};

	/**********KeyUp**********/
	class A9_API KeyUpEvent : public Event
	{
	public:
		KeyUpEvent(const WindowPtr window, const int& keyCode)
			: m_window(window)
			, m_keyCode(keyCode)
		{}
		KeyUpEvent(const KeyUpEvent& e)
			: m_window(e.GetWindow())
			, m_keyCode(e.GetKeyCode())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline const int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_TYPE(KeyUpEvent)
	private:
		const WindowPtr m_window;
		const int m_keyCode;
	};
}

// MouseButtonDown, MouseButtonUp, MouseMove, MouseScroll

namespace Alpha9
{
	/**********MouseButtonDown**********/
	class A9_API MouseButtonDownEvent : public Event
	{
	public:
		MouseButtonDownEvent(const WindowPtr window, const int& keyCode)
			: m_window(window)
			, m_button(keyCode)
		{}
		MouseButtonDownEvent(const MouseButtonDownEvent& e)
			: m_window(e.GetWindow())
			, m_button(e.GetButton())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline const int GetButton() const { return m_button; }

		EVENT_CLASS_TYPE(MouseButtonDownEvent)
	private:
		const WindowPtr m_window;
		const int m_button;
	};

	/**********MouseButtonUp**********/
	class A9_API MouseButtonUpEvent : public Event
	{
	public:
		MouseButtonUpEvent(const WindowPtr window, const int& keyCode)
			: m_window(window)
			, m_button(keyCode)
		{}
		MouseButtonUpEvent(const MouseButtonUpEvent& e)
			: m_window(e.GetWindow())
			, m_button(e.GetButton())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline const int GetButton() const { return m_button; }

		EVENT_CLASS_TYPE(MouseButtonUpEvent)
	private:
		const WindowPtr m_window;
		const int m_button;
	};

	/**********MouseMove**********/
	class A9_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(const WindowPtr window, double x, double y)
			: m_window(window)
			, m_x(x)
			, m_y(y)
		{}
		MouseMoveEvent(const MouseMoveEvent& e)
			: m_window(e.GetWindow())
			, m_x(e.GetX())
			, m_y(e.GetY())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline double GetX() const { return m_x; }
		inline double GetY() const { return m_y; }

		EVENT_CLASS_TYPE(MouseMoveEvent)
	private:
		const WindowPtr m_window;
		const double m_x, m_y;
	};

	/**********MouseScroll**********/
	class A9_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(const WindowPtr window, double xOffset, double yOffset)
			: m_window(window)
			, m_xOffset(xOffset)
			, m_yOffset(yOffset)
		{}
		MouseScrollEvent(const MouseScrollEvent& e)
			: m_window(e.GetWindow())
			, m_xOffset(e.GetXOffset())
			, m_yOffset(e.GetYOffset())
		{}

		inline const WindowPtr GetWindow() const { return m_window; }
		inline double GetXOffset() const { return m_xOffset; }
		inline double GetYOffset() const { return m_yOffset; }

		EVENT_CLASS_TYPE(MouseScrollEvent)
	private:
		const WindowPtr m_window;
		const double m_xOffset, m_yOffset;
	};
}