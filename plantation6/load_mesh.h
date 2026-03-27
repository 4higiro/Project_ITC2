#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
struct mesh_data
{
    std::vector<float> coord;
    std::vector<float> ncoord;
    std::vector<float> color;
    std::vector<float> indices;
};
mesh_data load_mesh(std::string path);
