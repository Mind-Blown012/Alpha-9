#pragma once

#include "macros.hpp"
#include "events/events.hpp"
#include "transform.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Alpha9
{
	class Application;

	// TODO: Add extra parameters to the Camera constructors.

	class A9_API Camera
	{
	public:
		Camera(bool isOrthographic = true);
		Camera(const glm::vec3& position, const glm::vec3& rotation, bool isOrthographic = true);
		virtual ~Camera();

		virtual inline const glm::vec3 GetPosition() const { return m_transform.GetPosition(); }
		virtual inline void SetPosition(const glm::vec3& position) { m_transform.SetPosition(position); };
		virtual inline void Translate(const glm::vec3& amount) { m_transform.Translate(amount); }

		virtual inline const glm::vec3 GetRotation() const { return m_transform.GetRotation(); }
		virtual inline void SetRotation(const glm::vec3& rotation) { m_transform.SetRotation(rotation); };

		virtual inline const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
		virtual const glm::mat4 GetViewMatrix() const;
		virtual const glm::mat4 GetViewProjectionMatrix() const;

		virtual inline const bool IsOrthographic() const { return m_isOrthographic; }
		virtual void SetIsOrthographic(bool isOrthographic);

		static inline const std::shared_ptr<Camera>& GetMainCamera() { return s_mainCamera; }
		static inline const std::vector<Camera*>& GetAllCameras() { return s_allCameras; }
	
		friend class Application;
	protected:
		glm::mat4 m_projectionMatrix;

		// Scale is to be ommitted
		Transform m_transform;
	private:
		void init();

		static bool s_isInitalized;
		// TODO: Perspective camera
		bool m_isOrthographic = true;
		static std::shared_ptr<Camera> s_mainCamera;
		static std::vector<Camera*> s_allCameras;

		static void WindowResize(Event&);
	};
}