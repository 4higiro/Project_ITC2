#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

struct MeshData
{
	std::vector<float> coords;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<unsigned> indices;
};

using MeshAnimation = std::vector<MeshData>;

MeshData loadMesh(std::string path);
MeshAnimation loadAnimation(std::string folder);
