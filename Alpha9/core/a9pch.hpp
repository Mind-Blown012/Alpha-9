#pragma once

// STL Containers
#include <vector>
#include <queue>
#include <tuple>
#include <array>
#include <string>
#include <iterator>
#include <map>
#include <iterator>
#include <unordered_map>


// STL Math and Time
#include <algorithm>
#include <cmath>
#include <complex>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <chrono>

// STL Streams
#include <iostream>
#include <fstream>
#include <sstream>

// STL Miscellaneous
#include <memory>
#include <functional>
#include <initializer_list>

// GLM Mathmatics library
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

// spdlog should be pre-compiled since it is 
// relatively large and header only.
#include "logger/logger.hpp"

#ifdef A9_PLATFORM_WINDOWS
	#include <Windows.h>
#endif