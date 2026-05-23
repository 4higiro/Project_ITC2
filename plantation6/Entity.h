#pragma once

#include "EventProcessor.h"
#include "Engine.h"

class EntityEventAdapter : public EventProcessor
{
protected:
	bool from_adapter = false;

public:
	bool adapter_mode = false;

	void jump();
	void left();
	void right();
	void forward();
	void back();
	void reset();

	static constexpr sf::Keyboard::Key jump_button = sf::Keyboard::Space;
	static constexpr sf::Keyboard::Key left_button = sf::Keyboard::A;
	static constexpr sf::Keyboard::Key right_button = sf::Keyboard::D;
	static constexpr sf::Keyboard::Key forward_button = sf::Keyboard::W;
	static constexpr sf::Keyboard::Key back_button = sf::Keyboard::S;
};

class Entity : public EntityEventAdapter
{
private:
	Engine physics;
	Mesh* graphics;
	int health = 100;

protected:
	void keyPressedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift) override;
	void keyReleasedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift) override;

public:
	Entity(float mass, sf::Vector3f pos, Mesh* mesh);

	bool isAlive();
	void emulate(Location& loc);

	static void interaction(Entity& a, Entity& b);
};