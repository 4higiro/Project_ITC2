#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "EventProcessor.h"

class CheckBox : public EventProcessor
{
public:
    CheckBox(sf::Vector2u resolution);
    ~CheckBox() = default;

    bool isChecked() const;
    void setChecked(bool enabled);

    void setSize(unsigned size);
    unsigned getSize();
    void setPosition(sf::Vector2u pos);
    sf::Vector2u getPosition();

    void setName(const std::u16string& text);
    std::u16string getName();

    void render(sf::RenderWindow* window) override;
    sf::Rect<unsigned> mouseArea() override;

protected:
    void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseHitEvent() override;
    void mouseMissedEvent() override;

private:
    void setupGraphics();
    void centerText();
    void updateTexture();
    void updatePosition();

private:
    sf::Vector2u position = { 0,0 };
    unsigned size = 20;
    unsigned real_size;
    unsigned win_height;
    std::u16string label;
    bool checked = false;
    bool hovered = false;

    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;

    sf::Texture unchecked_texture;
    sf::Texture unchecked_hovered_texture;
    sf::Texture checked_texture;
    sf::Texture checked_hovered_texture;
 
    sf::Color text_color = sf::Color(255, 0, 0);
    sf::Color outline_color = sf::Color(44, 62, 80);
};