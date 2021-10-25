#include "a9pch.hpp"

#include "windows/windows_input.hpp"
#include "rendering/renderer.hpp"
#include "rendering/camera.hpp"
#include "events/events.hpp"
#include "application.hpp"
#include "game_base.hpp"

#include <glad/glad.h>

namespace Alpha9
{
	Application& Application::Instance()
	{
		static Application instance;

		return instance;
	}

	Application::Application()
	{
		init();
		WindowBase::Create(*(new WindowProperties("Alpha 9 Engine", false)));
		Camera::s_mainCamera.reset(new Camera(glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, false));
	}

	Application::~Application()
	{
		cleanup();
	}

	void Application::init()
	{
		Logger::Init();
		Input::Init();
	}
	void Application::cleanup()
	{
		glfwTerminate();
		glfwSetErrorCallback(NULL);
	}

	void Application::Run(Game* g)
	{
		m_isRunning = true;
		BIND_EVENT(EngineStopEvent, [this](Event& e) -> 
			void {
				m_isRunning = false;
				cleanup();
			}
		);

		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		g->Start();
		// Main application loop
		while (m_isRunning)
		{
			// Resolve all events
			GetEventManager().Resolve();
			if (!m_isRunning) break;
			Renderer::Clear();

			g->Render();
			g->Update();
			Window::GetMainWindow()->Update();
			Input::Update();
		}
	}

	void Application::Update(float deltaTime)
	{
		
	}

	Application& GetMainApplication()
	{
		return Application::Instance();
	}
	EventManager& GetEventManager()
	{
		return EventManager::Instance();
	}
}