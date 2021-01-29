#include "../CalcSys.h"
#include "Models/WindowInfoModel.h"
#include "GLFW/glfw3.h"

namespace CalcSys
{
    void calcFPS();
    void calcWindowInfo()
    {
        calcFPS();
    }
    inline void calcFPS()
    {
        WindowInfoModel &wim = WindowInfoModel::getInstance();
        static float framesPerSecond = 0.0f; // This will store our fps
        static float lastTime = 0.0f;        // This will hold the time from the last frame
        float currentTime = glfwGetTime() * 0.001f;
        ++framesPerSecond;
        if (currentTime - lastTime > 1.0f)
        {
            lastTime = currentTime;
            // sprintf(strFrameRate, "Current Frames Per Second: %d", int(framesPerSecond));
            // SetWindowText(g_hWnd, strFrameRate);
            wim.fps = framesPerSecond;
            framesPerSecond = 0;
        }
    }
} // namespace CalcSys