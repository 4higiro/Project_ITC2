#pragma once

#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>

class Transformation
{
public:
	float psi = 0.0f, tetta = 0.0f, gamma = 0.0f;
	float k = 1.0f;
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Transformation();

	float* getRotPsi();
	float* getRotTetta();
	float* getRotGamma();
	float* getScale();
	float* getTrans();

private:
	std::vector<float> rot_psi;
	std::vector<float> rot_tetta;
	std::vector<float> rot_gamma;
	std::vector<float> scale;
	std::vector<float> trans;
};

class Camera
{
public:
	Transformation view;

	Camera(sf::Vector2u resolution);
	float* getProjection();

private:
	std::vector<float> projection;
};

struct MeshData
{
	std::vector<float> coords;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<unsigned> indices;
};

class Mesh
{
public:
	Transformation model;
	MeshData data;

	Mesh(const MeshData& data);
	void draw();

private:
	unsigned coords_buf, colors_buf, normals_buf, indices_buf;
	unsigned arrays;
};

class Scene
{
public:
	Scene();
	void draw(Camera& cam, Mesh& mesh);

private:
	unsigned shader_program;

	std::vector<float> light_pos = { 0.0, 1.0, 0.0 };
};
