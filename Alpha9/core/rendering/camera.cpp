#include "a9pch.hpp"

#include "camera.hpp"
#include "events/events.hpp"
#include "application.hpp"

// TODO: Refactor and cleanup Camera class, esspecially the WindowResize fn
// Might be a good idea to rewrite with events, using more fields that change
// when components are updated. This would allow for an accessible transform.

namespace Alpha9
{
	std::shared_ptr<Camera> Camera::s_mainCamera;
	std::vector<Camera*> Camera::s_allCameras;
	bool Camera::s_isInitalized = false;

	Camera::Camera(bool isOrthographic)
	{
		Camera(glm::vec3(), glm::vec3(), isOrthographic);
	}
	Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, bool isOrthographic)
		: m_isOrthographic(isOrthographic),
		m_transform(position, rotation)
	{
		if (!s_isInitalized)
		{
			BIND_EVENT(WindowResizeEvent, Camera::WindowResize);
			s_isInitalized = true;
		}

		s_allCameras.push_back(this);

		init();
	}

	Camera::~Camera()
	{
		auto i = std::find(s_allCameras.begin(), s_allCameras.end(), this);
		
		if(i != s_allCameras.end())
			s_allCameras.erase(i);
	}

	void Camera::SetIsOrthographic(bool isOrthographic)
	{
		if (isOrthographic == m_isOrthographic)
			return;
		m_isOrthographic = isOrthographic;

		init();
	}

	// TODO: Rename this later
	void Camera::init()
	{
		if (m_isOrthographic)
		{
			float width = (float)Window::GetMainWindow()->GetWidth();
			float height = (float)Window::GetMainWindow()->GetHeight();
			m_projectionMatrix = glm::ortho(0.0f, width, height, 0.0f, 0.1f, 1000.0f);
		}
		else
		{
			float width = (float)Window::GetMainWindow()->GetWidth();
			float height = (float)Window::GetMainWindow()->GetHeight();
			float aspectRatio = width / height;
			m_projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
		}
	}

	const glm::mat4 Camera::GetViewMatrix() const
	{
		// Since world space depends on the camera's position, it must move opposite
		return glm::inverse(m_transform.GetModelMatrix());
	}
	const glm::mat4 Camera::GetViewProjectionMatrix() const
	{
		return m_projectionMatrix * GetViewMatrix();
	}

	// TODO: Fix camera bug where screen will not fully resize when camera does
	
	void Camera::WindowResize(Event& e)
	{
		WindowResizeEvent &en = dynamic_cast<WindowResizeEvent&>(e);
		for (auto cam : s_allCameras)
		{
			// Not an easy way around of the repetitive code,
			// since this has to be called on each camera individually.
			if (cam->m_isOrthographic)
			{
				float width = (float)en.GetWidth();
				float height = (float)en.GetHeight();
				cam->m_projectionMatrix = glm::ortho(0.0f, width, height, 0.0f, 0.0f, 1000.0f);
			}
			else
			{
				float width = (float)en.GetWidth();
				float height = (float)en.GetHeight();
				float aspectRatio = width / height;
				cam->m_projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
			}
		}
	}
}