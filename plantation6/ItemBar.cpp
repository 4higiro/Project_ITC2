#include "ItemBar.h"

#include <SFML/Graphics.hpp>
#include <string>

ItemBar::ItemBar(sf::Vector2u windowResolution)
{
    size = 50;
    real_size = size / 1000.0 * windowResolution.y;
    win_resolution = windowResolution;

    for (int i = 0; i < 5; ++i)
    {
        boxes[i].setFillColor(in_color);
        boxes[i].setOutlineColor(out_color);
        boxes[i].setOutlineThickness(3);
    }

    current_name.setColor(text_color);

    clearItems();
    updateGeometry();
}

void ItemBar::updateGeometry()
{
    for (int i = 0; i < 5; ++i)
    {
        boxes[i].setSize({ static_cast<float>(real_size), static_cast<float>(real_size) });
        boxes[i].setPosition({ static_cast<float>(position.x + i * (real_size + 6)), static_cast<float>(position.y) });
    }

    current_name.setArea({ position.x, position.y + real_size, 5 * (real_size + 6), real_size });
}

void ItemBar::render(sf::RenderWindow* window)
{
    if (!isActive()) return;

    for (int i = 0; i < 5; ++i)
    {
        window->draw(boxes[i]);
    }

    current_name.render(window);
}

sf::Rect<unsigned> ItemBar::mouseArea()
{
    return sf::Rect<unsigned>(0, 0, win_resolution.x, win_resolution.y);
}

void ItemBar::setPosition(sf::Vector2u pos)
{
    position = pos;
    updateGeometry();
}

sf::Vector2u ItemBar::getPosition()
{
    return position;
}

void ItemBar::setSize(unsigned newSize)
{
    size = newSize;
    real_size = size / 1000.0 * win_resolution.y;
    updateGeometry();
}

unsigned ItemBar::getSize()
{
    return size;
}

bool ItemBar::addItem(Item newItem)
{
    for (int i = 0; i < 5; ++i)
    {
        if (items[i].is_empty_item)
        {
            items[i] = newItem;
            boxes[i].setFillColor(sf::Color::Transparent);
            boxes[i].setTexture(&newItem.texture);
            return true;
        }
    }

    return false;
}

void ItemBar::clearItems()
{
    for (int i = 0; i < 5; ++i)
    {
        boxes[i].setFillColor(in_color);
        boxes[i].setTexture(nullptr);
        items[i].is_empty_item = true;
    }
    selection_index = 0;
}

Item ItemBar::getSelectedItem()
{
    return items[selection_index];
}

void ItemBar::mouseScrollEvent(unsigned x, unsigned y, int delta)
{
    selection_index += delta;
    if (selection_index < 0) selection_index = 0;
    if (selection_index >= 5) selection_index = 4;

    Item& currentItem = items[selection_index];
    if (currentItem.is_empty_item)
    {
        current_name.setName(u"");
    }
    else
    {
        current_name.setName(currentItem.name);
    }
    
    for (int i = 0; i < 5; ++i)
    {
        boxes[i].setOutlineColor(i == selection_index ? select_color : out_color);
    }
}
