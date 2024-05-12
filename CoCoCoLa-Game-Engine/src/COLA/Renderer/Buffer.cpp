#include "clpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace COLA {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    COLA_CORE_ASSERT(false, "RendererAPI::目前不支持!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
        }

        COLA_CORE_ASSERT(false, "未知 RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    COLA_CORE_ASSERT(false, "RendererAPI::目前不支持!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
        }

        COLA_CORE_ASSERT(false, "未知 RendererAPI!");
        return nullptr;
    }

}