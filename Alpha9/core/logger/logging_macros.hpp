#pragma once

#define A9_CORE_TRACE(...)    ::Alpha9::Logger::CoreLogger()->trace(__VA_ARGS__)
#define A9_CORE_INFO(...)     ::Alpha9::Logger::CoreLogger()->info(__VA_ARGS__)
#define A9_CORE_WARN(...)     ::Alpha9::Logger::CoreLogger()->warn(__VA_ARGS__)
#define A9_CORE_ERROR(...)    ::Alpha9::Logger::CoreLogger()->error(__VA_ARGS__)
#define A9_CORE_CRITICAL(...) ::Alpha9::Logger::CoreLogger()->critical(__VA_ARGS__)

#define A9_TRACE(...)         ::Alpha9::Logger::ClientLogger()->trace(__VA_ARGS__)
#define A9_INFO(...)          ::Alpha9::Logger::ClientLogger()->info(__VA_ARGS__)
#define A9_WARN(...)          ::Alpha9::Logger::ClientLogger()->warn(__VA_ARGS__)
#define A9_ERROR(...)         ::Alpha9::Logger::ClientLogger()->error(__VA_ARGS__)
#define A9_CRITICAL(...)      ::Alpha9::Logger::ClientLogger()->critical(__VA_ARGS__)