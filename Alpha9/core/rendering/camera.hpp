#pragma once

#include "macros.hpp"
#include "events/events.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Alpha9
{
	class Application;

	class A9_API Camera
	{
	public:
		Camera(bool isOrthographic = true);
		Camera(const glm::vec3& position, const float& rotation, bool isOrthographic = true);
		virtual ~Camera();

		virtual inline const glm::vec3& GetPosition() { return m_position; }
		virtual const void SetPosition(const glm::vec3& position) { m_position = position; };

		virtual inline const float& GetRotation() { return m_rotation; }
		virtual inline const void SetRotation(const float& rotation) { m_rotation = rotation; };

		virtual inline const glm::mat4& GetViewMatrix() { return m_viewMatrix; }
		virtual inline const glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
		virtual inline const glm::mat4& GetViewProjectionMatrix() { return m_viewMatrix; }

		virtual inline const bool IsOrthographic() { return m_isOrthographic; }
		virtual const void SetIsOrthographic(bool isOrthographic);

		static inline const std::shared_ptr<Camera>& GetMainCamera() { return s_mainCamera; }
		static inline const std::vector<Camera*>& GetAllCameras() { return s_allCameras; }
	
		friend class Application;
	protected:
		glm::mat4 m_projectionMatrix, m_viewMatrix, m_viewProjectionMatrix;
		glm::vec3 m_position;
		float m_rotation;

		virtual void RecalculateViewMatrix();
	private:
		static bool s_isInitalized;
		// TODO: Perspective camera
		bool m_isOrthographic = true;
		static std::shared_ptr<Camera> s_mainCamera;
		static std::vector<Camera*> s_allCameras;

		static void WindowResize(Event&);
	};
}