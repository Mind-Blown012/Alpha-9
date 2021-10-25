#include "a9pch.hpp";

#include "transform.hpp"


namespace Alpha9
{
	Transform::Transform(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
		: m_position(position), m_rotation(rotation), m_scale(scale)
	{

	}

	glm::mat4 Transform::GetModelMatrix()
	{
		return glm::translate(glm::mat4(1.0f), m_position);
	}
}
