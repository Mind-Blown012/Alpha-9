#include "a9pch.hpp"

#include "camera.hpp"
#include "events/events.hpp"
#include "application.hpp"

namespace Alpha9
{
	std::shared_ptr<Camera> Camera::s_mainCamera;
	std::vector<Camera*> Camera::s_allCameras;
	bool Camera::s_isInitalized = false;

	Camera::Camera(bool isOrthographic)
	{
		Camera(glm::vec3(0.0f), 0.0f, isOrthographic);
	}
	Camera::Camera(const glm::vec3& position, const float& rotation, bool isOrthographic)
		: m_position(position)
		, m_rotation(rotation)
		, m_isOrthographic(isOrthographic)
	{
		if (!s_isInitalized)
		{
			BIND_EVENT(WindowResizeEvent, Camera::WindowResize);
			s_isInitalized = true;
		}

		s_allCameras.push_back(this);

		if (isOrthographic)
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
			m_projectionMatrix = glm::perspective(70.0f, aspectRatio, 0.1f, 1000.0f);
		}
		m_viewMatrix = glm::mat4(1.0f);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
		// Since the position and rotation changed:
		RecalculateViewMatrix();
	}

	Camera::~Camera()
	{
		auto i = std::find(s_allCameras.begin(), s_allCameras.end(), this);
		
		if(i != s_allCameras.end())
			s_allCameras.erase(i);
	}

	const void Camera::SetIsOrthographic(bool isOrthographic)
	{
		if (isOrthographic == m_isOrthographic)
			return;

		if (isOrthographic)
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
			m_projectionMatrix = glm::perspective(70.0f, aspectRatio, 0.1f, 1000.0f);
		}
			
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		// TODO: Create Transform class
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_viewMatrix = glm::inverse(transform);
		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void Camera::WindowResize(Event& e)
	{
		WindowResizeEvent &en = dynamic_cast<WindowResizeEvent&>(e);
		for (auto cam : s_allCameras)
		{
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
				cam->m_projectionMatrix = glm::perspective(70.0f, aspectRatio, 0.1f, 1000.0f);
			}
			cam->RecalculateViewMatrix();
		}
	}
}