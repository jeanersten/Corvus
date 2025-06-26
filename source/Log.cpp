#include "Log.h"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

std::shared_ptr<spdlog::logger> cvs::Log::m_logger;

cvs::Log::Log()
{}

cvs::Log::~Log()
{}

void cvs::Log::setup()
{
  spdlog::set_pattern("[%T]-[%n]-[%^ %L %$]: %v");
  m_logger = spdlog::stderr_color_mt("Corvus");
}

void cvs::Log::setLogLevel(spdlog::level::level_enum log_level)
{
  m_logger->set_level(log_level);
}

std::shared_ptr<spdlog::logger> cvs::Log::getLogger()
{
  return m_logger;
}
