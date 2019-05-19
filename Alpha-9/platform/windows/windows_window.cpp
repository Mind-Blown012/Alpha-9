#include "a9pch.hpp"
#include "windows_window.hpp"
#include "events/event.hpp"

#include <glad/glad.h>

namespace Alpha9
{
	EventManager &GetEventManager();


	/***************STATIC WINDOW EVENT FUNCTIONS*******************/
	// Each one of these functions will call the related function on the window
	void OnWindowClose(Event &e)
	{
		WindowCloseEvent &ev = static_cast<WindowCloseEvent&>(e);
		Window *win = static_cast<Window *>(glfwGetWindowUserPointer(ev.GetWindow()));
		win->OnWindowClose(ev);
	}
	void OnWindowMove(Event &e)
	{
		WindowMoveEvent &ev = static_cast<WindowMoveEvent&>(e);
		Window *win = static_cast<Window *>(glfwGetWindowUserPointer(ev.GetWindow()));
		win->OnWindowMove(ev);
	}
	void OnWindowFocus(Event &e)
	{
		WindowFocusEvent &ev = static_cast<WindowFocusEvent&>(e);
		Window *win = static_cast<Window *>(glfwGetWindowUserPointer(ev.GetWindow()));
		win->OnWindowFocus(ev);
	}
	void OnWindowResize(Event &e)
	{
		WindowResizeEvent &ev = static_cast<WindowResizeEvent&>(e);
		Window *win = static_cast<Window *>(glfwGetWindowUserPointer(ev.GetWindow()));
		win->OnWindowResize(ev);
	}
	void OnWindowMaximize(Event &e)
	{
		WindowMaximizeEvent &ev = static_cast<WindowMaximizeEvent&>(e);
		Window *win = static_cast<Window *>(glfwGetWindowUserPointer(ev.GetWindow()));
		win->OnWindowMaximize(ev);
	}

	/***************WINDOW METHODS*******************/
	bool Window::s_isGLFWinitalized = false;

	void glfwErrorCallback(int error, const char *description)
	{
		A9_CORE_ERROR("GLFW error ({}): {}", error, description);
	}

	Window::Window(const WindowProperties &properties)
	{
		init(properties);
	}
	Window::~Window()
	{
		// TODO: shutdown() method
		glfwDestroyWindow(m_window);
	}
	unsigned int Window::GetWidth() const
	{
		return m_data.Width;
	}
	unsigned int Window::GetHeight() const
	{
		return m_data.Height;
	}
	void *Window::GetNativeWindow() const
	{
		return m_window;
	}
	void Window::init(const WindowProperties &props)
	{
		m_data = props;

		/***************INITALIZING GLFW*******************/
		if (!s_isGLFWinitalized)
		{
			A9_CORE_INFO("Running with glfw version {}", glfwGetVersionString());
			glfwSetErrorCallback(glfwErrorCallback);

			int glfw_sucess = glfwInit();
			A9_CORE_ASSERT(glfw_sucess==GLFW_TRUE, "Failed to initalize glfw!");
			s_isGLFWinitalized = true;
		}

		/***************CREATING WINDOW*******************/
		A9_CORE_INFO("Creating window \"{}\" ({},{})", m_data.Title,
			m_data.Width, m_data.Height);

		m_window = glfwCreateWindow(m_data.Width, m_data.Height, m_data.Title.c_str(), 
			NULL, NULL);
		A9_CORE_ASSERT(m_window, "Failed to create window!");
		/***************CONTEXT CREATION / GLAD*******************/
		glfwMakeContextCurrent(m_window);
		// GLAD!
		int glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		A9_CORE_ASSERT(glad_status, "Failed to initalize Glad!");
		glfwSetWindowUserPointer(m_window, this);

		/***************GLFW CALLBACK FUNCTIONS*******************/
		/*WINDOW CALLBACKS*/
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
		{
			WindowCloseEvent e{ window };
			TRIGGER_EVENT(e);
		});
		glfwSetWindowPosCallback(m_window, [](GLFWwindow *window, int x, int y)
		{
			WindowMoveEvent e{ window, static_cast<unsigned int>(x), static_cast<unsigned int>(y) };
			TRIGGER_EVENT(e);
		});
		glfwSetWindowFocusCallback(m_window, [](GLFWwindow *window, int focused)
		{
			WindowFocusEvent e{ window, static_cast<bool>(focused) };
			TRIGGER_EVENT(e);
		});
		glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow *window, int maximized)
		{
			WindowMaximizeEvent e{ window, static_cast<bool>(maximized) };
			TRIGGER_EVENT(e);
		});
		// glfwSetWindowSizeCallback is in screen coordinates, not pixels so this is used
		glfwSetWindowContentScaleCallback(m_window, [](GLFWwindow *window, float width, float height)
		{
			WindowResizeEvent e{ window, width, height };
			TRIGGER_EVENT(e);
		});
		/*INPUT CALLBACKS*/
		// key
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				// TODO: when Input system implemented, do a `toA9Keycode(GLFW_KEY)` function
				KeyDownEvent e{ window, key };
				TRIGGER_EVENT(e);
			}
			else if (action == GLFW_RELEASE)
			{
				KeyUpEvent e{ window, key };
				TRIGGER_EVENT(e);
			}

		});
		// Mouse
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				// TODO: when Input system implemented, do a `toA9ButtonCode(GLFW_KEY)` function
				MouseButtonDownEvent e{ window, button };
				TRIGGER_EVENT(e);
			}
			else if (action == GLFW_RELEASE)
			{
				MouseButtonUpEvent e{ window, button };
				TRIGGER_EVENT(e);
			}
		});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double x, double y)
		{
			MouseMoveEvent e{ window, x, y };
			TRIGGER_EVENT(e);
		});
		glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset)
		{
			MouseScrollEvent e{ window, xOffset, yOffset };
			TRIGGER_EVENT(e);
		});

		/***************EVENT BINDING*******************/
		BIND_EVENT(WindowCloseEvent, Alpha9::OnWindowClose);
		BIND_EVENT(WindowMoveEvent, Alpha9::OnWindowMove);
		BIND_EVENT(WindowFocusEvent, Alpha9::OnWindowFocus);
		BIND_EVENT(WindowResizeEvent, Alpha9::OnWindowResize);
		BIND_EVENT(WindowMaximizeEvent, Alpha9::OnWindowMaximize);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	WindowBase *WindowBase::Create(const WindowProperties &properties)
	{
		return new Window(properties);
	}

	/***************WINDOW EVENTS*******************/
	
	void Window::OnWindowClose(WindowCloseEvent &e)
	{

	}
	void Window::OnWindowMove(WindowMoveEvent &e)
	{

	}
	void Window::OnWindowFocus(WindowFocusEvent &e)
	{

	}
	void Window::OnWindowResize(WindowResizeEvent &e)
	{

	}
	void Window::OnWindowMaximize(WindowMaximizeEvent &e)
	{

	}
}