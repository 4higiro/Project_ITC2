#include "LoadMesh.h"

MeshData loadMesh(std::string path)
{
    int size1;
    int size2;
    int umpty;
    std::string str;
    std::ifstream f;
    f.open(path);
    MeshData mesh_data;
    while (true)
    {
        f >> str;
        if (str == "vertex")
        {
            f >> size1;
            mesh_data.colors.resize(size1 * 3);
            mesh_data.normals.resize(size1 * 3);
            mesh_data.coords.resize(size1 * 3);

            break;
        }
    }
    while (true)
    {
        f >> str;
        if (str == "face")
        {
            f >> size2;
            mesh_data.indices.resize(size2 * 3);
            break;
        }
    }
    while (true)
    {

        f >> str;
        if (str == "end_header")
        {
            for (int i = 0; i < size1;++i)
            {
                std::vector<float> du(9);
                for (int k = 0; k < 9;++k)
                {
                    f >> du[k];
                }
                mesh_data.coords[0 + i * 3] = du[0];
                mesh_data.coords[1 + i * 3] = du[1];
                mesh_data.coords[2 + i * 3] = du[2];
                mesh_data.normals[0 + i * 3] = du[3];
                mesh_data.normals[1 + i * 3] = du[4];
                mesh_data.normals[2 + i * 3] = du[5];
                mesh_data.colors[0 + i * 3] = du[6];
                mesh_data.colors[1 + i * 3] = du[7];
                mesh_data.colors[2 + i * 3] = du[8];

            }
            for (int i = 0; i < size2; ++i)
            {
                f >> umpty;
                std::vector<float> du(3);
                for (int k = 0; k < 3; ++k)
                {
                    f >> du[k];
                }
                mesh_data.indices[0 + i * 3] = du[0];
                mesh_data.indices[1 + i * 3] = du[1];
                mesh_data.indices[2 + i * 3] = du[2];

            }
            break;

        }
    }

    f.close();
    return mesh_data;
}

MeshAnimation loadAnimation(std::string folder)
{
    MeshAnimation end;
    std::filesystem::path papka_file(folder);
    std::string imp = folder + "/all_mesh";
    std::filesystem::path all_mesh(imp);
    std::filesystem::create_directory(all_mesh);
    int i = 0;

    for (auto const& dir_entry : std::filesystem::directory_iterator(papka_file))
    {
        if (dir_entry.path().extension() == ".ply")
        {
            ++i;
            std::string filename = dir_entry.path().filename().string();
            std::filesystem::path dest = all_mesh / filename;
            std::filesystem::copy_file(dir_entry.path(), dest);
        }
    }
    int k = 0;
    std::string text = folder + "/all_mesh/mesh_0.ply";
    std::string x = folder + "/all_mesh/mesh_";
    std::string y = ".ply";
    end.resize(i);
    for (int j = 0;j < i;++j)
    {
        for (auto const& dir_entry : std::filesystem::directory_iterator(all_mesh))
        {
            if (dir_entry.path() == text)
            {
                ++k;
                text = x + std::to_string(j + 1) + y;
                end[j] = loadMesh(dir_entry.path().string());
                break;
            }
        }

    }


    return end;
}