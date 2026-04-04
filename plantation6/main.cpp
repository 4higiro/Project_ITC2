#include <iostream>
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "main_menu.h"
#include "AbstractGraphics.h"

void main()
{
	sf::RenderWindow main_window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
	sf::Vector2u resolution = main_window.getSize();

	Button play_button(resolution);
	Button settings_button(resolution);
	Button achievements_button(resolution);
	MainMenu main_menu(resolution);
	main_menu.setPlayButton(&play_button);
	main_menu.setSettingsButton(&settings_button);
	main_menu.setAchievementsButton(&achievements_button);
	


	AbstractGraphics* draw_objects[] = {
		
		&main_menu,& play_button,& settings_button,& achievements_button
		
	

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