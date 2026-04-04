#include "main_menu.h"
#include <iostream>
#include <sstream>


MainMenu::MainMenu(sf::Vector2u windowSize)
    : play(nullptr), settings(nullptr), achievements(nullptr), windowSize(windowSize)
{
    background.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));

    // Загружаем текстуру из папки resources
    if (backgroundTexture.loadFromFile("resources/menu_background.png"))
    {
        background.setTexture(&backgroundTexture);
    }
    else
    {
        // Если текстура не загрузилась, используем запасной цвет
        background.setFillColor(sf::Color(50, 50, 80));
    }
}

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
    settings->setName(u"settings");
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

void MainMenu::draw(sf::RenderWindow* window)
{
    if (!isVisible()) return;
    window->draw(background);

    if (play) play->draw(window);
    if (settings) settings->draw(window);
    if (achievements) achievements->draw(window);
}

sf::Rect<unsigned> MainMenu::area()
{
    return sf::Rect<unsigned>(0, 0, windowSize.x, windowSize.y);
}

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



