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

    virtual void keyPressedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift) {}
    virtual void keyReleasedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift) {}

    virtual void resizeEvent(unsigned width, unsigned height) = 0;
    virtual void showEvent() = 0;
    virtual void hideEvent() = 0;

public:
    void event(sf::Event e)
    {
        switch (e.type)
        {
        case sf::Event::EventType::MouseButtonPressed:
            mousePressedEvent(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
            break;
        case sf::Event::EventType::MouseButtonReleased:
            mouseReleasedEvent(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
            break;
        case sf::Event::EventType::MouseMoved:
            mouseMoveEvent(e.mouseMove.x, e.mouseMove.y);
            break;
        case sf::Event::EventType::MouseWheelScrolled:
            mouseScrollEvent(e.mouseWheel.x, e.mouseWheel.y, e.mouseWheel.delta);
            break;
        case sf::Event::EventType::KeyPressed:
            keyPressedEvent(e.key.code, e.key.control, e.key.alt, e.key.shift);
            break;
        case sf::Event::EventType::KeyReleased:
            keyReleasedEvent(e.key.code, e.key.control, e.key.alt, e.key.shift);
            break;
        case sf::Event::EventType::Resized:
            resizeEvent(e.size.width, e.size.height);
            break;
        }
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
private:
    bool is_visible = false;
};