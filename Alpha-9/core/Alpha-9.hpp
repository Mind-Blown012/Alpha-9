#pragma once

#include "application.hpp"
#include "logger.hpp"
#include "graphics/window_base.hpp"




// Entry Point: for each specific OS
#if defined(A9_PLATFORM_WINDOWS)
	#include "windows/windows_entrypoint.hpp"
#elif defined(A9_PLATFORM_LINUX)
	#include "linux/entrypoint.hpp"
#endif // A9_PLATFORM_WINDOWS, A9_PLATFORM_LINUX
