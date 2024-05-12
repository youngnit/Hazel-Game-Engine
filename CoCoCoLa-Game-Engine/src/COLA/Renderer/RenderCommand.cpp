#include "clpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace COLA {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}