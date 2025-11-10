#pragma once

#if defined(CORVUS_PLATFORM_WIN32)

namespace Corvus
{
  class Win32EventPoll
  {
  public:
    static void UpMessages();

  private:
    Win32EventPoll() = delete;
    ~Win32EventPoll() = delete;
  };
}

#endif
