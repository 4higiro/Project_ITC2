#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class AbstractGraphics
{
protected:
    virtual void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) {}
    virtual void mouseReleasedEvent(unsigned x, unsigned y, sf::Mouse::Button button) {}
    virtual void mouseMoveEvent(unsigned x, unsigned y) {}
    virtual void mouseScrollEvent(unsigned x, unsigned y, int delta) {}
    virtual void mouseHit() {}
    virtual void mouseMissed() {}

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
            is_mouse_hover = area().contains(sf::Vector2u(e.mouseButton.x, e.mouseButton.y));
            break;
        case sf::Event::EventType::MouseButtonReleased:
            mouseReleasedEvent(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
            is_mouse_hover = area().contains(sf::Vector2u(e.mouseButton.x, e.mouseButton.y));
            break;
        case sf::Event::EventType::MouseMoved:
            mouseMoveEvent(e.mouseMove.x, e.mouseMove.y);
            is_mouse_hover = area().contains(sf::Vector2u(e.mouseMove.x, e.mouseMove.y));
            break;
        case sf::Event::EventType::MouseWheelScrolled:
            mouseScrollEvent(e.mouseWheel.x, e.mouseWheel.y, e.mouseWheel.delta);
            is_mouse_hover = area().contains(sf::Vector2u(e.mouseWheel.x, e.mouseWheel.y));
            break;
        case sf::Event::EventType::KeyPressed:
            keyPressedEvent(e.key.code, e.key.control, e.key.alt, e.key.shift);
            break;
        case sf::Event::EventType::KeyReleased:
            keyReleasedEvent(e.key.code, e.key.control, e.key.alt, e.key.shift);
            break;
        }

        if (prev_is_mouse_hover && !is_mouse_hover) mouseMissed();
        if (!prev_is_mouse_hover && is_mouse_hover) mouseHit();
    }

    virtual void draw(sf::RenderWindow* window) = 0;
    virtual sf::Rect<unsigned> area() = 0;

    void show()
    {
        is_visible = true;
        showEvent();
    }

    void hide()
    {
        is_visible = false;
        hideEvent();
    }

    bool isVisible()
    {
        return is_visible;
    }

    bool isMouseHover()
    {
        return is_mouse_hover;
    }
private:
    bool is_visible = true;
    bool is_mouse_hover = false;
};