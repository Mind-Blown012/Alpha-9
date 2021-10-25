#include "a9pch.hpp"

#include "logger.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Alpha9
{
	std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_clientLogger;
	std::vector<std::shared_ptr<spdlog::logger>> Logger::s_loggers;

	bool Logger::s_isLoggerInitalized = false;


	void Logger::Init()
	{
		if (s_isLoggerInitalized)
			return;

		// TODO: Error handling

		spdlog::set_pattern("%^[%T.%e] (%t) %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("CORE");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("CLIENT");
		s_clientLogger->set_level(spdlog::level::trace);
	}

	void Logger::InitalizeLogger(const char* name)
	{
		// TODO: Look into async logging for better engine performance and no crashing!
		if (!s_isLoggerInitalized)
			spdlog::set_pattern("%^[%T.%e] (%t) %n: %v%$");

		auto log = spdlog::stdout_color_mt(name);
		log->set_level(spdlog::level::trace);

		s_loggers.insert(std::cend(s_loggers) - 1, log);
	}

	std::shared_ptr<spdlog::logger> Logger::GetLogger(const char* name)
	{
		return spdlog::get(name);
	}

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
}