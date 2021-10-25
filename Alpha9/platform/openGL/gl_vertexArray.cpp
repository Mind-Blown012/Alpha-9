#include "a9pch.hpp"

#include "gl_vertexArray.hpp"

#include <glad/glad.h>

namespace Alpha9
{
	GLVertexArray::GLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererID);
		glBindVertexArray(m_rendererID);
	}
	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void GLVertexArray::Bind() const
	{
		glBindVertexArray(m_rendererID);
	}
	void GLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void GLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_rendererID);
		vertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		m_vertexBuffers.push_back(vertexBuffer);
	}
	void GLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_rendererID);
		indexBuffer->Bind();

		m_indexBuffer = indexBuffer;
	}

}
