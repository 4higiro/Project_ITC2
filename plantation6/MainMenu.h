#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "EventProcessor.h"
#include "Button.h"

class MainMenu : public EventProcessor
{
public:
    MainMenu(sf::Vector2u windowSize);
    ~MainMenu() = default;


    void setPlayButton(Button* btn);
    void setSettingsButton(Button* btn);
    void setAchievementsButton(Button* btn);


    // Переопределённые методы AbstractGraphics
    void render(sf::RenderWindow* window) override;
    sf::Rect<unsigned> mouseArea() override;

protected:
    void showEvent() override;
    void hideEvent() override;

private:
    Button* play, *settings, *achievements;
    sf::Vector2u windowSize;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;   // храним текстуру, чтобы она не уничтожилась
};