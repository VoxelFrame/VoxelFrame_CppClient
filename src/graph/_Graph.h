#ifndef __DRAWSYS_H__
#define __DRAWSYS_H__
#include "GLFW/glfw3.h"

class Graph
{
private:
    /* data */
public:
    int windowH;
    int windowW;
    GLFWwindow *window;
    float highDPIscaleFactor = 1;
    void doDraw();
    bool init();
};

extern Graph _g_Graph;

#endif // __DRAWSYS_H__