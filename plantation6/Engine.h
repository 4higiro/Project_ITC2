#pragma once

#include "EventProcessor.h"
#include "Scene.h"

#include <chrono>

MeshData constructFloor(float y_level);
MeshData constructRandomWall();

struct Location
{
	MeshData* floor;
	MeshData* walls[10];

	void correctionSpeed(sf::Vector3f S, sf::Vector3f& V);
};

class Engine
{
private:
	float m;
	sf::Vector3f S, V;
	sf::Vector3f Fext;
	
	std::chrono::steady_clock::time_point t0;
public:
	Engine(float mass, sf::Vector3f S0, sf::Vector3f V0);

	void setExternalForce(sf::Vector3f F);
	sf::Vector3f calcPosition(Location& loc, bool reset_time = false);
};