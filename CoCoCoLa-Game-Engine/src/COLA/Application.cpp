#include "clpch.h"
#include "Application.h"

#include "Core.h"
#include "COLA/Input.h"

#include "COLA/Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace COLA {


    Application* Application::s_Instance = nullptr;

    

    Application::Application()
        : m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
    {
        COLA_CORE_ASSERT(!s_Instance, "应用程序已经存在!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(COLA_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverLay(m_ImGuiLayer);

        //
        m_VertexArray.reset(VertexArray::Create());

        
        float vertices[] = 
        {
            -0.5f, -0.5f,  0.0f,  0.8f,  0.2f,  0.8f,  1.0f,
             0.5f, -0.5f,  0.0f,  0.2f,  0.3f,  0.8f,  1.0f,
             0.0f,  0.5f,  0.0f,  0.8f,  0.8f,  0.2f,  1.0f
        };

        uint32_t indices[] =
        {
            0,1,2
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[] = 
        {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[] = 
        { 
            0, 1, 2, 
            2, 3, 0 
        };
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);


        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            uniform mat4 u_ViewProjection;
			out vec3 v_Position;
            out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
            in vec4 v_Color;
			void main()
			{
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
			}
		)";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
            uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

        std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

        m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    Application::~Application()
    {

    }
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(COLA_BIND_EVENT_FN(Application::OnWindowClose));

        //COLA_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLay(Layer* layer)
    {
        m_LayerStack.PushOverLay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_CodeRunning = 0;
        COLA_CLIENT_ERROR(e.ToString());
        return 1;

    }

    void Application::Run()
    {
        glfwSwapInterval(1);
        /*WindowResizeEvent e (m_Window->GetWidth(), m_Window->GetHeight());
        COLA_CLIENT_TRACE(e.ToString());*/
        while (m_CodeRunning)
        {
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();

            //m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
            //m_Camera.SetRotation(45.0f);
            Renderer::BeginScene(m_Camera);
            
            Renderer::Submit(m_BlueShader, m_SquareVA);
            Renderer::Submit(m_Shader, m_VertexArray);
            Renderer::EndScene();
            
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            //auto pos = Input::GetMousePosition();
            //COLA_CORE_TRACE("{0}, {1}", std::get<0>(pos), std::get<1>(pos));
           
            m_Window->OnUpdate();
                
            
        }
    }

}