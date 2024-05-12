#include "clpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace COLA {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    COLA_CORE_ASSERT(false, "RendererAPI::目前不支持!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
        }

        COLA_CORE_ASSERT(false, "未知 RendererAPI!");
        return nullptr;
    }

}