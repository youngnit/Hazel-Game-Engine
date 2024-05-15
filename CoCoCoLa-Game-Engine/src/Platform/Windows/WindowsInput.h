#pragma once

#include "COLA/Core/Input.h"

namespace COLA
{
    class WindowsInput :public Input
    {
    public:
        
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsKMouseButtonImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    private:
        
    };
}