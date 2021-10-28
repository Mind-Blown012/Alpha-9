#pragma once

#include "vertex_array.hpp"
#include "shader.hpp"
#include "macros.hpp"
#include "shader.hpp"
#include "transform.hpp"

#include <memory>

#include <glm/vec4.hpp>

namespace Alpha9
{
	enum class RenderAPI
	{
		None = 0,
		OpenGL
	};

	class A9_API Renderer
	{
	public:
		inline static RenderAPI GetAPI() { return s_renderAPI; };

		inline static void SetClearColor(const glm::vec4& clearColor) { s_clearColor = clearColor; }
		static void Clear();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Transform& transform);
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
	private:
		static RenderAPI s_renderAPI;
		static glm::vec4& s_clearColor;
	};
}