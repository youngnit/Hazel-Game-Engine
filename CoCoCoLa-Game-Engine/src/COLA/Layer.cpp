#include "clpch.h"
#include "Layer.h"
namespace COLA
{

    Layer::Layer(const std::string& debugname /*= "Layer"*/)
        :m_DebugName(debugname)
    {

    }

    Layer::~Layer()
    {

    }
    inline void Layer::OnUpdate() {}
}
