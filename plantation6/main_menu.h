#pragma once

#include "AbstractGraphics.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class MainMenu : public AbstractGraphics
{
public:
    MainMenu(sf::Vector2u windowSize);
    ~MainMenu() = default;


    void setPlayButton(Button* btn);
    void setSettingsButton(Button* btn);
    void setAchievementsButton(Button* btn);


    // Переопределённые методы AbstractGraphics
    void draw(sf::RenderWindow* window) override;
    sf::Rect<unsigned> area() override;

protected:
    void showEvent() override;
    void hideEvent() override;

private:
    Button* play, *settings, *achievements;
    sf::Vector2u windowSize;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;   // храним текстуру, чтобы она не уничтожилась
};