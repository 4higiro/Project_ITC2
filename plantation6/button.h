#pragma once

#include <iostream>
#include <string>

#include "EventProcessor.h"

class Action {
public:
    virtual void doAction() = 0;
};

class Button : public EventProcessor
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;  
    bool is_pressed = false;
    bool is_hovered = false;

    sf::Color normal_color = { 0, 0, 255 };        
    sf::Color pressed_color = { 0, 0, 0 };         
    sf::Color hover_color = { 128, 128, 128 };     
    sf::Color text_color = { 255, 255, 255 };      
    sf::Vector2u position = { 0, 0 };
    sf::Vector2u size = { 100, 50 };
    sf::Vector2u real_size;
    sf::Vector2u win_resolution;

    std::u16string name;

protected:
    void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseReleasedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseHitEvent() override;
    void mouseMissedEvent() override;

public:
    Button(sf::Vector2u window_resolution);

    Action* act = nullptr;
   
    void render(sf::RenderWindow* window) override;
    sf::Rect<unsigned> mouseArea() override;
    void setName(const std::u16string& button_text);
    std::u16string getName();
    void setPosition(sf::Vector2u pos);
    sf::Vector2u getPosition();
    void setSize(sf::Vector2u new_size);
    sf::Vector2u getSize();
};
