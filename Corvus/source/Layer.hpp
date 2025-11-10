#pragma once

#include "Core/Core.hpp"
#include "Event.hpp"
#include <string>

namespace Corvus
{
  class CORVUS_API Layer
  {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;

    inline const std::string& GetName() const
    {
      return m_name;
    }

    virtual void Attach() = 0;
    virtual void Detach() = 0;
    virtual void Update() = 0;
    virtual void RespondEvent(Event& event) = 0;

  protected:
    std::string m_name;
  };
}
