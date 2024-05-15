#pragma once

// 给SandboxApp准备的(应用程序)

#include "COLA/Core/Core.h"
#include "COLA/Core/Application.h"
#include "COLA/Core/Log.h"
#include "COLA/Core/Layer.h"
#include "COLA/Core/LayerStack.h"
#include "COLA/Core/Window.h"
#include "COLA/Core/Input.h"
#include "COLA/Core/MouseButtonCodes.h"
#include "COLA/Core/KeyCodes.h"

#include "COLA/Events/ApplicationEvents.h"
#include "COLA/Events/Events.h"
#include "COLA/Events/KeyEvents.h"
#include "COLA/Events/MouseEvents.h"

#include "COLA/ImGui/ImGuiLayer.h"

#include "COLA/Renderer/OrthographicCameraController.h"

#include "COLA/Renderer/Buffer.h"
#include "COLA/Renderer/GraphicsContext.h"
#include "COLA/Renderer/OrthographicCamera.h"
#include "COLA/Renderer/RenderCommand.h"
#include "COLA/Renderer/Renderer.h"
#include "COLA/Renderer/RendererAPI.h"
#include "COLA/Renderer/Shader.h"
#include "COLA/Renderer/VertexArray.h"
#include "COLA/Renderer/Texture.h"
#include "COLA/Renderer/OrthographicCamera.h"
#include "COLA/Renderer/Renderer2D.h"


#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "COLA/CORE/Timestep.h"
//----------程序入口点-----------
//#include "COLA/Core/EntryPoint.h"
//-----------------------------