#include "MainMenu.h"

#include <iostream>
#include <sstream>


void MainMenu::setPlayButton(Button* btn)
{
    play = btn;
    play->setName(u"Play");
    play->setPosition(sf::Vector2u(800, 300));
    play->setSize(sf::Vector2u(400, 100));
}

void MainMenu::setSettingsButton(Button* btn)
{
    settings = btn;
    settings->setName(u"Settings");
    settings->setPosition(sf::Vector2u(800, 450));
    settings->setSize(sf::Vector2u(400, 100));
}

void MainMenu::setAchievementsButton(Button* btn)
{
    achievements = btn;
    achievements->setName(u"Achievements");
    achievements->setPosition(sf::Vector2u(800, 600));
    achievements->setSize(sf::Vector2u(400, 100));
}

void MainMenu::render(sf::RenderWindow* window) {}
sf::Rect<unsigned> MainMenu::mouseArea() { return sf::Rect<unsigned>(); }

void MainMenu::showEvent()
{
    if (play) play->show();
    if (settings) settings->show();
    if (achievements) achievements->show();
}

void MainMenu::hideEvent()
{
    if (play) play->hide();
    if (settings) settings->hide();
    if (achievements) achievements->hide();
}



