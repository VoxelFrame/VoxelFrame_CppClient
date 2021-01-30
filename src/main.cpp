#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Systems/DrawSys/DrawSys.h"
#include "Models/WindowInfoModel.h"
#pragma comment(lib, "glfw3.lib")

int main()
{
    if (!DrawSys::init())
    {
        return -1; //启动失败
    }
    WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();

    //循环渲染，在退出前一直不断地绘制图像
    while (!glfwWindowShouldClose(windowInfoModel.window))
    {
        DrawSys::doDraw();
        // //清屏
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
    }

    // 退出前清理
    glfwTerminate();
    return 0;
}
