#pragma once

#include <string>
#include <memory>

#include "macros.hpp"

namespace Alpha9
{
	// If full-screen is set to true then width and height don't matter
	struct A9_API WindowProperties
	{
		// TODO: Full screen and V sync support

		WindowProperties(std::string title = "Alpha9 Engine", bool fullscreen = false);
		WindowProperties(size_t width, size_t height, std::string title = "Alpha9 Engine", bool fullscreen = false);
		
		WindowProperties(const WindowProperties& rhs);
		WindowProperties(WindowProperties&& lhs);

		// Assignment operators
		WindowProperties& operator=(const WindowProperties& rhs);
		WindowProperties& operator=(WindowProperties&& lhs);
		
		size_t Width, Height;
		bool Fullscreen;
		std::string Title;
	};

	class A9_API WindowBase
	{
	public:
		virtual ~WindowBase() = default;

		/********************GETTERS********************/
		virtual inline size_t GetWidth() const { return m_props.Width; };
		virtual inline size_t GetHeight() const { return m_props.Height; };
		virtual inline std::string GetTitle() const { return m_props.Title; };
		virtual inline bool IsFullscreen() const { return m_props.Fullscreen; };

		/********************SETTERS********************/
		// TODO: Have setting width, height, etc. actually set them in the window
		virtual inline void SetWidth(size_t width) { m_props.Width = width; };
		virtual inline void SetHeight(size_t height) { m_props.Height = height; };
		virtual inline void SetTitle(std::string title) { m_props.Title = title; };
		virtual inline void SetFullscreen(bool fullscreen) { m_props.Fullscreen = fullscreen; };

		virtual void Update() = 0;

		virtual inline void *GetNativeWindow() const = 0;

		static WindowBase *Create(const WindowProperties &props = WindowProperties());
	protected:
		WindowProperties m_props;
	};
}
// Logging
std::ostream& operator<<(std::ostream&, const Alpha9::WindowProperties&);