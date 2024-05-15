#pragma once

#include "COLA/Core/Layer.h"

#include "COLA/Core/Core.h"

namespace COLA {
    class COLA_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* layer);
        void PopLayer(Layer* layer);
        void PopOverLay(Layer* layer);

        inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    protected:

    private:

        std::vector<Layer*>m_Layers;
        //std::vector<Layer*>::iterator m_LayerInsert;
        unsigned int m_LayerInsertIndex = 0;
    };
}