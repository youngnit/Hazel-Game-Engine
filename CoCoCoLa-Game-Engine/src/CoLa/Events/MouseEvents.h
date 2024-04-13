#pragma once

#include "Events.h"

#include <sstream>

namespace Cola
{

    class MouseMovedEvent :public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << GetX() << "," << GetY();
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
    private:
        float m_MouseX, m_MouseY;
    };
    class COLA_API MouseScrolledEvent :public Event
    {
    public:
        MouseScrolledEvent(float xoffset, float yoffset) : m_Xoffset(xoffset), m_Yoffset(yoffset) {}
        inline float GetXOffset() const { return m_Xoffset; }
        inline float GetYOffset() const { return m_Yoffset; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << "," << GetYOffset();
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
    private:
        float m_Xoffset, m_Yoffset;
    };
    class COLA_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() { return m_Button; }
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
    protected:
        MouseButtonEvent(int button) : m_Button(button) {}
        int m_Button;
    };
    class COLA_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) :MouseButtonEvent(button) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
    };
    class COLA_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) :MouseButtonEvent(button) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtoReleasedEvent: " << m_Button;
            return ss.str();
        }
    };
}