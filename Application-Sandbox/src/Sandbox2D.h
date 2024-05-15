#pragma once

#include "Cola.h"

class Sandbox2D : public COLA::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(COLA::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(COLA::Event& e) override;
private:
    COLA::OrthographicCameraController m_CameraController;

    // Temp
    COLA::Ref<COLA::VertexArray> m_SquareVA;
    COLA::Ref<COLA::Shader> m_FlatColorShader;

    COLA::Ref<COLA::Texture2D> m_CheckerboardTexture;
    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};