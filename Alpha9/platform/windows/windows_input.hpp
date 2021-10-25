#pragma once

#include "macros.hpp"
#include "events/events.hpp"
#include "key_codes.inl"


#ifdef A9_PLATFORM_WINDOWS

namespace Alpha9
{
	class A9_API Input
	{
	public:
		static void Init();


		// GetKey, GetKeyDown, and GetKeyUp, each with KeyCode and int arguments
		static bool GetKey(KeyCode);
		static bool GetKeyDown(KeyCode);
		static bool GetKeyUp(KeyCode);

		// GetMouseButton, GetMouseButtonDown, and GetMouseButtonUp, each with MouseButton and int arguments
		static bool GetMouseButton(MouseButton button);
		static bool GetMouseButtonDown(MouseButton button);
		static bool GetMouseButtonUp(MouseButton button);

		static const int NumKeys, NumMouseButtons;
	private:
		Input() = default;
		~Input() = default;

		static void Update();

		static void onKeyDown(Event& e);
		static void onKeyUp(Event& e);
		static void onMouseButtonDown(Event& e);
		static void onMouseButtonUp(Event& e);

		// So that private member functions can be called
		friend class EventManager;
		friend class Application;
	private:
		static bool s_isInitalized;

		// Storing the keys
		static std::vector<int> s_keys;
		static std::vector<int> s_lastKeys;
		// Storing the mouse buttons
		static std::vector<int> s_mouseButtons;
		static std::vector<int> s_lastMouseButtons;
	};
}

#endif