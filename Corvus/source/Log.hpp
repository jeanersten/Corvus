#pragma once

#include "Core/Core.hpp"
#include <cstdlib>
#include <format>
#include <print>
#include <string>
#include <string_view>

namespace Corvus
{
  enum class LogLevel
  {
    Trace,
    Info,
    Warn,
    Error,
    Fatal
  };

  class CORVUS_API Logger
  {
  public:
    Logger(std::string_view name);
    ~Logger() = default;

    template<typename... Args>
    inline void Print(LogLevel level, std::format_string<Args...> fmt,
                      Args&&... args) const
    {
      if (level >= m_level)
      {
        std::string str_fmted{ std::format(fmt, std::forward<Args>(args)...) };

        std::println("[{}]-[{}{}{}]-[{}{}{}]: {}", m_name,
                     TEXT_COLOR_GRAY, GetCurrentTimeString(), TEXT_COLOR_RESET,
                     GetLevelColorString(level),
                     GetLevelString(level),
                     TEXT_COLOR_RESET,
                     str_fmted);

        if (level == LogLevel::Fatal)
        {
          std::exit(EXIT_FAILURE);
        }
      }
    }

    inline void SetLogLevel(LogLevel level)
    {
      m_level = level;
    }

  private:
    static constexpr std::string_view TEXT_TRACE{ "TRACE" };
    static constexpr std::string_view TEXT_INFO { "INFO" };
    static constexpr std::string_view TEXT_WARN { "WARN" };
    static constexpr std::string_view TEXT_ERROR{ "ERROR" };
    static constexpr std::string_view TEXT_FATAL{ "FATAL" };

    static constexpr std::string_view TEXT_COLOR_RESET  { "\x1B[0m" };
    static constexpr std::string_view TEXT_COLOR_GRAY   { "\x1B[90m" };
    static constexpr std::string_view TEXT_COLOR_RED    { "\x1B[91m" };
    static constexpr std::string_view TEXT_COLOR_GREEN  { "\x1B[92m" };
    static constexpr std::string_view TEXT_COLOR_YELLOW { "\x1B[93m" };
    static constexpr std::string_view TEXT_COLOR_BLUE   { "\x1B[94m" };
    static constexpr std::string_view TEXT_COLOR_MAGENTA{ "\x1B[95m" };

    std::string m_name;
    LogLevel m_level;

    std::string_view GetLevelString(LogLevel level) const;
    std::string_view GetLevelColorString(LogLevel level) const;
    std::string_view GetCurrentTimeString() const;
  };

  class CORVUS_API Log
  {
  public:
    static inline Logger& GetEngineLogger()
    {
      return s_engine_logger;
    }

    static inline Logger& GetClientLogger()
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
  #define CORVUS_SET_ENGINE_LOG_LEVEL(LVL) \
  Corvus::Log::GetEngineLogger().SetLogLevel(LVL)
  #define CORVUS_SET_CLIENT_LOG_LEVEL(LVL) \
  Corvus::Log::GetClientLogger().SetLogLevel(LVL)

  #if defined(CORVUS_BUILD_ENGINE)
    #define CORVUS_LOG_TRACE(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Trace, __VA_ARGS__)
    #define CORVUS_LOG_INFO(...)  \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Info, __VA_ARGS__)
    #define CORVUS_LOG_WARN(...)  \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Warn, __VA_ARGS__)
    #define CORVUS_LOG_ERROR(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Error, __VA_ARGS__)
    #define CORVUS_LOG_FATAL(...) \
    Corvus::Log::GetEngineLogger().Print(Corvus::LogLevel::Fatal, __VA_ARGS__)
  #else
    #define CORVUS_LOG_TRACE(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Trace, __VA_ARGS__)
    #define CORVUS_LOG_INFO(...)  \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Info, __VA_ARGS__)
    #define CORVUS_LOG_WARN(...)  \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Warn, __VA_ARGS__)
    #define CORVUS_LOG_ERROR(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Error, __VA_ARGS__)
    #define CORVUS_LOG_FATAL(...) \
    Corvus::Log::GetClientLogger().Print(Corvus::LogLevel::Fatal, __VA_ARGS__)
  #endif
#else
  #define CORVUS_SET_ENGINE_LOG_LEVEL(LVL)
  #define CORVUS_SET_CLIENT_LOG_LEVEL(LVL)
  #define CORVUS_LOG_TRACE(...)
  #define CORVUS_LOG_INFO(...)
  #define CORVUS_LOG_WARN(...)
  #define CORVUS_LOG_ERROR(...)
  #define CORVUS_LOG_FATAL(...)
#endif
