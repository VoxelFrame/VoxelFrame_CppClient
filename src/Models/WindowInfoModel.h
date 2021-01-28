#include "glad/glad.h"
#include "GLFW/glfw3.h"
class WindowInfoModel
{
public:
    WindowInfoModel();
    static WindowInfoModel &getInstance();

    GLFWwindow *window;
};