#include "Engine.h"

#include <random>
#include <thread>
#include <cmath>

MeshData constructFloor(float y_level)
{
	MeshData floor;
	floor.coords = {
		-10'000.0f, 0.0f, -10'000.0f, 
		-10'000.0f, 0.0f, 10'000.0f, 
		10'000.0f, 0.0f, -10'000.0f, 
		10'000.0f, 0.0f, 10'000.0f 
	};
	
	float r = 200.0f / 255.0f;
	float g = 229.0f / 255.0f;
	float b = 245.0f / 255.0f;

	floor.colors = {
		r, g, b,
		r, g, b,
		r, g, b,
		r, g, b
	};

	floor.normals = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	floor.indices = { 0, 1, 2, 1, 2, 3 };
	return floor;
}

MeshData constructRandomWall()
{
    float width = 10.0f + rand() % 25;
    float depth = 2.0f;
    float height = 5.0f;

    float ang = (rand() % 314) / 100.0f;
    float cos_a = cos(ang);
    float sin_a = sin(ang);

    float centerX = (rand() % 101) - 50;
    float centerZ =  (rand() % 101) - 50;

    float hw = width * 0.5f;
    float hd = depth * 0.5f;
    float hh = height * 0.5f;

    struct Face 
    {
        float vertices[4][3];
        float normal[3];
    };

    Face faces[6];

    faces[0].vertices[0][0] = -hw; faces[0].vertices[0][1] = 0;    faces[0].vertices[0][2] = -hd;
    faces[0].vertices[1][0] = hw; faces[0].vertices[1][1] = 0;    faces[0].vertices[1][2] = -hd;
    faces[0].vertices[2][0] = hw; faces[0].vertices[2][1] = 0;    faces[0].vertices[2][2] = hd;
    faces[0].vertices[3][0] = -hw; faces[0].vertices[3][1] = 0;    faces[0].vertices[3][2] = hd;
    faces[0].normal[0] = 0; faces[0].normal[1] = -1; faces[0].normal[2] = 0;

    faces[1].vertices[0][0] = -hw; faces[1].vertices[0][1] = height; faces[1].vertices[0][2] = -hd;
    faces[1].vertices[1][0] = hw; faces[1].vertices[1][1] = height; faces[1].vertices[1][2] = -hd;
    faces[1].vertices[2][0] = hw; faces[1].vertices[2][1] = height; faces[1].vertices[2][2] = hd;
    faces[1].vertices[3][0] = -hw; faces[1].vertices[3][1] = height; faces[1].vertices[3][2] = hd;
    faces[1].normal[0] = 0; faces[1].normal[1] = 1; faces[1].normal[2] = 0;

    faces[2].vertices[0][0] = -hw; faces[2].vertices[0][1] = 0;    faces[2].vertices[0][2] = hd;
    faces[2].vertices[1][0] = hw; faces[2].vertices[1][1] = 0;    faces[2].vertices[1][2] = hd;
    faces[2].vertices[2][0] = hw; faces[2].vertices[2][1] = height; faces[2].vertices[2][2] = hd;
    faces[2].vertices[3][0] = -hw; faces[2].vertices[3][1] = height; faces[2].vertices[3][2] = hd;
    faces[2].normal[0] = 0; faces[2].normal[1] = 0; faces[2].normal[2] = 1;

    faces[3].vertices[0][0] = -hw; faces[3].vertices[0][1] = 0;    faces[3].vertices[0][2] = -hd;
    faces[3].vertices[1][0] = -hw; faces[3].vertices[1][1] = height; faces[3].vertices[1][2] = -hd;
    faces[3].vertices[2][0] = hw; faces[3].vertices[2][1] = height; faces[3].vertices[2][2] = -hd;
    faces[3].vertices[3][0] = hw; faces[3].vertices[3][1] = 0;    faces[3].vertices[3][2] = -hd;
    faces[3].normal[0] = 0; faces[3].normal[1] = 0; faces[3].normal[2] = -1;

    faces[4].vertices[0][0] = -hw; faces[4].vertices[0][1] = 0;    faces[4].vertices[0][2] = -hd;
    faces[4].vertices[1][0] = -hw; faces[4].vertices[1][1] = height; faces[4].vertices[1][2] = -hd;
    faces[4].vertices[2][0] = -hw; faces[4].vertices[2][1] = height; faces[4].vertices[2][2] = hd;
    faces[4].vertices[3][0] = -hw; faces[4].vertices[3][1] = 0;    faces[4].vertices[3][2] = hd;
    faces[4].normal[0] = -1; faces[4].normal[1] = 0; faces[4].normal[2] = 0;

    faces[5].vertices[0][0] = hw; faces[5].vertices[0][1] = 0;    faces[5].vertices[0][2] = hd;
    faces[5].vertices[1][0] = hw; faces[5].vertices[1][1] = height; faces[5].vertices[1][2] = hd;
    faces[5].vertices[2][0] = hw; faces[5].vertices[2][1] = height; faces[5].vertices[2][2] = -hd;
    faces[5].vertices[3][0] = hw; faces[5].vertices[3][1] = 0;    faces[5].vertices[3][2] = -hd;
    faces[5].normal[0] = 1; faces[5].normal[1] = 0; faces[5].normal[2] = 0;

    MeshData wall;

    auto rotate = [cos_a, sin_a](float x, float z, float& out_x, float& out_z) 
    {
        out_x = x * cos_a - z * sin_a;
        out_z = x * sin_a + z * cos_a;
    };

    float r = 220.0f / 255.0f;
    float g = 249.0f / 255.0f;
    float b = 255.0f / 255.0f;

    for (int f = 0; f < 6; ++f) 
    {
        float nx, nz;
        rotate(faces[f].normal[0], faces[f].normal[2], nx, nz);
        float ny = faces[f].normal[1];

        for (int v = 0; v < 4; ++v) 
        {
            float lx = faces[f].vertices[v][0];
            float ly = faces[f].vertices[v][1];
            float lz = faces[f].vertices[v][2];

            float wx, wz;
            rotate(lx, lz, wx, wz);
            wx += centerX;
            wz += centerZ;

            wall.coords.push_back(wx);
            wall.coords.push_back(ly);
            wall.coords.push_back(wz);

            wall.colors.push_back(r);
            wall.colors.push_back(g);
            wall.colors.push_back(b);

            wall.normals.push_back(nx);
            wall.normals.push_back(ny);
            wall.normals.push_back(nz);
        }

        unsigned int base = f * 4;
        wall.indices.push_back(base + 0);
        wall.indices.push_back(base + 1);
        wall.indices.push_back(base + 2);
        wall.indices.push_back(base + 2);
        wall.indices.push_back(base + 3);
        wall.indices.push_back(base + 0);
    }

    return wall;
}

