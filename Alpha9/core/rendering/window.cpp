#include "a9pch.hpp"

#include "window.hpp"

namespace Alpha9
{
	/********************WINDOW PROPERTIES********************/
	/**********CONSTRUCTORS**********/
	WindowProperties::WindowProperties(std::string title, bool fullscreen)
		: Width(1280)
		, Height(720)
		, Title(title)
		, Fullscreen(fullscreen)
	{}
	WindowProperties::WindowProperties(size_t width, size_t height, std::string title, bool fullscreen)
		: Width(width)
		, Height(height)
		, Title(title)
		, Fullscreen(fullscreen)
	{}
	WindowProperties::WindowProperties(const WindowProperties& rhs)
		: Width(rhs.Width)//.GetWidth())
		, Height(rhs.Height)
		, Title(rhs.Title)
	{}
	WindowProperties::WindowProperties(WindowProperties&& lhs)
	{
		// Copy the values (from their memory location, stealing them):
		Width = lhs.Width;
		Height = lhs.Height;
		Title = lhs.Title;

		// Reset the left-hand-side so that it cannot be used anymore:
		lhs.Width = 0;
		lhs.Height = 0;
		lhs.Title = "";
	}
	///////////CONSTRUCTORS///////////
	/**********ASSIGNMENT OPERATORS**********/
	WindowProperties& WindowProperties::operator=(const WindowProperties& rhs)
	{
		Width = rhs.Width;
		Height = rhs.Height;
		Title = rhs.Title;
		Fullscreen = rhs.Fullscreen;

		return *this;
	}
	WindowProperties& WindowProperties::operator=(WindowProperties&& lhs)
	{
		// Copy the values (from their memory location, stealing them):
		Width = lhs.Width;
		Height = lhs.Height;
		Title = lhs.Title;
		Fullscreen = lhs.Fullscreen;

		// Reset the left-hand-side so that it cannot be used anymore:
		lhs.Width = 0;
		lhs.Height = 0;
		lhs.Title = "";
		lhs.Fullscreen = false;

		return *this;
	}
	///////////ASSIGNMENT OPERATORS///////////
	/////////////////////WINDOW PROPERTIES////////////////////
}
// Logging
std::ostream& operator<<(std::ostream& os, const Alpha9::WindowProperties& props)
{
	os << "Window Properties: \"" << props.Title << "\"";
	os << ", Full-screen = " << (props.Fullscreen ? "true" : "false");
	os << ", (" << props.Width << ", " << props.Height << ")";
	return os;
}