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
        const char* vsPath = "./resource/Shader/shader.vs";
        const char* fsPath = "./resource/Shader/shader.fs";
        unsigned int VBO, VAO,EBO;
        int shaderProgram;
        const float vertices[180] =
            {
                0.5f,-0.5f, 0.5f,      0.0f,0.0f,  //正面
                -0.5f,-0.5f,  0.5f,    1.0f,0.0f,
                -0.5f,0.5f,0.5f,       1.0f,1.0f,

                -0.5f,0.5f,0.5f,       1.0f,1.0f,
                0.5f,0.5f,0.5f,        0.0f,1.0f,
                0.5f,-0.5f,0.5f,       0.0f,0.0f,

                -0.5f,0.5f,-0.5f,      0.0f,0.0f,  //反面
                0.5f,0.5f,-0.5f,       1.0f,0.0f,
                0.5f,-0.5f,-0.5f,      1.0f,1.0f,

                0.5f,-0.5f,-0.5f,      1.0f,1.0f,
                -0.5f,-0.5f,-0.5f,     0.0f,1.0f,
                -0.5f,0.5f,-0.5f,      0.0f,0.0f,

                -0.5f, 0.5f,-0.5f,     0.0f,0.0f,  //左面
                -0.5f,-0.5f,-0.5f,     1.0f,0.0f,
                -0.5f,-0.5f,0.5f,      1.0f,1.0f,

                -0.5f,-0.5f,0.5f,      1.0f,1.0f,
                -0.5f,0.5f,0.5f,       0.0f,1.0f,
                -0.5f,0.5f,-0.5f,      0.0f,0.0f,

                0.5f,0.5f,-0.5f,       0.0f,0.0f,   //右面
                0.5f,0.5f,0.5f,        1.0f,0.0f,
                0.5f,-0.5f,0.5f,       1.0f,1.0f,

                0.5f,-0.5f,0.5f,       1.0f,1.0f,
                0.5f,-0.5f,-0.5f,      0.0f,1.0f,
                0.5f,0.5f,-0.5f,       0.0f,0.0f,

                0.5f,0.5f,0.5f,        0.0f,0.0f,   //上面
                0.5f,0.5f,-0.5f,       1.0f,0.0f,
                -0.5f,0.5f,-0.5f,      1.0f,1.0f,

                -0.5f,0.5f,-0.5f,      1.0f,1.0f,   
                -0.5f,0.5f,0.5f,       0.0f,1.0f,
                0.5f,0.5f,0.5f,        0.0f,0.0f,

                -0.5f,-0.5f,-0.5f,     0.0f,0.0f,   //下面
                0.5f,-0.5f,-0.5f,      1.0f,0.0f,
                0.5f,-0.5f,0.5f,       1.0f,1.0f,

                0.5f,-0.5f,0.5f,       1.0f,1.0f,   
                -0.5f,-0.5f,0.5f,      0.0f,1.0f,
                -0.5f,-0.5f,-0.5f,     0.0f,0.0f,
            };

        //const enum maps{grass,blue};

    public:
        MapDrawer(/* args */);
        static MapDrawer *getInstance();
        unsigned int LoadTexture(string path);
        void AddShader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType);
        void CompileShaders();
        bool ReadFile(const char* pFileName, string& outFile);
        float* GenerateVertices(float x,float y,float z);
        void doDraw();
    };

} // namespace DrawSys

#endif // __MAPDRAWER_H__