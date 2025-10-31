#pragma once

#include "Core/Core.hpp"
#include <chrono>
#include <format>
#include <print>
#include <string>
#include <string_view>

#define CORVUS_LOG_COLOR_UNKNOWN "\x1B[90m"
#define CORVUS_LOG_COLOR_TRACE   "\x1B[36m"
#define CORVUS_LOG_COLOR_INFO    "\x1B[32m"
#define CORVUS_LOG_COLOR_WARN    "\x1B[33m"
#define CORVUS_LOG_COLOR_ERR     "\x1B[31m"
#define CORVUS_LOG_COLOR_FATAL   "\x1B[95m"
#define CORVUS_LOG_COLOR_DEFAULT "\x1B[0m"

namespace Corvus
{
  enum class LogLevel
  {
    None = 0,
    Trace,
    Info,
    Warn,
    Err,
    Fatal
  };

  class CORVUS_API Logger
  {
  public:
    Logger(const std::string& name);
    ~Logger() = default;

    // default print
    template<typename... Args>
    void Print(std::format_string<Args...> fmt,
               Args&&... args)
    {
      std::chrono::time_point now_tp { std::chrono::floor<std::chrono::seconds>(
                                       std::chrono::system_clock::now()) };

      std::string time_str { std::format("{:%d-%m-%Y %H:%M:%S}",
                             std::chrono::current_zone()->to_local(now_tp)) };
      std::string format_str { std::format(fmt, std::forward<Args>(args)...) };

      std::println("[{}]-[{}]-[{}]: {}", m_name, time_str,
                   GetLevelString(LogLevel::None), format_str);
    }

    // leveled print
    template<typename... Args>
    void Print(LogLevel level, std::format_string<Args...> fmt,
               Args&&... args)
    {
      std::chrono::time_point now_tp { std::chrono::floor<std::chrono::seconds>(
                                       std::chrono::system_clock::now()) };

      std::string time_str { std::format("{:%d-%m-%Y %H:%M:%S}",
                             std::chrono::current_zone()->to_local(now_tp)) };
      std::string format_str { std::format(fmt, std::forward<Args>(args)...) };

      std::println("[{}]-[{}]-[{}]: {}", m_name, time_str,
                   GetLevelString(level), format_str);
    }

  private:
    std::string m_name;

    std::string_view GetLevelString(LogLevel level) const;
  };

  class CORVUS_API Log
  {
  public:
    inline static Logger& GetEngineLogger()
    {
      return s_engine_logger;
    }

    inline static Logger& GetClientLogger()
    {
      return s_client_logger;
    }

  private:
    Log() = delete;
    ~Log() = delete;

    static Logger s_engine_logger;
    static Logger s_client_logger;
  };
}

#if defined(CORVUS_DEBUG)
  #if defined(CORVUS_BUILD_ENGINE)
    #define CORVUS_LOG(...) \
    Corvus::Log::GetEngineLogger().Print(__VA_ARGS__)
    #define CORVUS_LOG_TRACE(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Trace, __VA_ARGS__)
    #define CORVUS_LOG_INFO(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Info, __VA_ARGS__)
    #define CORVUS_LOG_WARN(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Warn, __VA_ARGS__)
    #define CORVUS_LOG_ERR(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Err, __VA_ARGS__)
    #define CORVUS_LOG_FATAL(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Fatal, __VA_ARGS__)
  #else
    #define CORVUS_LOG(...) \
    Corvus::Log::GetClientLogger().Print(__VA_ARGS__)
    #define CORVUS_LOG_TRACE(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Trace, __VA_ARGS__)
    #define CORVUS_LOG_INFO(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Info, __VA_ARGS__)
    #define CORVUS_LOG_WARN(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Warn, __VA_ARGS__)
    #define CORVUS_LOG_ERR(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Err, __VA_ARGS__)
    #define CORVUS_LOG_FATAL(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Fatal, __VA_ARGS__)
  #endif
#else
    #define CORVUS_LOG()
    #define CORVUS_LOG_TRACE(...)
    #define CORVUS_LOG_INFO(...)
    #define CORVUS_LOG_WARN(...)
    #define CORVUS_LOG_ERR(...)
    #define CORVUS_LOG_FATAL(...)
#endif
