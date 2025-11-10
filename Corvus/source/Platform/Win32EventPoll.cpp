#if defined(CORVUS_PLATFORM_WIN32)

#include "Win32EventPoll.hpp"
#include <windows.h>

namespace Corvus
{
  void Win32EventPoll::UpMessages()
  {
    MSG message{ };

    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) != 0)
    {
      if (message.message == WM_QUIT)
      {
        break;
      }

      TranslateMessage(&message);
      DispatchMessage(&message);
    }
  }
}

#endif
