#pragma once

// Platforms
#if defined(A9_PLATFORM_WINDOWS)
	#ifdef A9_DYNAMIC_LINK
		#ifdef A9_BUILD_DLL
			#define A9_API __declspec(dllexport)
		#else
			#define A9_API __declspec(dllimport)
		#endif // A9_BUILD_DLL
	#else
		#define A9_API
	#endif // A9_DYNAMIC_LINK
#elif defined(A9_PLATFORM_LINUX)
	#define A9_API
#else
	#error "Windows and Linux are the only supported OS\'s for Alpha-9!"
#endif // A9_PLATFORM_WINDOWS

// Debug helpers
#define BIT(x) (1 << x)
#define STRING(...) #__VA_ARGS__
#define A9_RAW_TYPE(variable) decltype(variable)
#define A9_TYPE(variable) ::Alpha9::type_name<decltype(variable)>()

// Assertions
#ifdef A9_DEBUG
	#define A9_CORE_ASSERT(x, what) if(!(x)) { A9_CORE_ERROR("Assertion failed (!{}): {}", #x, what); __debugbreak(); }
	#define A9_ASSERT(x, what) if(!(x)) { A9_ERROR("Assertion failed (!{}): {}", #x, what); __debugbreak(); }
#else
	#define A9_ASSERT(condition, ...)
	#define A9_CORE_ASSERT(condition, ...)
#endif // A9_DEBUG_MODE

// Events
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return ::Alpha9::EventType::##type; }\
							virtual EventType GetEventType() const override { return GetStaticType(); }\
							virtual const char* GetName() const override { return #type; }\
							virtual Event *copy() const override { return new type(*this); }

#define TRIGGER_EVENT(e) ::Alpha9::EventManager::Instance().Trigger(&e)
#define BIND_EVENT(type, func) ::Alpha9::EventManager::Instance().Bind(::Alpha9::EventType::##type, func)
// For member functions
#define BIND_CLASS_EVENT(type, func, instance) ::Alpha9::EventManager::Instance().Bind(::Alpha9::EventType::##type, std::bind(&func, instance, std::placeholders::_1))
