#include "ItemBar.h"

#include <SFML/Graphics.hpp>
#include <string>

ItemBar::ItemBar(sf::Vector2u windowResolution)
{
    size = 50;
    realSize = size / 1000.0 * windowResolution.y;
    winResolution = windowResolution;

    for (int i = 0; i < maxItemsCount; ++i)
    {
        boxes[i].setFillColor(inColor);
        boxes[i].setOutlineColor(outColor);
        boxes[i].setOutlineThickness(3);
        boxes[i].setSize({ static_cast<float>(realSize), static_cast<float>(realSize) });
        boxes[i].setPosition({ static_cast<float>(i * (realSize + 6)), 0.0f });
    }

    items.reserve(maxItemsCount);

    clearItems();
    setupGraphics();
}

void ItemBar::setupGraphics()
{
    for (int i = 0; i < maxItemsCount; ++i)
    {
        boxes[i].setSize({ static_cast<float>(realSize), static_cast<float>(realSize) });
        boxes[i].setPosition({ static_cast<float>(position.x + i * (realSize + 6)),
                               static_cast<float>(position.y) });
        // Проверяем, есть ли предмет в этой ячейке
        if (i < static_cast<int>(items.size()))
        {
            boxes[i].setFillColor(sf::Color::Transparent);
            boxes[i].setTexture(&items[i].texture);
        }
        else
        {
            // Ячейка без предмета - закрашенная
            boxes[i].setFillColor(inColor);
            boxes[i].setTexture(nullptr);
        }
        if (i == selectionIndex)
        {

            boxes[i].setOutlineColor(selectColor);
            boxes[i].setOutlineThickness(3);
        }
        else
        {
           
            boxes[i].setOutlineColor(outColor);
            boxes[i].setOutlineThickness(1);
        }
    }
}

void ItemBar::render(sf::RenderWindow* window)
{
    setupGraphics();

    for (int i = 0; i < 5; ++i)
    {
        window->draw(boxes[i]);
    }

    currentName.render(window);
}

sf::Rect<unsigned> ItemBar::mouseArea()
{
    return sf::Rect<unsigned>(0, 0, winResolution.x, winResolution.y);
}

void ItemBar::setPosition(sf::Vector2u pos)
{
    position = pos;
}

sf::Vector2u ItemBar::getPosition()
{
    return position;
}

void ItemBar::setSize(unsigned newSize)
{
    size = newSize;
    realSize = size / 1000.0 * winResolution.y;
}

unsigned ItemBar::getSize()
{
    return size;
}

bool ItemBar::addItem(Item newItem)
{
    if (items.size() < maxItemsCount)
    {
        items.push_back(newItem);
        boxes[items.size() - 1].setTexture(&newItem.texture);
        return true;
    }
    else return false;
}

void ItemBar::clearItems()
{
    items.clear();
    for (int i = 0; i < 5; ++i)
    {
        boxes[i].setTexture(nullptr);
    }
    selectionIndex = 0;
}

Item ItemBar::getSelectedItem()
{
    if (!items.empty() && selectionIndex >= 0 && selectionIndex < static_cast<int>(items.size()))
    {
        return items[selectionIndex];
    }
    return Item();
}

void ItemBar::mouseScrollEvent(unsigned x, unsigned y, int delta)
{
    selectionIndex += delta;
    if (selectionIndex < 0) selectionIndex = 0;
    if (selectionIndex >= maxItemsCount) selectionIndex = maxItemsCount - 1;
}
