#include <Corvus/Engine.hpp>
#include <Corvus/Entry.hpp>

class MainLayer final : public Corvus::Layer
{
public:
  MainLayer()
    : Layer("MainLayer")
  {}

  ~MainLayer() override = default;

  void Attach() override
  {
    CORVUS_LOG_INFO("Attached layer: {}", GetName());
  }

  void Detach() override
  {
    CORVUS_LOG_INFO("Detached layer: {}", GetName());
  }

  void Update() override
  {
    CORVUS_LOG_INFO("Updated layer: {}", GetName());
  }

  void RespondEvent(Corvus::Event&) override
  {
    CORVUS_LOG_INFO("Event occurred in layer: {}", GetName());
  }
};

class Sandbox final: public Corvus::Application
{
public:
  Sandbox()
    : m_main_layer(nullptr)
  {}

  ~Sandbox() override = default;

private:
  Corvus::Layer* m_main_layer;

  void Setup() override
  {
    Corvus::Application::Setup();

    m_main_layer = PushLayer<MainLayer>();
  }

  void Cleanup() override
  {
    Corvus::Application::Cleanup();
  }
};

CORVUS_REGISTER_APPLICATION_ENTRY(Sandbox);
