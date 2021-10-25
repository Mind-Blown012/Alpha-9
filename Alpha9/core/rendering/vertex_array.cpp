#include "a9pch.hpp"

#include "renderer.hpp"
#include "vertex_array.hpp"
#include "openGL/gl_vertexArray.hpp"

namespace Alpha9
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			A9_CORE_ASSERT(false, "RenderAPI of 'None' is currently not supported!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new GLVertexArray();
		}
		A9_CORE_ERROR("Unsupported RenderAPI chosen! ({0})", (int)Renderer::GetAPI());
		return nullptr;
	}
}