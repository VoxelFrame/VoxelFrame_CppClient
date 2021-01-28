#include "InputSys.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Models/WindowInfoModel.h"
namespace InputSys
{
    //处理输入
    void process_input_callabck(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }
    void init()
    {
        //处理输入
        glfwSetKeyCallback(WindowInfoModel::getInstance().window, process_input_callabck);
    }

} // namespace InputSys