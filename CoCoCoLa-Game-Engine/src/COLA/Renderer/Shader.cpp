﻿#include "clpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


#include <glad/glad.h>

namespace COLA {

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    COLA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        COLA_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
        
    }
}