#include "a9pch.hpp"

#include "buffers.hpp"
#include "openGL/gl_buffers.hpp"
#include "renderer.hpp"

namespace Alpha9
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			A9_CORE_ASSERT(false, "RenderAPI of 'None' is currently not supported!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new GLVertexBuffer(vertices, size);
		}
		A9_CORE_ERROR("Unsupported RenderAPI chosen! ({0})", (int)Renderer::GetAPI());
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			A9_CORE_ASSERT(false, "RenderAPI of 'None' is currently not supported!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new GLIndexBuffer(indices, count);
		}
		A9_CORE_ERROR("Unsupported RenderAPI chosen! ({0})", (int)Renderer::GetAPI());
		return nullptr;
	}
}