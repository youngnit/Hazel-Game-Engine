#pragma once

#include "Events.h"


namespace COLA
{
    class COLA_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keycode) : m_KeyCode(keycode) {}
        int m_KeyCode;
    };
    class COLA_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
        inline int GetRepeatCount() { return m_RepeatCount; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "键盘事件: " << (char)m_KeyCode << " (" << m_RepeatCount << "repeats)";
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };
    class COLA_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) :KeyEvent(keycode) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "键盘按键释放事件: " << (char)m_KeyCode ;
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyReleased)
    };
    class COLA_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "键盘类型事件: " << (char)m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}