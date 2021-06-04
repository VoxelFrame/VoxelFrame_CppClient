#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "base.h"
#include "paecs/paecs.h"
#include "game/game.h"
#include "graph/_Graph.h"
#include "net/_net.h"

struct A
{
    int id;
};
struct B
{
    int id;
    char testChar;
};

void helloworld_sys(B &a)
{
    std::cout << "helloworld" << std::endl;
}

//the global one
//全局唯一单例 存储，访问 所有动静态资源
class app
{
private:
    /* data */
public:
    // Scene scene;
    std::shared_ptr<paecs::Scene> ecsPtr;
    std::shared_ptr<Game> gamePtr;

    // app()
    // {

    // }
    void run()
    {
        ecsPtr = paecs::createScene();
        gamePtr = std::make_shared<Game>();

        if (!_g_Graph.init())
        {
            return; //启动失败
        }

        auto &ecs = *ecsPtr;
        ecs.createEntity()
            .addEmptyComponent<A>()
            .addEmptyComponent<B>();
        ecs.addSysByFunc(helloworld_sys);
        // _g_net.start();
        // NetSys::start();
        // WindowInfoModel &windowInfoModel = WindowInfoModel::getInstance();
        gamePtr->start();
        while (_g_Graph.running())
        {
            // DrawSys::doDraw();
            _g_Graph.doDraw();
            // //清屏
            // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);
            ecs.loop();
        }

        // //循环渲染，在退出前一直不断地绘制图像
        // while (!glfwWindowShouldClose(_g_Graph.window))
        // {
        //     // DrawSys::doDraw();
        //     _g_Graph.doDraw();
        //     // //清屏
        //     // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //     // glClear(GL_COLOR_BUFFER_BIT);
        // }

        // // 退出前清理
        _g_Graph.end();
    }
};

extern app _g_app;