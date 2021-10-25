#include "a9pch.hpp"

#include "spdlog/fmt/ostr.h"

#include "windows_window.hpp"
#include "rendering/window.hpp"
#include "openGL/gl_context.hpp"

#include "macros.hpp"
#include "events/events.hpp"
#include "time.hpp"


#ifdef A9_PLATFORM_WINDOWS

namespace Alpha9
{
	static bool s_isGLFWInitalized = false;
	Window* Window::s_mainWindow = nullptr;

	static void glfwErrorCallbackFn(int error, const char* description)
	{
		A9_CORE_ERROR("GLFW Error #{0}: {1}", error, description);
	}

	
	WindowBase *WindowBase::Create(const WindowProperties& props)
	{
		return new Window(props);
	}

	Window::Window(const WindowProperties& props)
	{
		// Copying the properties
		m_props = props;
		init();
	}
	Window::Window(const Window& rhs)
	{
		// Copying the properties
		m_props = rhs.m_props;
		init();
	}
	Window::Window(Window&& lhs)
	{
		// Copying the properties, window and context
		// Also setting the left-side properties to null values
		m_props = std::move(lhs.m_props);
		m_context = std::move(lhs.m_context);
		m_window = std::move(lhs.m_window);

		init();
	}
	Window::~Window()
	{
		shutdown();
	}

	void Window::init()
	{
		if (s_mainWindow == nullptr)
			s_mainWindow = this;

		if (!s_isGLFWInitalized)
		{
			int GLFWInitializationError = glfwInit();
			// Make sure that GLFW initialized successfully 
			A9_CORE_ASSERT(GLFWInitializationError, "Error initializing GLFW!");
			// Set the GLFW error callback to `glfwErrorCallbackFn`
			glfwSetErrorCallback(glfwErrorCallbackFn);
			// Set GLFW initialized to true
			s_isGLFWInitalized = true;
		}
		
		/*****Create Window:*****/
		// Check if the window should be full-screen
		if (m_props.Fullscreen)
		{
			//A9_INFO("Creating full-screen window \"{0}\"", m_props.Title);
			m_window = glfwCreateWindow((int)m_props.Width, (int)m_props.Height,
				m_props.Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
		}
		else
		{
			//A9_INFO("Creating window \"{0}\": ({1}, {2})", m_props.Title, m_props.Width, m_props.Height);
			m_window = glfwCreateWindow((int)m_props.Width, (int)m_props.Height,
				m_props.Title.c_str(), nullptr, nullptr);
		}

		/********************CONTEXT AND VSYNC********************/
		m_context = new GLContext(m_window);
		m_context->Init();
		// VSync
		m_context->SetVSync(true);

		/********************GLFW Callback Functions*******************/
		/**********Window Callbacks **********/
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowCloseEvent e{ window };
			TRIGGER_EVENT(e);
		});
		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y)
		{
			WindowMoveEvent e{ window, static_cast<unsigned int>(x), static_cast<unsigned int>(y) };
			TRIGGER_EVENT(e);
		});
		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused)
		{
			WindowFocusEvent e{ window, static_cast<bool>(focused) };
			TRIGGER_EVENT(e);
		});
		glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* window, int maximized)
		{
			WindowMaximizeEvent e{ window, static_cast<bool>(maximized) };
			TRIGGER_EVENT(e);
		});
		// glfwSetWindowSizeCallback is in screen coordinates, not pixels so this is used
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent e{ window, width, height };
			TRIGGER_EVENT(e);
		});
		/**********Input Callbacks **********/
		// Key
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
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y)
		{
			MouseMoveEvent e{ window, x, y };
			TRIGGER_EVENT(e);
		});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			MouseScrollEvent e{ window, xOffset, yOffset };
			TRIGGER_EVENT(e);
		});
		
		/***************Binding Events*******************/
		BIND_CLASS_EVENT(WindowCloseEvent, Window::OnWindowClose, this);
		BIND_CLASS_EVENT(WindowMoveEvent, Window::OnWindowMove, this);
	}
	void Window::shutdown()
	{
		if(m_window)
			// Destroy the window
			glfwDestroyWindow(m_window);
	}

	void Window::Update()
	{
		glfwPollEvents();
		m_context->SwapBuffers();
	}

	/***************Window Events*******************/
	void Window::OnWindowClose(Event& e)
	{
		if (this == s_mainWindow) {
			EngineStopEvent e{ Time::getTime() };
			TRIGGER_EVENT(e);
		}
		shutdown();
	}
	void Window::OnWindowMove(Event& e)
	{
		WindowMoveEvent &en = dynamic_cast<WindowMoveEvent&>(e);

		//A9_INFO("Window moved to: ({0}, {1})", en.GetX(), en.GetY());
	}
}
// Logging
std::ostream& operator<<(std::ostream& os, const Alpha9::Window& win)
{
	if (win.IsFullscreen())
		os << "Full-Screen ";
	os << "Window: \"" << win.GetTitle() << "\"";
	if (!win.IsFullscreen())
		os << ", (" << win.GetWidth() << ", " << win.GetHeight() << ")";
	return os;
}

#endif