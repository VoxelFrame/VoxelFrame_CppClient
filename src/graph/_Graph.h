#ifndef __DRAWSYS_H__
#define __DRAWSYS_H__
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Graph
{
private:
    /* data */
public:
    int windowH = 800;
    int windowW = 1000;
    GLFWwindow *window;
    float highDPIscaleFactor = 1;
    void doDraw();
    bool init();
    inline bool running()
    {
        return !glfwWindowShouldClose(window);
    }
    inline void end()
    {
        glfwTerminate();
    }
};

extern Graph _g_Graph;

#endif // __DRAWSYS_H__