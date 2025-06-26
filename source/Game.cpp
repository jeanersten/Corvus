#include "Game.h"

cvs::Game::Game()
  : m_window(640, 480, "Corvus Engine!")
{
  init();
}

cvs::Game::~Game()
{}

void cvs::Game::init()
{
  m_window.create();
}

void cvs::Game::update()
{
  while (!m_window.closed())
  {
    m_window.clear();
    m_window.display();
  }
}

void cvs::Game::run()
{
  update();
}
