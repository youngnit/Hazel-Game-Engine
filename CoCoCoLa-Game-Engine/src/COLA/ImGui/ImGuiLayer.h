#pragma once
#include "COLA/Core/Layer.h"

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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };
}
