#include "MapDrawer.h"
#include "iostream"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace DrawSys
{
    using namespace std;
    MapDrawer::MapDrawer(/* args */)
    {
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        float vertices[] =
            {
                0.5f,-0.5f,-0.5f,  
                0.5f,0.5f,-0.5f,    
                -0.5f, 0.5f,-0.5f,  
                -0.5f,-0.5f,-0.5f,  
                0.5f,-0.5f,0.5f,   
                0.5f,0.5f,0.5f,     
                -0.5f,0.5f,0.5f,    
                -0.5f,-0.5f,0.5f,   
            };
        unsigned int indices[] =
            {
                4,5,6, //前
                6,7,4,
                2,1,0, //后
                0,3,2,
                2,3,7, //左
                7,6,2,
                1,5,4, //右
                4,0,1,
                5,1,2, //上
                2,6,5,
                3,0,4, //下
                4,7,3,
            };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

    MapDrawer *MapDrawer::getInstance()
    {
        static MapDrawer mp;
        return &mp;
    }

    void MapDrawer::doDraw()
    {
        // draw our first triangle
        unsigned int img=LoadTexture("./resource/images/default.png");
        glEnable(GL_TEXTURE_2D);
        glUseProgram(shaderProgram);
        glm::mat4 rotate = glm::mat4(1.0f);
        rotate = glm::rotate(rotate, 2 * (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        unsigned int rotateLoc = glGetUniformLocation(shaderProgram, "rotate");
        glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, glm::value_ptr(rotate));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    unsigned int MapDrawer::LoadTexture(string path)
    {
        //load texture
        unsigned int texture;
        FILE *img = NULL;
        errno_t error;
        if((error=fopen_s(&img, path.c_str(), "rb"))!=0)
        {
            cout<<"File"+path+"can not open"<<endl;
        }
        unsigned long width = 0;
        unsigned long height = 0;
        unsigned long size = 0;
        fseek(img, 18, SEEK_SET);
        fread(&width, 4, 1, img);
        fread(&height, 4, 1, img);
        fseek(img, 0, SEEK_END);
        size = ftell(img) - 54;
        unsigned char *data = (unsigned char *)malloc(size);
        fseek(img, 54, SEEK_SET); // image data
        fread(data, size, 1, img);
        fclose(img);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (data)
        {
            free(data);
        }
        return texture;
    }
} // namespace DrawSys