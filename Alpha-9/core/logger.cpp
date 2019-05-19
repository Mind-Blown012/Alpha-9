#include "a9pch.hpp"
#include "logger.hpp"

namespace Alpha9
{
	bool Logger::s_isInitalized = false;
	std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_clientLogger;
	std::shared_ptr<spdlog::logger> Logger::s_nullLogger;

	void Logger::Init()
	{
		if (s_isInitalized)
			return;

		spdlog::set_pattern("%^[%T.%e] [thread %t] %n:%$ %v");

		s_coreLogger = spdlog::stdout_color_mt("CORE");
	#ifdef A9_DEBUG_MODE
		s_coreLogger->set_level(spdlog::level::level_enum::debug);
	#endif
		s_clientLogger = spdlog::stdout_color_mt("CLIENT");
	#ifdef A9_DEBUG_MODE
		// TODO: implement client-level debug setting.
		s_clientLogger->set_level(spdlog::level::level_enum::debug);
	#endif
		s_nullLogger = spdlog::create<spdlog::sinks::null_sink_st>("null");

		s_isInitalized = true;
	}
	void Logger::Stop()
	{
		s_coreLogger->flush();
		s_clientLogger->flush();
		s_isInitalized = false;
	}
	

	std::shared_ptr<spdlog::logger> Logger::getLogger(const std::string &logger)
	{
		if (s_isInitalized)
		{
			if (logger == "CORE")
			{
				return s_coreLogger;
			}
			else if (logger == "CLIENT")
			{
				return s_clientLogger;
			}
			else
			{
				s_coreLogger->warn("{} is not a logger! Available loggers are {}.", \
					logger, "CORE and CLIENT");
				return s_nullLogger;
			}
		}
		return s_nullLogger;
	}
}