#pragma once

#include <vector>
#include <memory>

#include "macros.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Alpha9
{
	class A9_API Logger
	{
	public:
		static void Init();
		static void InitalizeLogger(const char* name);

		inline static std::shared_ptr<spdlog::logger>& CoreLogger() { return s_coreLogger; };
		inline static std::shared_ptr<spdlog::logger>& ClientLogger() { return s_clientLogger; };
		static std::shared_ptr<spdlog::logger> GetLogger(const char* name);
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
		static std::vector<std::shared_ptr<spdlog::logger>> s_loggers;

		static bool s_isLoggerInitalized;
	};

	template<typename T> 
	std::string type_name();
}

#include "logging_macros.hpp"