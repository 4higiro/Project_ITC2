#include <SFML/Window.hpp>
#include <iostream>

#include "main_menu.h"
#include "AbstractGraphics.h"
#include "Scene.h"

void main()
{
	sf::ContextSettings ogl_context;
	ogl_context.majorVersion = 3;
	ogl_context.minorVersion = 3;
	ogl_context.attributeFlags = sf::ContextSettings::Default;
	ogl_context.depthBits = 24;
	ogl_context.stencilBits = 8;
	ogl_context.antialiasingLevel = 4;

	sf::RenderWindow main_window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen, ogl_context);
	sf::Vector2u resolution = main_window.getSize();

	main_window.setActive(true);
	Scene main_scene;
	Camera main_camera(resolution);

	Mesh* mesh_list[] = {
		nullptr
	};
	constexpr int n_meshes = sizeof(mesh_list) / sizeof(Mesh*);

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
		// сцена рисуется новым OpenGL 3.3 Core
		for (int i = 0; i < n_meshes; ++i)
		{
			if (!mesh_list[i]) continue;
			main_scene.draw(main_camera, *mesh_list[i]);
		}

		// интерфейс рисуется старым OpenGL примитивами SFML
		main_window.pushGLStates();

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
				if (draw_objects[i] && draw_objects[i]->isVisible())
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

		main_window.popGLStates();
		
		main_window.display();
	}
}