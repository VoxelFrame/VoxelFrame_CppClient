#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "base.h"
#include "paecs/paecs.h"
#include "game/game.h"
#include "graph/_Graph.h"
#include "net/_net.h"

class Game;
////////////////////////////////////////
struct A
{
    int id;
};
struct B
{
    int id;
    char testChar;
};

void helloworld_sys(B &a);

//the global one
//全局唯一单例 存储，访问 所有动静态资源
class App
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
    void run();
    static App &getInstance();
};

// extern app _g_app;