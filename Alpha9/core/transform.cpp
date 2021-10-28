#include "a9pch.hpp"

#include "transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/euler_angles.hpp"

namespace Alpha9
{
	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: m_position(position), m_rotation(rotation), m_scale(scale)
	{}

	// Changes the position by specified amount, and then returns the modified position.
	glm::vec3 Transform::Translate(const glm::vec3& amount)
	{
		m_position += amount;
		return m_position;
	}
	glm::vec3 Transform::Translate(float x, float y, float z)
	{
		m_position += glm::vec3(x, y, z);
		return m_position;
	}


	glm::mat4 Transform::GetModelMatrix() const
	{
		// TODO: Possibly create a global constant for the identity matrix, as it's used often
		return glm::translate(glm::mat4(1.0f), m_position)
			* glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z)
			* glm::scale(glm::mat4(1.0f), m_scale);
	}
}
