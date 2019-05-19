#pragma once

#include <string>
#include <memory>
#include "core.hpp"

namespace Alpha9
{

	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string &title = "Alpha-9 Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	class A9_API WindowBase
	{
	public:
		using WindowPtr = WindowBase*;

		virtual ~WindowBase() {}

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void Update() = 0;

		virtual void *GetNativeWindow() const = 0;

		// Defined for each specific platform
		static WindowBase *Create(
			const WindowProperties& properties = WindowProperties());
	};
}