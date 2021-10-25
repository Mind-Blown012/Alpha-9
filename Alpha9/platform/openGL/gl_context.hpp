#pragma once

#include "macros.hpp"
#include <GLFW/glfw3.h>
#include "rendering/context.hpp"

struct GLFWwindow;

namespace Alpha9
{
	class A9_API GLContext : public Context
	{
	public:
		GLContext(GLFWwindow*);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual inline void SetVSync(bool isVSync) override 
		{
			// Swap interval of 1 if set to true, 0 if false
			glfwSwapInterval((int)isVSync);
			m_isUsingVSync = isVSync;
		};
		virtual inline bool IsVSync() const override { return m_isUsingVSync; };
	private:
		GLFWwindow* m_windowHandle;
	};
}