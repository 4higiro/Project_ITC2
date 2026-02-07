#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void main()
{
	sf::RenderWindow main_window(sf::VideoMode(500, 500), "window");
	sf::Event::EventType;
	while (main_window.isOpen()) // цикл отрисовки кадра
	{
		sf::Event main_window_event;
		while (main_window.pollEvent(main_window_event)) // цикл обработки событий
		{
			if (main_window_event.type == sf::Event::Closed)
			{
				main_window.close();
			}
		}
	}
}