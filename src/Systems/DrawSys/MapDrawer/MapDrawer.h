#ifndef __MAPDRAWER_H__
#define __MAPDRAWER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace DrawSys
{
    class MapDrawer
    {
    private:
        /* data */
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";
        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\n\0";
        unsigned int VBO, VAO;
        int shaderProgram;

    public:
        MapDrawer(/* args */);

        static MapDrawer *getInstance();

        void doDraw();
    };

} // namespace DrawSys

#endif // __MAPDRAWER_H__