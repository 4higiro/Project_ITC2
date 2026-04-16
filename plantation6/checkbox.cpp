#include "CheckBox.h"

#include <iostream>

CheckBox::CheckBox(sf::Vector2u resolution)
    : win_height(resolution.y)
{
    real_size = size * win_height / 1000.0;

    checked_hovered_texture.loadFromFile("resources/CheckedHovered.png");
    checked_texture.loadFromFile("resources/Checked.png");
    unchecked_hovered_texture.loadFromFile("resources/UncheckedHovered.png");
    unchecked_texture.loadFromFile("resources/Unchecked.png");
    font.loadFromFile("resources/Strogo-Regular.ttf");

    setupGraphics();
}

bool CheckBox::isChecked() const
{
    return checked;
}

void CheckBox::setChecked(bool enabled)
{
    checked = enabled;
    updateTexture();
}

void CheckBox::setSize(unsigned size)
{
    size = size;
    real_size = size * win_height / 1000.0;
    setupGraphics();
}

unsigned CheckBox::getSize()
{
    return size;
}

void CheckBox::setPosition(sf::Vector2u pos)
{
    position = pos;
    updatePosition();
}
sf::Vector2u CheckBox::getPosition()
{
    return position;
}
void CheckBox::setName(const std::u16string& text)
{
    label = text;
    setupGraphics();
}

std::u16string CheckBox::getName()
{
    return label;
}

void CheckBox::updatePosition()
{
    box.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
    centerText();
}

void CheckBox::render(sf::RenderWindow* window)
{
    if (!isActive()) return;

    window->draw(box);
    window->draw(text);
}

sf::Rect<unsigned> CheckBox::mouseArea()
{
    float text_width = text.getLocalBounds().width;
    return sf::Rect<unsigned>(
        position.x,
        position.y,
        real_size + 5 + static_cast<unsigned>(text_width),
        real_size 
    );
}

void CheckBox::mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left)
    {
        checked = !checked;
        updateTexture();
    }
}


void CheckBox::mouseHitEvent()
{
    hovered = true;
    updateTexture();
}
void CheckBox::mouseMissedEvent()
{
    hovered = false;
    updateTexture();
}

void CheckBox::setupGraphics()
{
    box.setSize(sf::Vector2f(real_size, real_size));
    box.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
    box.setOutlineThickness(2);
    box.setOutlineColor(outline_color);
    updateTexture();

    text.setFont(font);
    text.setString(sf::String::fromUtf16(label.begin(), label.end()));
    text.setCharacterSize(static_cast<unsigned>(real_size * 0.8f));
    text.setFillColor(text_color);
    text.setCharacterSize(real_size);
    centerText();
}

void CheckBox::centerText()
{
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        static_cast<float>(position.x + real_size + 5),
        static_cast<float>(position.y + (real_size - textBounds.height) / 2 - textBounds.top)
    );
}

void CheckBox::updateTexture()
{
    if (checked && hovered)
    {
        box.setTexture(&checked_hovered_texture);
    }
    else if (checked && !hovered)
    {
        box.setTexture(&checked_texture);
    }
    else if (!checked && hovered)
    {
        box.setTexture(&unchecked_hovered_texture);
    }
    else
    {
        box.setTexture(&unchecked_texture);
    }
}
