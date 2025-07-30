#include <Corvus/Engine.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
  Corvus::Window* window = Corvus::Window::Create("Corvus!", 640, 480);
  std::cout << "Title: " << window->GetTitle() << " Width: " << window->GetWidth() << " Height:" << window->GetHeight();

  return 0;
}
