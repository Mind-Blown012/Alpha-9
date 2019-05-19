#pragma once

#include <functional>
#include <algorithm>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "logger.hpp"

// TODO: other platform support
#ifdef A9_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // A9_PLATFORM_WINDOWS