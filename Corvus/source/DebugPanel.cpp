#include "Core/PCH.hpp"
#include "DebugPanel.hpp"
#include <imgui/imgui.h>

namespace Corvus
{
  static bool show_demo_wnd{ true };
  static bool show_another_wnd{ false };
  static ImVec4 clear_color{ 0.45f, 0.55f, 0.60f, 1.00f };

  void DebugPanel::Start(Window* window)
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io{ ImGui::GetIO() }; (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsClassic();

    ImGuiStyle& style{ ImGui::GetStyle() };

    style.ScaleAllSizes(1.0f);
    style.FontScaleDpi = 1.0f;

    #if defined(CORVUS_PLATFORM_WIN32) && defined(CORVUS_RENDERER_OPENGL)
      ImGui_ImplWin32_InitForOpenGL(window->GetNativeWindow());
      ImGui_ImplOpenGL3_Init();
    #endif
  }

  void DebugPanel::Update()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (show_demo_wnd) ImGui::ShowDemoWindow(&show_demo_wnd);
  }

  void DebugPanel::Render()
  {
    ImGui::Render();
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}
