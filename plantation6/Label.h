#pragma once

#include <SFML/Graphics.hpp>
#include <string> 

#include "EventProcessor.h"

class Label : public EventProcessor
{
public:
    Label();

    void setName(const std::u16string& name);
    std::u16string getName();
    void setArea(sf::Rect<unsigned> rect);
    void setColor(sf::Color col);
    sf::Color getColor();

    void render(sf::RenderWindow* window) override;
    sf::Rect<unsigned> mouseArea() override;

private:
    void centerText();

private:
    sf::Rect<unsigned> area;
    std::u16string label;

    sf::Text text;
    sf::Font font;
    sf::Color color = sf::Color::Red;
};

