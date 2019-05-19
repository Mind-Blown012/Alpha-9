#pragma once

#include "core.hpp"
#include "events/event.hpp"
#include "key_codes.hpp"

namespace Alpha9
{
	class A9_API Input
	{
	public:
		Input();
		~Input() = default;

		
		// GetKey, GetKeyDown, and GetKeyUp, each with KeyCode and int arguments
		static bool GetKey(int code);
		static bool GetKey(KeyCode code);
		static bool GetKeyDown(int code);
		static bool GetKeyDown(KeyCode code);
		static bool GetKeyUp(int code);
		static bool GetKeyUp(KeyCode code);

		// GetMouseButton, GetMouseButtonDown, and GetMouseButtonUp, each with MouseButton and int arguments
		static bool GetMouseButton(int button);
		static bool GetMouseButton(MouseButton button);
		static bool GetMouseButtonDown(int button);
		static bool GetMouseButtonDown(MouseButton button);
		static bool GetMouseButtonUp(int button);
		static bool GetMouseButtonUp(MouseButton button);
	private:
		static std::unique_ptr<Input> s_instance;

		// Storing the keys
		static std::vector<bool> 
	};
}