#pragma once

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/null_sink.h"
#include "core.hpp"

namespace Alpha9
{
	class A9_API Logger
	{
	public:
		Logger() = delete;
		~Logger() = delete;

		static void Init();
		static void Stop();

		static std::shared_ptr<spdlog::logger> getLogger(const std::string &logger);
	private:
		static bool s_isInitalized;
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
		static std::shared_ptr<spdlog::logger> s_nullLogger;
	};

	namespace _logger_helpers
	{
		/* Printer:
		 * For each expression
		 * **name (type): value**
		 * is added!
		*/
		template<typename T>
		void printer(std::ostream& out, std::vector<std::string>::const_iterator name,
			std::vector<std::string>::const_iterator type, T t)
		{
			out << *name << " (" << *type << "): " << t;
		}
		template<typename T, typename... Args>
		void printer(std::ostream& out, std::vector<std::string>::const_iterator name,
			std::vector<std::string>::const_iterator type, T t, Args... args)
		{
			out << *name << " (" << *type << "): " << t << ", ";
			printer(out, ++name, ++type, args...);
		}


		template<typename T>
		void getTypes(std::vector<std::string> &out, T t)
		{
			out.insert(std::end(out), type_name<decltype(t)>());
		}
		template<typename T, typename... Args>
		void getTypes(std::vector<std::string> &out, T t, Args... args)
		{
			out.insert(std::end(out), type_name<decltype(t)>());
			getTypes(out, args...);
		}

		template<typename T>
		std::vector<std::string> stringify_names(const T& s)
		{
			// TODO: Fix so that spaces are allowed, only split at commas
			std::vector<std::string> result{};

			// Loop through the *s* string and append anything
			// that is not a comma or space
			std::string tempString;
			for (std::string::const_iterator c = s.cbegin(); c < s.cend(); c++)
			{
				tempString = "";
				while (*c != ',')
				{
					if (std::isspace(*c))
						++c;
					tempString.insert(tempString.end(), *c);
					if (c != (s.cend() - 1))
						++c;
					else
						break;
				}
				if (tempString != "")
				{
					result.insert(result.end(), tempString);
				}
			}
			return result;
		}

		template<typename... Args>
		std::string log_expression(const std::string& names_string, Args... values)
		{
			std::vector<std::string> names{};
			std::vector<std::string> types{};

			names = stringify_names(names_string);

			getTypes(types, values...);

			std::ostringstream os{};
			printer(os, std::begin(names), std::begin(types), values...);

			return os.str();
		}

		template<typename... Args>
		std::string log_types(const std::string& names_string, Args... values)
		{
			std::ostringstream os;

			std::vector<std::string> names{};
			std::vector<std::string> types{};

			names = stringify_names(names_string);
			getTypes(types, values...);

			// Loop through all of the names and types and add them to a string-stream
			for (size_t i = 0; i < names.size(); i++)
			{
				os << names[i] << ": " << types[i];
				if (i != (names.size() - 1))
					os << ", "; // Only put a comma if this is not the last argument
			}

			return os.str();
		}
		// TODO: create common style and don't jump around with it
	}
}

// Core logging macros
#define A9_CORE_TRACE(...)		::Alpha9::Logger::getLogger("CORE")->trace(__VA_ARGS__)
#define A9_CORE_DEBUG(...)		::Alpha9::Logger::getLogger("CORE")->debug(__VA_ARGS__)
#define A9_CORE_INFO(...)		::Alpha9::Logger::getLogger("CORE")->info(__VA_ARGS__)
#define A9_CORE_WARN(...)		::Alpha9::Logger::getLogger("CORE")->warn(__VA_ARGS__)
#define A9_CORE_ERROR(...)		::Alpha9::Logger::getLogger("CORE")->error(__VA_ARGS__)
#define A9_CORE_CRITICAL(...)	::Alpha9::Logger::getLogger("CORE")->critical(__VA_ARGS__)

// Client logging macros
#define A9_TRACE(...)			::Alpha9::Logger::getLogger("CLIENT")->trace(__VA_ARGS__)
#define A9_DEBUG(...)			::Alpha9::Logger::getLogger("CLIENT")->debug(__VA_ARGS__)
#define A9_INFO(...)			::Alpha9::Logger::getLogger("CLIENT")->info(__VA_ARGS__)
#define A9_WARN(...)			::Alpha9::Logger::getLogger("CLIENT")->warn(__VA_ARGS__)
#define A9_ERROR(...)			::Alpha9::Logger::getLogger("CLIENT")->error(__VA_ARGS__)
#define A9_CRITICAL(...)		::Alpha9::Logger::getLogger("CLIENT")->critical(__VA_ARGS__)

// Logs the types of each variable/expressioin passed in.
#define A9_LOG_TYPES(...) A9_DEBUG(::Alpha9::_logger_helpers::log_types(STRING(__VA_ARGS__), __VA_ARGS__))
// Used to log expressions
// ex: A9_LOG_EXPRESSION(my_func("hello"));
// output: "(int) my_func("hello"): 0"
#define A9_LOG_EXPRESSION(...) A9_DEBUG(::Alpha9::_logger_helpers::log_expression(STRING(__VA_ARGS__), __VA_ARGS__))