#pragma once

#include <spdlog/spdlog.h>

#include <memory>

#define LOG_LEVEL_TRACE spdlog::level::trace
#define LOG_LEVEL_DEBUG spdlog::level::debug
#define LOG_LEVEL_INFO spdlog::level::info
#define LOG_LEVEL_WARN spdlog::level::warn
#define LOG_LEVEL_ERROR spdlog::level::err
#define LOG_LEVEL_CRITICAL spdlog::level::critical

namespace cvs
{
  class Log
  {
  private:
    static std::shared_ptr<spdlog::logger> m_logger;

  public:
    Log();
    ~Log();

    static void setup();
    static void setLogLevel(spdlog::level::level_enum log_level);
    static std::shared_ptr<spdlog::logger> getLogger();
  };
}

#define LOG_TRACE(message, ...) cvs::Log::getLogger()->trace(message, __VA_ARGS__)
#define LOG_DEBUG(message, ...) cvs::Log::getLogger()->debug(message, __VA_ARGS__)
#define LOG_INFO(message, ...) cvs::Log::getLogger()->info(message, __VA_ARGS__)
#define LOG_WARN(message, ...) cvs::Log::getLogger()->warn(message, __VA_ARGS__)
#define LOG_ERROR(message, ...) cvs::Log::getLogger()->error(message, __VA_ARGS__)
#define LOG_CRITICAL(message, ...) cvs::Log::getLogger()->critical(message, __VA_ARGS__)
