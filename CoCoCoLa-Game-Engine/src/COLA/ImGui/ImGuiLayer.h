#pragma once
#include "COLA/Layer.h"

#include "COLA/Events/Events.h"
#include "COLA/Events/KeyEvents.h"
#include "COLA/Events/MouseEvents.h"
#include "COLA/Events/ApplicationEvents.h"

namespace COLA {
    class COLA_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        float m_Time = 0.0f;
    };
}