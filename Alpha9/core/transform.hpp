#pragma once

#include "macros.hpp"
#include "components/component.hpp"

#include <glm/glm.hpp>

namespace Alpha9
{
	class A9_API Transform : public Component
	{
	public:
		Transform(glm::vec3& position = glm::vec3(), glm::vec3& rotation = glm::vec3(), glm::vec3& scale = glm::vec3());
		Transform(const Transform& rhs) = default; // Need to make sure to not change Component attributes
		Transform(Transform&& lhs) = default; // Do not change component attributes

		glm::mat4 GetModelMatrix();
	protected:
		// TODO: Quaternions for rotation
		glm::vec3 m_position, m_rotation, m_scale;
	private:

	};
}