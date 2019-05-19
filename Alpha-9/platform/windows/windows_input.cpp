#include "a9pch.hpp"

#include "windows_input.hpp"

namespace Alpha9
{
	std::unique_ptr<Input> Input::s_instance = nullptr;

	Input::Input()
	{
		A9_CORE_ASSERT(!s_instance, "Error: cannot have more than one input manager!");
		
		if (!s_instance)
			s_instance = std::make_unique<Input>(*this);
	}


	/***************KEYBOARD INPUT*******************/
	// GetKey, GetKeyDown, and GetKeyUp, each with KeyCode and int arguments
	bool Input::GetKey(int code)
	{
		return false;
	}
	bool Input::GetKey(KeyCode code)
	{
		return GetKey(static_cast<int>(code));
	}
	bool Input::GetKeyDown(int code)
	{
		return false;
	}
	bool Input::GetKeyDown(KeyCode code)
	{
		return false;
	}
	bool Input::GetKeyUp(int code)
	{
		return false;
	}
	bool Input::GetKeyUp(KeyCode code)
	{
		return false;
	}
}