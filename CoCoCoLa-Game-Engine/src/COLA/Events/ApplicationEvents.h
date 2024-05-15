#pragma once
#include "COLA/Core/Core.h"
#include "Events.h"

namespace COLA
{
    class COLA_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned width, unsigned height) :m_Width(width), m_Height(height){}
        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "窗口改变大小事件: " << m_Width << "," << m_Height;
            return ss.str();
        }
        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        unsigned int m_Width, m_Height;
    };
    class COLA_API WindowCloseEvent :public Event
    {
    public:
        WindowCloseEvent() {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "窗口关闭";
            return ss.str();
        }
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
    class COLA_API AppTickEvent :public Event
    {
    public:
        AppTickEvent() {}
        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
    class COLA_API AppUpdateEvent :public Event
    {
    public:
        AppUpdateEvent() {}
        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
    class COLA_API AppRenderEvent :public Event
    {
    public:
        AppRenderEvent() {}
        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}