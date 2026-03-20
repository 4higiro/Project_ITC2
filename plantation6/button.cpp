#include "Button.h"

Button::Button(const std::u16string& buttonText, sf::Vector2u windowResolution)
{
    real_size.x = size.x / 2000.0 * windowResolution.x;
    real_size.y = size.y / 1000.0 * windowResolution.y;
    winResolution = windowResolution;

    font.loadFromFile("resources/Strogo-Regular.ttf");

    text.setString(sf::String::fromUtf16(buttonText.begin(), buttonText.end()));
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(textColor);

    shape.setSize(sf::Vector2f(real_size.x, real_size.y));
    shape.setFillColor(normalColor);
   
}

void Button::draw(sf::RenderWindow* window)
{
    if (window) {
        window->draw(shape);
        window->draw(text);
    }
}

sf::Rect<unsigned> Button::area()
{
    return sf::Rect<unsigned>(position.x, position.y, real_size.x, real_size.y);
}

void Button::mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left) {
        isPressed = true;
        shape.setFillColor(pressedColor);
        if (act) act->doAction();
    }
}

void Button::mouseReleasedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left) {
        isPressed = false;

        if (isHovered) {
            shape.setFillColor(hoverColor);
        }
        else {
            shape.setFillColor(normalColor);
        }
    }
}

void Button::mouseHit()
{
    isHovered = true;

    if (!isPressed) {
        shape.setFillColor(hoverColor);
    }
}

void Button::mouseMissed()
{
    isHovered = false;

    if (!isPressed) {
        shape.setFillColor(normalColor);
    }
}

void Button::setPosition(sf::Vector2u pos)
{
    position = pos;
    shape.setPosition(sf::Vector2f(pos.x, pos.y));

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        pos.x + (real_size.x - textBounds.width) / 2,
        pos.y + (real_size.y - textBounds.height) / 2
    );
}

sf::Vector2u Button::getPosition()
{
    return position;
}

void Button::setSize(sf::Vector2u newSize)
{
    size = newSize;
    real_size.x = size.x / 2000.0 * winResolution.x;
    real_size.y = size.y / 1000.0 * winResolution.y;
    shape.setSize(sf::Vector2f(real_size.x, real_size.y));

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (real_size.x - textBounds.width) / 2,
        position.y + (real_size.y - textBounds.height) / 2
    );
}

sf::Vector2u Button::getSize()
{
    return size;
}