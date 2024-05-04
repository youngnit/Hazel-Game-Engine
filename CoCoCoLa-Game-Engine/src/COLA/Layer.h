﻿#pragma once

#include "Core.h"
#include "Events/Events.h"

namespace COLA {
    class COLA_API Layer
    {
    public:
        Layer(const std::string& debugname = "Layer");
        virtual ~Layer();

        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate();
        virtual void OnEvent(Event& event){}
        

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}