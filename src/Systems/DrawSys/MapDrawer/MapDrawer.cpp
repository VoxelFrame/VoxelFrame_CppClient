#include "MapDrawer.h"
#include "iostream"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "string"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include"stdio.h"
#include <fstream>

#define BLOCKSIZE 1.0f

namespace DrawSys
{
    using namespace std;
    MapDrawer::MapDrawer(/* args */)
    {    
        // float vertices[] =
        //     {
        //         0.5f,-0.5f, 0.5f,      0.0f,0.0f,  //正面
        //         -0.5f,-0.5f,  0.5f,      1.0f,0.0f,
        //         -0.5f,0.5f,0.5f,       1.0f,1.0f,

        //         -0.5f,0.5f,0.5f,       1.0f,1.0f,
        //         0.5f,0.5f,0.5f,      0.0f,1.0f,
        //         0.5f,-0.5f,0.5f,       0.0f,0.0f,

        //         -0.5f,0.5f,-0.5f,      0.0f,0.0f,  //反面
        //         0.5f,0.5f,-0.5f,       1.0f,0.0f,
        //         0.5f,-0.5f,-0.5f,      1.0f,1.0f,

        //         0.5f,-0.5f,-0.5f,      1.0f,1.0f,
        //         -0.5f,-0.5f,-0.5f,     0.0f,1.0f,
        //         -0.5f,0.5f,-0.5f,      0.0f,0.0f,

        //         -0.5f, 0.5f,-0.5f,     0.0f,0.0f,  //左面
        //         -0.5f,-0.5f,-0.5f,     1.0f,0.0f,
        //         -0.5f,-0.5f,0.5f,      1.0f,1.0f,

        //         -0.5f,-0.5f,0.5f,      1.0f,1.0f,
        //         -0.5f,0.5f,0.5f,       0.0f,1.0f,
        //         -0.5f,0.5f,-0.5f,      0.0f,0.0f,

        //         0.5f,0.5f,-0.5f,       0.0f,0.0f,   //右面
        //         0.5f,0.5f,0.5f,        1.0f,0.0f,
        //         0.5f,-0.5f,0.5f,       1.0f,1.0f,

        //         0.5f,-0.5f,0.5f,       1.0f,1.0f,
        //         0.5f,-0.5f,-0.5f,      0.0f,1.0f,
        //         0.5f,0.5f,-0.5f,       0.0f,0.0f,

        //         0.5f,0.5f,0.5f,        0.0f,0.0f,   //上面
        //         0.5f,0.5f,-0.5f,       1.0f,0.0f,
        //         -0.5f,0.5f,-0.5f,      1.0f,1.0f,

        //         -0.5f,0.5f,-0.5f,      1.0f,1.0f,   
        //         -0.5f,0.5f,0.5f,       0.0f,1.0f,
        //         0.5f,0.5f,0.5f,        0.0f,0.0f,

        //         -0.5f,-0.5f,-0.5f,     0.0f,0.0f,   //下面
        //         0.5f,-0.5f,-0.5f,      1.0f,0.0f,
        //         0.5f,-0.5f,0.5f,       1.0f,1.0f,

        //         0.5f,-0.5f,0.5f,       1.0f,1.0f,   
        //         -0.5f,-0.5f,0.5f,      0.0f,1.0f,
        //         -0.5f,-0.5f,-0.5f,     0.0f,0.0f,
        //     };
        CompileShaders();        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const GLvoid*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        
    }

    MapDrawer *MapDrawer::getInstance()
    {
        static MapDrawer mp;
        return &mp;
    }

    void MapDrawer::doDraw()
    {
        // draw our first triangle      
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
        glm::mat4 rotate = glm::mat4(1.0f);
        rotate = glm::rotate(rotate, 0.5f * (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotate"), 1, GL_FALSE, glm::value_ptr(rotate));
        glm::vec3 offset=glm::vec3(0.5f,0.5f,0.0f);
        glUniform3fv(glGetUniformLocation(shaderProgram,"offset"),1,glm::value_ptr(offset));
        // glActiveTexture(GL_TEXTURE0);
        // glUniform1i(glGetUniformLocation(shaderProgram, "mainTex"), 0); 
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glEnable(GL_DEPTH_TEST);
        unsigned int img1=LoadTexture("./resource/images/1.png");
        glDrawArrays(GL_TRIANGLES,0,6);
        unsigned int img2=LoadTexture("./resource/images/2.png");       
        glDrawArrays(GL_TRIANGLES,6,6);
        unsigned int img3=LoadTexture("./resource/images/3.png");
        glDrawArrays(GL_TRIANGLES,12,6);
        unsigned int img4=LoadTexture("./resource/images/4.png");
        glDrawArrays(GL_TRIANGLES,18,6);
        unsigned int img5=LoadTexture("./resource/images/5.png");
        glDrawArrays(GL_TRIANGLES,24,6);
        unsigned int img6=LoadTexture("./resource/images/6.png");
        glDrawArrays(GL_TRIANGLES,30,6);
        
    }

    //load texture
    unsigned int MapDrawer::LoadTexture(string path)
    {
        //load texture
        unsigned int texture;
        glGenTextures(1, &texture);
        int width, height, nrComponents;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format = 3;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
	    stbi_image_free(data);
        return texture;
    }
    
    //compile shader program
    void MapDrawer:: AddShader(GLuint ShaderProgram, const char* ShaderText, GLenum ShaderType)
    {
        GLuint Shader = glCreateShader(ShaderType);
        if (Shader == 0) 
        {
            fprintf(stderr, "Error creating shader type %d\n", ShaderType);
            exit(1);
        }
        glShaderSource(Shader, 1, &ShaderText, NULL);
        glCompileShader(Shader);
        GLint success;
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(Shader, 1024, NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
            exit(1);
        }

        glAttachShader(ShaderProgram, Shader);
    }

    //link shader programs
    void MapDrawer::CompileShaders() 
    {
        shaderProgram = glCreateProgram();
        if (shaderProgram == 0)
        {
            fprintf(stderr, "Error creating shader program\n");
            exit(1);
        }  

        string vShader, fShader;
        if (!ReadFile(vsPath, vShader)) 
        {
            exit(1);
        };
        if (!ReadFile(fsPath, fShader)) 
        {
            exit(1);
        };

        AddShader(shaderProgram, vShader.c_str(), GL_VERTEX_SHADER);
        AddShader(shaderProgram, fShader.c_str(), GL_FRAGMENT_SHADER);
        GLint Success = 0;
        GLchar ErrorLog[1024] = { 0 };
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);
        if (Success == 0) 
        {
            glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
            exit(1);
        }

        glValidateProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
        if (!Success) 
        {
            glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
            exit(1);
        }
        glUseProgram(shaderProgram);
    }

    //read shader file    
    bool MapDrawer::ReadFile(const char* pFileName, string& outFile) 
    {
        ifstream f(pFileName);   
        bool ret = false;   
        if (f.is_open()) 
        {
            string line;
            while (getline(f, line)) 
            {
                outFile.append(line);
                outFile.append("\n");
            }       
            f.close();       
            ret = true;
        }
        else 
        {
            cout<<"cna't read file:"+*pFileName<<endl;
        }      
        return ret;
    }
} // namespace DrawSys