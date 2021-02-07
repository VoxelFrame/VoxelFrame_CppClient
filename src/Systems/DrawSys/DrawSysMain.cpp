#include "DrawSys.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Models/WindowInfoModel.h"
#include "Systems/CalcSys/CalcSys.h"
#include "Systems/DrawSys/GuiSys/GuiSys.h"
#include "./MapDrawer/MapDrawer.h"
namespace DrawSys
{
    void drawBegin();
    void drawMain();
    void drawEnd();
    // int Render();
    void processInput(GLFWwindow *window);
    void doDraw()
    {
        drawBegin();
        drawMain();
        drawEnd();
    }
    //窗口大小变化时，重新设置视口
    void framebuff_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
        WindowInfoModel &wim = WindowInfoModel::getInstance();
        wim.Height = height;
        wim.Width = width;
    }
    bool init()
    {
        glfwInit(); //初始化GLFW

        //指明OpenGL版本
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();

        //创建窗口
        GLFWwindow *window = glfwCreateWindow(
            windowInfoModel.Width,
            windowInfoModel.Height, "OpenGLTest", NULL, NULL);

        windowInfoModel.window = window;
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window " << std::endl;
            //销毁所有窗口
            glfwTerminate();
            return false;
        }
        //将该窗口作为当前线程的主上下文
        glfwMakeContextCurrent(window);
        //GLAD是管理OpenGL指针的，在调用任何OpenGL的函数之前需要初始化GLAD
        if (!gladLoadGL())
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        //设置视口Viewport
        //前两个参数控制渲染窗口左下角的相对位置，第三和第四个参数控制渲染窗口的宽度和高度
        //OpenGL会在此窗口大小范围内进行坐标变换
        glViewport(0, 0, 800, 600);

        //监听窗口大小变化
        glfwSetFramebufferSizeCallback(window, framebuff_size_callback);

        GuiSys::init();
        return true;
    }

    inline void drawBegin()
    {

        //fpsStart = clock();
        // double nowTime = glfwGetTime();
        // control->elapseTime = nowTime - control->oldTime;
        // control->oldTime = nowTime;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void drawMain()
    {
        if (GuiSys::isRender)
        {
            // Render();
            MapDrawer::getInstance()->doDraw();
        }
        GuiSys::renderGui();
        GuiSys::drawGui(); //绘制gui，最后一步做
    }

    inline void drawEnd()
    {
        WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();
        // CalcSys::calcWindowInfo();
        // drawWindowInfo();

        //将存储在缓冲区中的像素颜色进行绘制，这里涉及到双缓冲的问题
        glfwSwapBuffers(windowInfoModel.window);
        //检查有没有触发什么事件（键盘输入、鼠标移动等)、窗口改变
        glfwPollEvents();
        //control->keyPress();
    }


    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

} // namespace DrawSys