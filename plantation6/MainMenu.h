#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "EventProcessor.h"
#include "Button.h"
#include "Label.h"

class MainMenu : public EventProcessor
{
public:
    MainMenu();

    void setPlayButton(Button* btn);
    void setSettingsButton(Button* btn);
    void setAchievementsButton(Button* btn);

    void render(sf::RenderWindow* window) override;
    sf::Rect<unsigned> mouseArea() override;

protected:
    void showEvent() override;
    void hideEvent() override;

private:
    Button* play, *settings, *achievements;
    Label name;
};