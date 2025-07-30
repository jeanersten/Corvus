#pragma once

#ifdef CORVUS_PLATFORM_WIN32

  #ifdef CORVUS_BUILD_DLL

    #define CORVUS_API __declspec(dllexport)

  #else

    #define CORVUS_API __declspec(dllimport)

  #endif

#else

  #define CORVUS_API
  #error [CORVUS][Current platform is not supported!]

#endif
