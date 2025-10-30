#include "Log.hpp"
#include <string>
#include <string_view>

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

  Logger Log::s_engine_logger { "CORVUS" };
  Logger Log::s_client_logger { "CLIENT" };
}
