﻿#include "clpch.h"

#include <Cola.h>
#include <COLA/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public COLA::Layer
{
public:
    ExampleLayer()
        :Layer("Example"), m_CameraController(1280.0f / 720.0f)
    {
        //m_VertexArray.reset(COLA::VertexArray::Create());
        m_VertexArray = COLA::VertexArray::Create();
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        COLA::Ref<COLA::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(COLA::VertexBuffer::Create(vertices, sizeof(vertices)));
        COLA::BufferLayout layout = {
            { COLA::ShaderDataType::Float3, "a_Position" },
            { COLA::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[] = { 0, 1, 2 };
        COLA::Ref<COLA::IndexBuffer> indexBuffer;
        indexBuffer.reset(COLA::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        //m_SquareVA.reset(COLA::VertexArray::Create());
        m_SquareVA = COLA::VertexArray::Create();
        float squareVertices[] = {
            -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.0f,  0.0f,  1.0f
        };
        COLA::Ref<COLA::VertexBuffer> squareVB;
        squareVB.reset(COLA::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout(
            {
                { COLA::ShaderDataType::Float3, "a_Position" },
                { COLA::ShaderDataType::Float2, "a_TexCoord" }
            }
        );
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
        COLA::Ref<COLA::IndexBuffer> squareIB;
        squareIB.reset(COLA::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
        m_Shader = COLA::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
        std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
        std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

        m_FlatColorShader = COLA::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

        auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

        m_Texture = COLA::Texture2D::Create("assets/textures/Checkerboard.png");
        m_LogoTexture = COLA::Texture2D::Create("assets/textures/Logo.png");

        std::dynamic_pointer_cast<COLA::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<COLA::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    }
    void OnUpdate(COLA::Timestep ts) override
    {
        m_CameraController.OnUpdate(ts);
        COLA::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        COLA::RenderCommand::Clear();
        COLA::Renderer::BeginScene(m_CameraController.GetCamera());


        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        std::dynamic_pointer_cast<COLA::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<COLA::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                COLA::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }
        auto textureShader = m_ShaderLibrary.Get("Texture");
        m_Texture->Bind();

        COLA::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_LogoTexture->Bind();

        COLA::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        COLA::Renderer::EndScene();
    }
    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }
    void OnEvent(COLA::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }
private:
    COLA::ShaderLibrary m_ShaderLibrary;
    COLA::Ref<COLA::Shader> m_Shader;
    COLA::Ref<COLA::VertexArray> m_VertexArray;

    COLA::Ref<COLA::Shader> m_FlatColorShader;
    COLA::Ref<COLA::VertexArray> m_SquareVA;

    COLA::Ref<COLA::Texture2D> m_Texture, m_LogoTexture;

    COLA::OrthographicCameraController m_CameraController;
   
    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
class Sandbox : public COLA::Application
{
public:
    Sandbox()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }
    ~Sandbox()
    {
    }
};
COLA::Application* COLA::CreateApplication()
{
    return new Sandbox();
}