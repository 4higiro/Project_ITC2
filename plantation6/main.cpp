#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AbstractGraphics.h"

void main()
{
	sf::RenderWindow main_window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
	sf::Vector2u resolution = main_window.getSize();

	// Здесь создаете объект вашего класса, например:
	// Button start_game;


	AbstractGraphics* draw_objects[] = {
		// Здесь добавляете в массив ссылку на ваш объект, например:
		// *другие ссылки*..., &start_game
		nullptr
	};
	constexpr int n_draw_objects = sizeof(draw_objects) / sizeof(AbstractGraphics*);
	
	while (main_window.isOpen()) // цикл отрисовки кадра
	{
		main_window.clear(sf::Color(255, 255, 255));

		sf::Event main_window_event;
		while (main_window.pollEvent(main_window_event)) // цикл обработки событий
		{
			if (main_window_event.type == sf::Event::Closed
			 || main_window_event.type == sf::Event::EventType::KeyPressed
			 && main_window_event.key.code == sf::Keyboard::Escape)
			{
				main_window.close();
				break;
			}

			for (int i = 0; i < n_draw_objects; ++i)
			{
				if (draw_objects[i]->isVisible())
				{
					if (main_window_event.type == sf::Event::EventType::MouseButtonPressed
					 || main_window_event.type == sf::Event::EventType::MouseButtonReleased
					 || main_window_event.type == sf::Event::EventType::MouseMoved
					 || main_window_event.type == sf::Event::EventType::MouseWheelScrolled)
					{
						sf::Vector2u pos = { (unsigned)main_window_event.mouseButton.x, (unsigned)main_window_event.mouseButton.y };
						if (main_window_event.type == sf::Event::EventType::MouseMoved)
							pos = { (unsigned)main_window_event.mouseMove.x, (unsigned)main_window_event.mouseMove.y };
						if (main_window_event.type == sf::Event::EventType::MouseWheelScrolled)
							pos = { (unsigned)main_window_event.mouseWheel.x, (unsigned)main_window_event.mouseWheel.y };
						if (draw_objects[i]->area().contains(pos) || draw_objects[i]->isMouseHover()) draw_objects[i]->event(main_window_event);
					}
					else draw_objects[i]->event(main_window_event);
				}
			}
		}

		for (int i = 0; i < n_draw_objects; ++i)
		{
			if (draw_objects[i]->isVisible())
				draw_objects[i]->draw(&main_window);
		}
		
		main_window.display();
	}
}