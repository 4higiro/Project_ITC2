#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class EventProcessor
{
protected:
    virtual void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) {}
    virtual void mouseReleasedEvent(unsigned x, unsigned y, sf::Mouse::Button button) {}
    virtual void mouseMoveEvent(unsigned x, unsigned y) {}
    virtual void mouseScrollEvent(unsigned x, unsigned y, int delta) {}
    virtual void mouseHitEvent() {}
    virtual void mouseMissedEvent() {}

    virtual void keyPressedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift) {}
    virtual void keyReleasedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift) {}

    virtual void showEvent() {};
    virtual void hideEvent() {};

public:
    void event(sf::Event e)
    {
        bool prev_is_mouse_hover = is_mouse_hover;

        switch (e.type)
        {
        case sf::Event::EventType::MouseButtonPressed:
            mousePressedEvent(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
            is_mouse_hover = mouseArea().contains(sf::Vector2u(e.mouseButton.x, e.mouseButton.y));
            break;
        case sf::Event::EventType::MouseButtonReleased:
            mouseReleasedEvent(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
            is_mouse_hover = mouseArea().contains(sf::Vector2u(e.mouseButton.x, e.mouseButton.y));
            break;
        case sf::Event::EventType::MouseMoved:
            mouseMoveEvent(e.mouseMove.x, e.mouseMove.y);
            is_mouse_hover = mouseArea().contains(sf::Vector2u(e.mouseMove.x, e.mouseMove.y));
            break;
        case sf::Event::EventType::MouseWheelScrolled:
            mouseScrollEvent(e.mouseWheelScroll.x, e.mouseWheelScroll.y, e.mouseWheelScroll.delta);
            is_mouse_hover = mouseArea().contains(sf::Vector2u(e.mouseWheelScroll.x, e.mouseWheelScroll.y));
            break;
        case sf::Event::EventType::KeyPressed:
            keyPressedEvent(e.key.code, e.key.control, e.key.alt, e.key.shift);
            break;
        case sf::Event::EventType::KeyReleased:
            keyReleasedEvent(e.key.code, e.key.control, e.key.alt, e.key.shift);
            break;
        }

        if (prev_is_mouse_hover && !is_mouse_hover) mouseMissedEvent();
        if (!prev_is_mouse_hover && is_mouse_hover) mouseHitEvent();
    }

    virtual void render(sf::RenderWindow* window) = 0;
    virtual sf::Rect<unsigned> mouseArea() = 0;

    void show()
    {
        is_active = true;
        showEvent();
    }

    void hide()
    {
        is_active = false;
        hideEvent();
    }

    bool isActive()
    {
        return is_active;
    }

    bool isMouseHover()
    {
        return is_mouse_hover;
    }
private:
    bool is_active = true;
    bool is_mouse_hover = false;
};