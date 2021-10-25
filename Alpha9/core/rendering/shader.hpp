#pragma once

#include "macros.hpp"

#include <string>
#include <glm/glm.hpp>

namespace Alpha9
{
	class A9_API Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);

		// Move constructors/operators are allowed but not copy constructors/operators
		Shader(Shader&&);
		Shader& operator=(Shader&&);

		void Bind();
		void Unbind();

		virtual ~Shader();
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		Shader(const Shader& rhs) = delete;
		Shader& operator=(const Shader& rhs) = delete;

		uint32_t m_renderID;
	};
}