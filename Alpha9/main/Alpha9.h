#pragma once

#include "a9pch.hpp"

/***********GLAD*********/
#include "glad/glad.h" // Must be included first before any other graphics library

/**********MISC**********/
#include "time.hpp"

/**********LOGGER**********/
#include "logger/logger.hpp"
#include "logger/logging_macros.hpp"

/**********WINDOW**********/
#include "rendering/window.hpp"
#ifdef A9_PLATFORM_WINDOWS
	#include "windows/windows_window.hpp"
	#include "windows/windows_input.hpp"
#endif // A9_PLATFORM_WINDOWS

/**********RENDERING**********/
#include "rendering/shader.hpp"
#include "rendering/buffers.hpp"
#include "rendering/context.hpp"
#include "rendering/renderer.hpp"
#include "rendering/vertex_array.hpp"
#include "rendering/camera.hpp"
#ifdef A9_PLATFORM_WINDOWS
	#include "openGL/gl_context.hpp"
	#include "openGL/gl_buffers.hpp"
	#include "openGL/gl_vertexArray.hpp"
#endif // A9_PLATFORM_WINDOWS

/**********GAME**********/
#include "game_base.hpp"

/**********MAIN**********/
#include "main.hpp"