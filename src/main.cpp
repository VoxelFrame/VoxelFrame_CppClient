#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#pragma comment(lib, "glfw3.lib")

//窗口大小变化时，重新设置视口
void framebuff_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//处理输入
void process_input_callabck(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit(); //初始化GLFW

    //指明OpenGL版本
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGLTest", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window " << std::endl;
        //销毁所有窗口
        glfwTerminate();
        return -1;
    }
    //将该窗口作为当前线程的主上下文
    glfwMakeContextCurrent(window);

    //处理输入
    glfwSetKeyCallback(window, process_input_callabck);

    //GLAD是管理OpenGL指针的，在调用任何OpenGL的函数之前需要初始化GLAD
    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //设置视口Viewport
    //前两个参数控制渲染窗口左下角的相对位置，第三和第四个参数控制渲染窗口的宽度和高度
    //OpenGL会在此窗口大小范围内进行坐标变换
    glViewport(0, 0, 800, 600);

    //监听窗口大小变化
    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);

    //循环渲染，在退出前一直不断地绘制图像
    while (!glfwWindowShouldClose(window))
    {
        //清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //将存储在缓冲区中的像素颜色进行绘制，这里涉及到双缓冲的问题
        glfwSwapBuffers(window);
        //检查有没有触发什么事件（键盘输入、鼠标移动等)、窗口改变
        glfwPollEvents();
    }

    // 退出前清理
    glfwTerminate();
    return 0;
}