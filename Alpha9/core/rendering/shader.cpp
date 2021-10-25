#include "a9pch.hpp"

#include "shader.hpp"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Alpha9
{
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
		: m_renderID(0)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send shader data to OpenGL
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		// Error handling
		GLint compileStatus = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// String for the error log
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

			// Compile error that can't be recovered from, delete shader
			glDeleteShader(vertexShader);

			A9_CORE_ERROR("Vertex shader compilation failure! {0}", errorLog.data());
			return;
		}

		// SAME exact thing for the fragment shader
		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send shader data to OpenGL
		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(fragmentShader);

		// Error handling
		compileStatus = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// String for the error log
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

			// Compile error that can't be recovered from, delete both shaders
			// so that no data is leaked
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);


			A9_CORE_ERROR("Fragment shader compilation failure! {0}", errorLog.data());
			return;
		}

		// Done compiling shaders, get a program handle
		m_renderID = glCreateProgram();

		// Attach the shaders to the program
		glAttachShader(m_renderID, vertexShader);
		glAttachShader(m_renderID, fragmentShader);

		// Link the program
		glLinkProgram(m_renderID);

		GLint linkError = 0;
		glGetProgramiv(m_renderID, GL_LINK_STATUS, &linkError);
		if (linkError == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_renderID, GL_INFO_LOG_LENGTH, &maxLength);

			// String for the error log
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(m_renderID, maxLength, &maxLength, &errorLog[0]);

			// Delete the program
			glDeleteProgram(m_renderID);
			// Compile error that can't be recovered from, delete both shaders
			// so that no data is leaked
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);


			A9_CORE_ERROR("Shader link failure! {0}", errorLog.data());
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_renderID, vertexShader);
		glDetachShader(m_renderID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_renderID);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_renderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	Shader::Shader(Shader&& lhs)
	{
		m_renderID = lhs.m_renderID;
		lhs.m_renderID = 0;
	}
	Shader& Shader::operator=(Shader&& lhs)
	{
		if (this != &lhs)
		{
			m_renderID = lhs.m_renderID;
			lhs.m_renderID = 0;
		}
		return *this;
	}

	void Shader::Bind()
	{
		glUseProgram(m_renderID);
	}
	void Shader::Unbind()
	{
		glUseProgram(0);
	}
}