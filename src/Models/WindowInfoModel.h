#ifndef __WINDOWINFOMODEL_H__
#define __WINDOWINFOMODEL_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"
class WindowInfoModel
{
public:
    WindowInfoModel();
    static WindowInfoModel &getInstance();

    GLFWwindow *window;
    float fps;
    int Width;
    int Height;
};
#endif // __WINDOWINFOMODEL_H__