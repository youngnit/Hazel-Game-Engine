#pragma once

#include "Core.h"
#include "COLA/Core/Timestep.h"
#include "COLA/Events/Events.h"

namespace COLA {
    class COLA_API Layer
    {
    public:
        Layer(const std::string& debugname = "Layer");
        virtual ~Layer();

        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate(Timestep ts);
        virtual void OnEvent(Event& event){}
        virtual void OnImGuiRender() {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}