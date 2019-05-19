#pragma once

#include <string>

#if defined(A9_PLATFORM_WINDOWS)
	#ifdef A9_BUILD_DLL
		#define A9_API __declspec(dllexport)
	#else
		#define A9_API __declspec(dllimport)
	#endif // A9_BUILD_DLL
#elif defined(A9_PLATFORM_LINUX)
	#define A9_API
#else
	#error "Windows and Linux are the only supported OS\'s for Alpha-9!"
#endif // A9_PLATFORM_WINDOWS



// Function is used for getting the complete type of a variable
// Credits to Howard Hinnant on Stack Overflow
template<typename T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own
	(
#ifndef _MSC_VER
		abi::__cxa_demangle(typeid(TR).name(), nullptr,
			nullptr, nullptr),
#else
		nullptr,
#endif
		std::free
	);

	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)
		r += " const";
	if (std::is_volatile<TR>::value)
		r += " volatile";
	if (std::is_lvalue_reference<T>::value)
		r += "&";
	else if (std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}

#define BIT(x) (1 << x)
#define STRING(...) #__VA_ARGS__
#define A9_RAW_TYPE(variable) decltype(variable)
#define A9_TYPE(variable) type_name<decltype(variable)>()


#ifdef A9_DEBUG_MODE
	#define A9_ASSERT(condition, ...) if(!(condition)) { A9_ERROR("Assertion failed: {}", __VA_ARGS__); __debugbreak(); }
	#define A9_CORE_ASSERT(condition, ...) if(!(condition)) { A9_CORE_ERROR("Assertion failed: {}", __VA_ARGS__); __debugbreak(); }
#else
	#define A9_ASSERT(condition, ...) (condition)
	#define A9_CORE_ASSERT(condition, ...) (condition)
#endif // A9_DEBUG_MODE