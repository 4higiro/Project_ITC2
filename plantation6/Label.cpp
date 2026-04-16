#include "Label.h"
#include <iostream>

Label::Label()
{
    font.loadFromFile("resources/Strogo-Regular.ttf");
    text.setFont(font);
    text.setFillColor(color);

    centerText();
}

void Label::setName(const std::u16string& name)
{
    label = name;
    text.setString(sf::String::fromUtf16(label.begin(), label.end()));

    centerText();
}

std::u16string Label::getName()
{
    return label;
}

void Label::setArea(sf::Rect<unsigned> rect)
{
    area = rect;
    centerText();
}

void Label::setColor(sf::Color col)
{
    color = col;
    text.setFillColor(color);
}

void Label::render(sf::RenderWindow* window)
{
    if (!isActive()) return;
    window->draw(text);
}

sf::Rect<unsigned> Label::mouseArea()
{
    return area;
}

void Label::centerText()
{
    sf::FloatRect bounds = text.getLocalBounds();

    float scaleX = area.width / bounds.width;
    float scaleY = area.height / bounds.height;

    float scale = std::min(scaleX, scaleY);

    scale *= 0.9f;

    unsigned new_size = static_cast<unsigned>(20 * scale);
    if (new_size < 8) new_size = 8;
    if (new_size > 200) new_size = 200;

    text.setCharacterSize(new_size);

    if (area.width > 0 && area.height > 0) 
    {
        float textX = area.left + (area.width - bounds.width) / 2 - bounds.left;
        float textY = area.top + (area.height - bounds.height) / 2 - bounds.top;
        text.setPosition(textX, textY);
    }
}