sf::Vector3f projectionPointOnPlane(sf::Vector3f p0, sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f point)
{
    sf::Vector3f v1 = p1 - p0;
    sf::Vector3f v2 = p2 - p0;

    sf::Vector3f normal(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );

    float len = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    sf::Vector3f unitNormal = { normal.x / len, normal.y / len, normal.z / len };
    sf::Vector3f toPoint = point - p0;
    float signedDist = unitNormal.x * toPoint.x + unitNormal.y * toPoint.y + unitNormal.z * toPoint.z;

    return sf::Vector3f(
        point.x - unitNormal.x * signedDist,
        point.y - unitNormal.y * signedDist,
        point.z - unitNormal.z * signedDist
    );
}

bool isPointInFace(sf::Vector3f p0, sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f point)
{
    const float eps = 1e-6f;

    sf::Vector3f v0 = p1 - p0;
    sf::Vector3f v1 = p2 - p0;
    sf::Vector3f v2 = point - p0;

    sf::Vector3f N;
    N.x = v0.y * v1.z - v0.z * v1.y;
    N.y = v0.z * v1.x - v0.x * v1.z;
    N.z = v0.x * v1.y - v0.y * v1.x;

    float Nlen2 = N.x * N.x + N.y * N.y + N.z * N.z;
    if (Nlen2 < eps) 
    {
        return false;
    }

    float d = v2.x * N.x + v2.y * N.y + v2.z * N.z;
    if (std::fabs(d) > eps) 
    {
        return false;
    }

    int axis1, axis2;
    if (std::fabs(N.x) > std::fabs(N.y) && std::fabs(N.x) > std::fabs(N.z)) 
    {
        axis1 = 1;
        axis2 = 2;
    }
    else if (std::fabs(N.y) > std::fabs(N.z)) 
    {
        axis1 = 0;
        axis2 = 2;
    }
    else 
    {
        axis1 = 0;
        axis2 = 1;
    }

    auto proj = [axis1, axis2](const sf::Vector3f& v) -> sf::Vector2f 
    {
        if (axis1 == 0 && axis2 == 1) return sf::Vector2f(v.x, v.y);
        if (axis1 == 0 && axis2 == 2) return sf::Vector2f(v.x, v.z);
        return sf::Vector2f(v.y, v.z);
    };

    sf::Vector2f A = proj(p0);
    sf::Vector2f B = proj(p1);
    sf::Vector2f C = proj(p2);
    sf::Vector2f P = proj(point);

    sf::Vector2f v0_2d = C - A;
    sf::Vector2f v1_2d = B - A;
    sf::Vector2f v2_2d = P - A;

    float dot00 = v0_2d.x * v0_2d.x + v0_2d.y * v0_2d.y;
    float dot01 = v0_2d.x * v1_2d.x + v0_2d.y * v1_2d.y;
    float dot02 = v0_2d.x * v2_2d.x + v0_2d.y * v2_2d.y;
    float dot11 = v1_2d.x * v1_2d.x + v1_2d.y * v1_2d.y;
    float dot12 = v1_2d.x * v2_2d.x + v1_2d.y * v2_2d.y;

    float denom = dot00 * dot11 - dot01 * dot01;
    if (std::fabs(denom) < eps) 
    {
        return false;
    }
    float invDenom = 1.0f / denom;
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= -eps) && (v >= -eps) && (u + v <= 1.0f + eps);
}

