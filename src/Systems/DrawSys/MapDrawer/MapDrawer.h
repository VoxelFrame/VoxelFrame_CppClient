#ifndef __MAPDRAWER_H__
#define __MAPDRAWER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
using namespace std;

namespace DrawSys
{
    class MapDrawer
    {
    private:
        /* data */
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "layout (location = 1) in vec2 aTexCoord;\n"
                                         "out vec2 texCoord;\n"
                                         "uniform mat4 rotate;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = rotate * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "   texCoord=aTexCoord;\n"
                                         "}\0";
        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "in vec2 texCoord;\n"
                                           "uniform sampler2D mainTex;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = texture(mainTex,texCoord);\n"
                                           
                                           "}\n\0";
        const char* vsPath = "./Shader/shader.vs";
        const char* fsPath = "./Shader/shader.fs";
        unsigned int VBO, VAO,EBO;
        int shaderProgram;
        

    public:
        MapDrawer(/* args */);

        static MapDrawer *getInstance();
        unsigned int LoadTexture(string path);
        void AddShader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType);
        void LinkShaders();
        bool ReadFile(const char* pFileName, string& outFile);
        void doDraw();
    };

} // namespace DrawSys

#endif // __MAPDRAWER_H__