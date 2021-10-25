#include "a9pch.hpp"

#include "macros.hpp"
#include "gl_context.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Alpha9
{
	GLContext::GLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		A9_CORE_ASSERT(windowHandle, "Window handle is invalid (nullptr)!")
	}

	void GLContext::Init()
	{
		// Context
		glfwMakeContextCurrent(m_windowHandle);
		// GLAD
		int glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		// Error handling
		A9_CORE_ASSERT(glad_status, "Failed to initialize Glad!");

		/**OPENGL INFO**/
		A9_CORE_INFO("OpenGL Version {0}: {1}", glGetString(GL_VERSION), glGetString(GL_RENDERER));
	}

	void GLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}