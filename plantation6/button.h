#pragma once
#include "AbstractGraphics.h"
#include <iostream>
#include <string>

class Action {
public:
    virtual void doAction() = 0;
};

class Button : public AbstractGraphics 
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;  
    bool isPressed = false;
    bool isHovered = false;

    sf::Color normalColor = { 0, 0, 255 };        
    sf::Color pressedColor = { 0, 0, 0 };         
    sf::Color hoverColor = { 128, 128, 128 };     
    sf::Color textColor = { 255, 255, 255 };      
    sf::Vector2u position = { 0, 0 };
    sf::Vector2u size = { 100, 50 };
    sf::Vector2u real_size;
    sf::Vector2u winResolution;

protected:
    void mousePressedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseReleasedEvent(unsigned x, unsigned y, sf::Mouse::Button button) override;
    void mouseHit() override;
    void mouseMissed() override;

public:
    Button(sf::Vector2u windowResolution);

    Action* act = nullptr;
   
    void draw(sf::RenderWindow* window) override;
    sf::Rect<unsigned> area() override;
    void setName(const std::u16string& buttonText);
    std::u16string getName();
    void setPosition(sf::Vector2u pos);
    sf::Vector2u getPosition();
    void setSize(sf::Vector2u newSize);
    sf::Vector2u getSize();
};
