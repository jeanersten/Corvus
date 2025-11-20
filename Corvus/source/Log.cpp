#include "Core/PCH.hpp"
#include "Log.hpp"

namespace Corvus
{
  Logger::Logger(std::string_view name)
    : m_name(name)
    , m_level(LogLevel::Trace)
  {}

  std::string_view Logger::GetLevelString(LogLevel level) const
  {
    switch (level)
    {
      case LogLevel::Trace:
        return TEXT_TRACE;

      case LogLevel::Info:
        return TEXT_INFO;

      case LogLevel::Warn:
        return TEXT_WARN;

      case LogLevel::Error:
        return TEXT_ERROR;

      case LogLevel::Fatal:
        return TEXT_FATAL;

      default:
        return "";
    }
  }

  std::string_view Logger::GetLevelColorString(LogLevel level) const
  {
    switch (level)
    {
      case LogLevel::Trace:
        return TEXT_COLOR_BLUE;

      case LogLevel::Info:
        return TEXT_COLOR_GREEN;

      case LogLevel::Warn:
        return TEXT_COLOR_YELLOW;

      case LogLevel::Error:
        return TEXT_COLOR_RED;

      case LogLevel::Fatal:
        return TEXT_COLOR_MAGENTA;

      default:
        return "";
      }
  }

  std::string_view Logger::GetCurrentTimeString() const
  {
    static std::string time_str{ };
    std::chrono::time_point current_tp{ std::chrono::floor<std::chrono::seconds>
                                        (std::chrono::system_clock::now()) };

    time_str = std::format("{:%d-%m-%Y %H:%M:%S}",
                           std::chrono::current_zone()->to_local(current_tp));

    return time_str;
  }

  Logger Log::s_engine_logger{ "CORVUS" };
  Logger Log::s_client_logger{ "CLIENT" };
}
