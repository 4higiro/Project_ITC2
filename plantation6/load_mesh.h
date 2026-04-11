#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <filesystem>
struct mesh_data
{
    std::vector<float> coord;
    std::vector<float> ncoord;
    std::vector<float> color;
    std::vector<float> indices;
};
struct mesh_animation
{
    bool valid;
    std::vector<mesh_data>  animation;
};
mesh_data load_mesh(std::string path);
mesh_animation load_mesh_folder(std::string folder);
