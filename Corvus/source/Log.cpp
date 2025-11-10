#include "Core/PCH.hpp"
#include "Log.hpp"

namespace Corvus
{
  Logger::Logger(const std::string& name)
    : m_name(name)
  {}

  std::string_view Logger::GetLevelString(LogLevel level) const
  {
    switch (level)
    {
      case LogLevel::Trace:
      return "TRACE";

      case LogLevel::Info:
      return "INFO";

      case LogLevel::Warn:
      return "WARN";

      case LogLevel::Err:
      return "ERR";

      case LogLevel::Fatal:
      return "FATAL";

      default:
      return "UNKNOWN";
    }
  }

  std::string_view Logger::GetLevelColorString(LogLevel level) const
  {
    switch (level)
    {
    case LogLevel::Trace:
      return COLOR_CYAN;

    case LogLevel::Info:
      return COLOR_GREEN;

    case LogLevel::Warn:
      return COLOR_YELLOW;

    case LogLevel::Err:
      return COLOR_RED;

    case LogLevel::Fatal:
      return COLOR_MAGENTA;

    default:
      return COLOR_GRAY;
    }
  }

  std::string_view Logger::GetCurrentTimeString() const
  {
    static std::string time_str{ };

    std::chrono::time_point now_tp{ std::chrono::floor<std::chrono::seconds>(
                                    std::chrono::system_clock::now()) };

    time_str = std::format("{:%d-%m-%Y %H:%M:%S}",
                           std::chrono::current_zone()->to_local(now_tp));

    return time_str;
  }

  Logger Log::s_engine_logger { "CORVUS" };
  Logger Log::s_client_logger { "CLIENT" };
}
