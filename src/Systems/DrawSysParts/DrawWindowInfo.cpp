#include "../DrawSys.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include "Models/WindowInfoModel.h"
using namespace std;
namespace DrawSys
{
    void drawWindowInfo()
    {
        WindowInfoModel &wim = WindowInfoModel::getInstance();
        //drawFPS
        string fpsText = "FPS:";
        fpsText.append(to_string(wim.fps));
        // interface::drawText(fpsText, 0.9 * wim.Width, 0.925 * wim.Height, 1.0f, glm::vec3(1.00f, 1.00f, 1.00f));
    }
} // namespace DrawSys