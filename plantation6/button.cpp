#include "Button.h"

Button::Button(sf::Vector2u window_resolution)
{
    real_size.x = size.x / 2000.0 * window_resolution.x;
    real_size.y = size.y / 1000.0 * window_resolution.y;
    win_resolution = window_resolution;

    font.loadFromFile("resources/Strogo-Regular.ttf");

    shape.setSize(sf::Vector2f(real_size.x, real_size.y));
    shape.setFillColor(normal_color);
   
}

void Button::render(sf::RenderWindow* window)
{
    if (isActive()) 
    {
        window->draw(shape);
        window->draw(text);
    }
}

sf::Rect<unsigned> Button::mouseArea()
{
    return sf::Rect<unsigned>(position.x, position.y, real_size.x, real_size.y);
}

void Button::mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left) 
    {
        is_pressed = true;
        shape.setFillColor(pressed_color);
        if (act) act->doAction();
    }
}

void Button::mouseReleasedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left) 
    {
        is_pressed = false;

        if (is_hovered) shape.setFillColor(hover_color);
        else shape.setFillColor(normal_color);
    }
}

void Button::mouseHitEvent()
{
    is_hovered = true;

    if (!is_pressed) shape.setFillColor(hover_color);
}

void Button::mouseMissedEvent()
{
    is_hovered = false;

    if (!is_pressed) shape.setFillColor(normal_color);
}

void Button::setPosition(sf::Vector2u pos)
{
    position = pos;
    shape.setPosition(sf::Vector2f(pos.x, pos.y));

    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setPosition(
        pos.x + (real_size.x - text_bounds.width) / 2,
        pos.y + (real_size.y - text_bounds.height) / 2
    );
}

sf::Vector2u Button::getPosition()
{
    return position;
}

void Button::setSize(sf::Vector2u new_size)
{
    size = new_size;
    real_size.x = size.x / 2000.0 * win_resolution.x;
    real_size.y = size.y / 1000.0 * win_resolution.y;
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

void Button::setName(const std::u16string& button_text)
{
    text.setString(sf::String::fromUtf16(button_text.begin(), button_text.end()));
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(text_color);
    name = button_text;
}

std::u16string Button::getName()
{
    return name;
}