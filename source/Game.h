#pragma once

#include "Window.h"

namespace cvs
{
  class Game
  {
  private:
    Window m_window;

    void init();
    void update();
  
  public:
    Game();
    ~Game();

    void run();
  };
}
