#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Systems/DrawSys/DrawSys.h"
#include "Systems/NetSys/NetSys.h"
#include "Models/WindowInfoModel.h"
// #pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "ws2_32.lib")
// #pragma comment(lib,"lib文件名或路径")

int main()
{
    if (!DrawSys::init())
    {
        return -1; //启动失败
    }
    NetSys::start();
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
