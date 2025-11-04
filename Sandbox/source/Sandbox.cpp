#include <Corvus/Engine.hpp>

class SampleLayer : public Corvus::Layer
{
public:
  SampleLayer() = default;
  ~SampleLayer() override = default;

  void OnAttach() override
  {}

  void OnDetach() override
  {}

  void OnUpdate() override
  {
    CORVUS_LOG_TRACE("Sample layer updated!");
  }

  void OnEvent(Corvus::Event& event) override
  {
    CORVUS_LOG_TRACE("An event occured in the sample layer!");
  }
};

class Sandbox : public Corvus::Application
{
public:
  Sandbox() = default;
  ~Sandbox() override = default;

protected:
  void OnSetup() override
  {
    PushLayer(new SampleLayer());

    Corvus::Application::OnSetup();
  }

  void OnCleanup() override
  {
    Corvus::Application::OnCleanup();
  }

  void OnUpdate() override
  {
    Corvus::Application::OnUpdate();
  }

  void OnEvent(Corvus::Event& event) override
  {
    Corvus::Application::OnEvent(event);
  }
};

CORVUS_REGISTER_APPLICATION_ENTRY(Sandbox);
