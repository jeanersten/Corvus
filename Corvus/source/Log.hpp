#pragma once

#include "Core/Core.hpp"
#include <format>
#include <print>
#include <string>
#include <string_view>

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

    template<typename... Args>
    void Print(std::format_string<Args...> fmt, Args&&... args) const
    {
      std::string format_str { std::format(fmt, std::forward<Args>(args)...) };

      std::println("[{}]-[{}]-[{}{}{}]: {}", m_name,
                   COLOR_GRAY, GetCurrentTimeString(), COLOR_RESET,
                   GetLevelColorString(LogLevel::None),
                   GetLevelString(LogLevel::None),
                   COLOR_RESET,
                   format_str);
    }

    template<typename... Args>
    void Print(LogLevel level, std::format_string<Args...> fmt,
               Args&&... args) const
    {

      std::string format_str { std::format(fmt, std::forward<Args>(args)...) };

      std::println("[{}]-[{}{}{}]-[{}{}{}]: {}", m_name,
                   COLOR_GRAY, GetCurrentTimeString(), COLOR_RESET,
                   GetLevelColorString(level),
                   GetLevelString(level),
                   COLOR_RESET,
                   format_str);
    }

  private:
    static constexpr const char* COLOR_RESET  { "\x1B[0m" };
    static constexpr const char* COLOR_RED    { "\x1B[31m" };
    static constexpr const char* COLOR_GREEN  { "\x1B[32m" };
    static constexpr const char* COLOR_YELLOW { "\x1B[33m" };
    static constexpr const char* COLOR_MAGENTA{ "\x1B[35m" };
    static constexpr const char* COLOR_CYAN   { "\x1B[36m" };
    static constexpr const char* COLOR_GRAY   { "\x1B[90m" };

    std::string m_name;

    std::string_view GetLevelString(LogLevel level) const;
    std::string_view GetLevelColorString(LogLevel level) const;
    std::string_view GetCurrentTimeString() const;
  };

  class CORVUS_API Log
  {
  public:
    static inline const Logger& GetEngineLogger()
    {
      return s_engine_logger;
    }

    static inline const Logger& GetClientLogger()
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
