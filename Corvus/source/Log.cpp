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
      return CORVUS_LOG_COLOR_TRACE "TRACE" CORVUS_LOG_COLOR_DEFAULT;

      case LogLevel::Info:
      return CORVUS_LOG_COLOR_INFO "INFO" CORVUS_LOG_COLOR_DEFAULT;

      case LogLevel::Warn:
      return CORVUS_LOG_COLOR_WARN "WARN" CORVUS_LOG_COLOR_DEFAULT;

      case LogLevel::Err:
      return CORVUS_LOG_COLOR_ERR "ERR" CORVUS_LOG_COLOR_DEFAULT;

      case LogLevel::Fatal:
      return CORVUS_LOG_COLOR_FATAL "FATAL" CORVUS_LOG_COLOR_DEFAULT;

      default:
      return CORVUS_LOG_COLOR_UNKNOWN "UNKNOWN" CORVUS_LOG_COLOR_DEFAULT;
    }
  }

  Logger Log::s_engine_logger { "CORVUS" };
  Logger Log::s_client_logger { "CLIENT" };
}
