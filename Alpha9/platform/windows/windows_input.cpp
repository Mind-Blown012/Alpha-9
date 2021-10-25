#include "a9pch.hpp"

#include "windows_input.hpp"


#ifdef A9_PLATFORM_WINDOWS

namespace Alpha9
{
	const int Input::NumKeys = 119;
	const int Input::NumMouseButtons = 8;
	bool Input::s_isInitalized = false;
	std::vector<int> Input::s_keys;
	std::vector<int> Input::s_lastKeys;
	std::vector<int> Input::s_mouseButtons;
	std::vector<int> Input::s_lastMouseButtons;

	void Input::Init()
	{
		if (!s_isInitalized)
		{
			// Binding key and mouse events
			BIND_EVENT(KeyDownEvent, Input::onKeyDown);
			BIND_EVENT(KeyUpEvent, Input::onKeyUp);
			BIND_EVENT(MouseButtonDownEvent, Input::onMouseButtonDown);
			BIND_EVENT(MouseButtonUpEvent, Input::onMouseButtonUp);

			s_isInitalized = true;
		}
	}

	void Input::Update()
	{
		s_lastKeys = s_keys;
		s_lastMouseButtons = s_mouseButtons;
	}

	// Used by client
	bool Input::GetKey(KeyCode code)
	{ 
		bool inKeys = std::find(s_keys.begin(), s_keys.end(), (int)code) != s_keys.end();
		return  inKeys;
	}
	bool Input::GetKeyDown(KeyCode code)
	{
		bool inKeys = std::find(s_keys.begin(), s_keys.end(), (int)code) != s_keys.end();
		bool inLastKeys = std::find(s_lastKeys.begin(), s_lastKeys.end(), (int)code) != s_lastKeys.end();
		return (inKeys && !inLastKeys);
	}
	bool Input::GetKeyUp(KeyCode code)
	{
		bool inKeys = std::find(s_keys.begin(), s_keys.end(), (int)code) != s_keys.end();
		bool inLastKeys = std::find(s_lastKeys.begin(), s_lastKeys.end(), (int)code) != s_lastKeys.end();
		return (!inKeys && inLastKeys);
	}

	bool Input::GetMouseButton(MouseButton button)
	{
		bool inMouseButtons = std::find(s_mouseButtons.begin(), s_mouseButtons.end(), (int)button) != s_mouseButtons.end();
		return inMouseButtons;
	}
	bool Input::GetMouseButtonDown(MouseButton button)
	{
		bool inMouseButtons = std::find(s_mouseButtons.begin(), s_mouseButtons.end(), (int)button) != s_mouseButtons.end();
		bool inLastMouseButtons = std::find(s_lastMouseButtons.begin(), s_lastMouseButtons.end(), (int)button) != s_lastMouseButtons.end();
		return (inMouseButtons && !inLastMouseButtons);
	}
	bool Input::GetMouseButtonUp(MouseButton button)
	{
		bool inMouseButtons = std::find(s_mouseButtons.begin(), s_mouseButtons.end(), (int)button) != s_mouseButtons.end();
		bool inLastMouseButtons = std::find(s_lastMouseButtons.begin(), s_lastMouseButtons.end(), (int)button) != s_lastMouseButtons.end();
		return (!inMouseButtons && inLastMouseButtons);
	}


	void Input::onKeyDown(Event& e)
	{
		KeyDownEvent& en = static_cast<KeyDownEvent&>(e);
		
		if(std::find(s_keys.begin(), s_keys.end(), en.GetKeyCode()) == s_keys.end())
			s_keys.push_back(en.GetKeyCode());
	}
	void Input::onKeyUp(Event& e)
	{
		KeyUpEvent& en = static_cast<KeyUpEvent&>(e);

		auto codePos = std::find(s_keys.begin(), s_keys.end(), en.GetKeyCode());
		if (codePos != s_keys.end())
			s_keys.erase(codePos);
	}
	void Input::onMouseButtonDown(Event& e)
	{
		MouseButtonDownEvent& en = static_cast<MouseButtonDownEvent&>(e);

		if (std::find(s_mouseButtons.begin(), s_mouseButtons.end(), en.GetButton()) == s_mouseButtons.end())
			s_mouseButtons.push_back(en.GetButton());
	}
	void Input::onMouseButtonUp(Event& e)
	{
		MouseButtonUpEvent& en = static_cast<MouseButtonUpEvent&>(e);

		auto codePos = std::find(s_mouseButtons.begin(), s_mouseButtons.end(), en.GetButton());
		if (codePos != s_mouseButtons.end())
			s_mouseButtons.erase(codePos);
	}
}

#endif