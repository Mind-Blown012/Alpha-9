#pragma once

#include "macros.hpp"
#include "components/component.hpp"

#include <glm/glm.hpp>

namespace Alpha9
{
	class A9_API Transform : public Component
	{
	public:
		Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f));
		Transform(const Transform& rhs) = default; // Need to make sure to not change Component attributes
		Transform(Transform&& lhs) = default; // Do not change component attributes

		// Eventually ApplyForce once physics engine is in place
		glm::vec3 Translate(const glm::vec3& amount);
		glm::vec3 Translate(float x = 1.0f, float y = 1.0f, float z = 1.0f);

		// TODO: Rotation implementation, for now just use setters and getters.

		
		glm::vec3 inline GetPosition() const { return m_position; };
		void inline SetPosition(const glm::vec3& pos) { m_position = pos; };
		void inline SetPosition(float x, float y) { m_position = glm::vec3(x, y, 0.0f); }; // When working with 2D coordinate systems, or when more convienient.
		void inline SetPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); };

		glm::vec3 inline GetRotation() const { return m_rotation; };
		void inline SetRotation(const glm::vec3& rot) { m_rotation = rot; };
		void inline SetRotation(float x, float y) { m_rotation = glm::vec3(x, y, 0.0f); }; // When working with 2D coordinate systems, or when more convienient.
		void inline SetRotation(float x, float y, float z) { m_rotation = glm::vec3(x, y, z); };

		glm::vec3 inline GetScale() const { return m_scale; };
		void inline SetScale(const glm::vec3& scale) { m_scale = scale; };
		void inline SetScale(float x, float y) { m_scale = glm::vec3(x, y, 0.0f); }; // When working with 2D coordinate systems, or when more convienient.
		void inline SetScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); };

		glm::mat4 GetModelMatrix() const;
	protected:
		// TODO: Quaternions for rotation (maybe)
		glm::vec3 m_position, m_rotation, m_scale;
	private:

	};
}