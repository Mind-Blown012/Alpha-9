#include "a9pch.hpp"

#include "camera.hpp"
#include "renderer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Alpha9
{
#ifdef A9_PLATFORM_WINDOWS
	RenderAPI Renderer::s_renderAPI = RenderAPI::OpenGL;
#else
	RenderAPI Renderer::s_renderAPI = RenderAPI::None;
#endif
	glm::vec4& Renderer::s_clearColor = glm::vec4(0, 0, 0, 0);

	void Renderer::Clear()
	{
		glClearColor(s_clearColor.r, s_clearColor.g, s_clearColor.b, s_clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_viewProjectionMatrix", Camera::GetMainCamera()->GetViewProjectionMatrix());
		
		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}