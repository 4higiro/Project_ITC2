#include "load_mesh.h"
mesh_data load_mesh(std::string path)
{
    int size1;
    int size2;
    int umpty;
    std::string str;
    std::ifstream f;
    f.open(path);
    mesh_data mesh_data;
    if (f.is_open())
    {
        std::cout << "ply";
    }
    while (true)
    {
        f >> str;
        if (str == "vertex")
        {
            f >> size1;
            mesh_data.color.resize(size1 * 3);
            mesh_data.ncoord.resize(size1 * 3);
            mesh_data.coord.resize(size1 * 3);

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
                mesh_data.coord[0 + i * 3] = du[0];
                mesh_data.coord[1 + i * 3] = du[1];
                mesh_data.coord[2 + i * 3] = du[2];
                mesh_data.ncoord[0 + i * 3] = du[3];
                mesh_data.ncoord[1 + i * 3] = du[4];
                mesh_data.ncoord[2 + i * 3] = du[5];
                mesh_data.color[0 + i * 3] = du[6];
                mesh_data.color[1 + i * 3] = du[7];
                mesh_data.color[2 + i * 3] = du[8];

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