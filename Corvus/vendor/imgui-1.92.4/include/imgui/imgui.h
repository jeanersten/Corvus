#pragma once

#include "../../source/imconfig.h"
#include "../../source/imgui.h"

#ifdef CORVUS_PLATFORM_WIN32
#include "../../source//imgui_impl_win32.h"
#endif

#ifdef CORVUS_RENDERER_OPENGL
#include "../../source/imgui_impl_opengl3.h"
#endif

#ifdef CORVUS_RENDERER_DIRECT3D11
#include "../../source/imgui_impl_dx11.h"
#endif
