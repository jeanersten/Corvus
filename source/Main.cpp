#include "Game.h"
#include "Init.h"
#include "Log.h"

int main()
{
  cvs::Init::setup();

  cvs::Game game;
  game.run();

  cvs::Init::cleanup();

  return 0;
}
