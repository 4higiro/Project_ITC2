#include "Entity.h"

void EntityEventAdapter::jump()
{
	if (!adapter_mode) return;
	from_adapter = true;
	keyPressedEvent(jump_button, false, false, false);
	from_adapter = false;
}

void EntityEventAdapter::left()
{
	if (!adapter_mode) return;
	from_adapter = true;
	keyPressedEvent(left_button, false, false, false);
	from_adapter = false;
}

void EntityEventAdapter::right()
{
	if (!adapter_mode) return;
	from_adapter = true;
	keyPressedEvent(right_button, false, false, false);
	from_adapter = false;
}

void EntityEventAdapter::forward()
{
	if (!adapter_mode) return;
	from_adapter = true;
	keyPressedEvent(forward_button, false, false, false);
	from_adapter = false;
}

void EntityEventAdapter::back()
{
	if (!adapter_mode) return;
	from_adapter = true;
	keyPressedEvent(back_button, false, false, false);
	from_adapter = false;
}

void EntityEventAdapter::reset()
{
	if (!adapter_mode) return;
	from_adapter = true;
	keyReleasedEvent((sf::Keyboard::Key)0, false, false, false);
	from_adapter = false;
}

void Entity::keyPressedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift)
{
	if (adapter_mode && !from_adapter) return;
	if (!adapter_mode && from_adapter) return;

	float x = 0.0f, y = 0.0f, z = 0.0f;
	switch (key)
	{
	case jump_button:
		y = 1.0f;
		break;
	case left_button:
		x = -1.0f;
		break;
	case right_button:
		x = 1.0f;
		break;
	case forward_button:
		z = 1.0f;
		break;
	case back_button:
		z = -1.0f;
		break;
	default:
		break;
	}

	physics.setExternalForce(sf::Vector3f(x * physics.getMass() * 25.0f, y * physics.getMass() * 25.0f, z * physics.getMass() * 25.0f));
}

void Entity::keyReleasedEvent(sf::Keyboard::Key key, bool ctrl, bool alt, bool shift)
{
	physics.setExternalForce({ 0.0f, 0.0f, 0.0f });
}

Entity::Entity(float mass, sf::Vector3f pos, Mesh* mesh)
	: physics(mass, pos, { 0.0f, 0.0f, 0.0f }), graphics(mesh) {}

bool Entity::isAlive()
{
	return health > 0;
}

void Entity::emulate(Location& loc)
{
	sf::Vector3f pos = physics.calcPosition(loc);
	graphics->model.x = pos.x;
	graphics->model.y = pos.y;
	graphics->model.z = pos.z;
}

void Entity::interaction(Entity& a, Entity& b)
{
	int& health_a = a.health;
	int& health_b = b.health;
}
