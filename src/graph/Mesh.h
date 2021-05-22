#pragma once

#include "string"
#include "vector"

#include "glm/glm.hpp"

#include "./interface/Drawer.h"

using std::string;
using std::vector;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    string type;
};

class Mesh : public Drawer
{
public:
    /*  网格数据  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  函数  */
    Mesh();
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    // void Draw(Shader shader);

    void draw();

private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
    void setupMesh();
};