sf::Vector3f Location::getSupportForce(float m, sf::Vector3f S, sf::Vector3f V)
{
    sf::Vector3f Fsupport = { 0.0f, 0.0f, 0.0f };
    const float threshold = 0.1f;
    const float k = 1000.0f;
    const float damping = 10.0f;

    for (int i = 0; i < 11; ++i)
    {
        MeshData* mesh = i == 10 ? floor : walls[i];

        for (int j = 0; j < mesh->indices.size(); j += 3)
        {
            int j0 = mesh->indices[j];
            int j1 = mesh->indices[j + 1];
            int j2 = mesh->indices[j + 2];

            sf::Vector3f s0 = { mesh->coords[j0 * 3], mesh->coords[j0 * 3 + 1], mesh->coords[j0 * 3 + 2] };
            sf::Vector3f s1 = { mesh->coords[j1 * 3], mesh->coords[j1 * 3 + 1], mesh->coords[j1 * 3 + 2] };
            sf::Vector3f s2 = { mesh->coords[j2 * 3], mesh->coords[j2 * 3 + 1], mesh->coords[j2 * 3 + 2] };

            sf::Vector3f Sp = projectionPointOnPlane(s0, s1, s2, S);
            if (!isPointInFace(s0, s1, s2, Sp)) continue;

            sf::Vector3f r = Sp - S;
            float len_r = sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
            if (len_r < 1E-6 || len_r > threshold) continue;

            sf::Vector3f n = { -r.x / len_r, -r.y / len_r, -r.z / len_r };
            float Vn = V.x * n.x + V.y * n.y + V.z * n.z;
            float F = k * (threshold - len_r) - damping * Vn;

            if (F > 0)
            {
                Fsupport.x += F * n.x;
                Fsupport.y += F * n.y;
                Fsupport.z += F * n.z;
            }
        }
    }

    return Fsupport;
}

sf::Vector3f Location::getFrictionalForce(float m, sf::Vector3f S, sf::Vector3f V)
{
    float len_V = sqrt(V.x * V.x + V.y * V.y + V.z * V.z);
    if (len_V < 1E-6) return sf::Vector3f(0.0f, 0.0f, 0.0f);

    float x = V.x / len_V;
    float y = V.y / len_V;
    return sf::Vector3f(-9.8f * x, 0.0f, -9.8f * y) * m;
}

Engine::Engine(float mass, sf::Vector3f S0, sf::Vector3f V0)
    : m(mass), S(S0), V(V0), t0(std::chrono::high_resolution_clock::now()) {}

void Engine::setExternalForce(sf::Vector3f F)
{
    Fext = F;
}

sf::Vector3f Engine::calcPosition(Location& loc, bool reset_time)
{
    if (reset_time) t0 = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto t1 = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() * 1E-6;

    sf::Vector3f F = sf::Vector3f(0.0, -9.8f, 0.0f) * m + Fext + loc.getFrictionalForce(m, S, V) + loc.getSupportForce(m, S, V);

    sf::Vector3f Vt = F * (1.0f / m);
    sf::Vector3f St = V;

    S += St * dt;
    V += Vt * dt;
    t0 = t1;

    return S;
}

sf::Vector3f Engine::getPosition()
{
    return S;
}

sf::Vector3f Engine::getSpeed()
{
    return V;
}

float Engine::getMass()
{
    return m;
}
