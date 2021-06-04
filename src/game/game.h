#pragma once
#include "base.h"
#include "chunk.h"

class Game
{
    // private:

    /* data */
public:
    // datas
    std::shared_ptr<ChunkManager> chunkManager;
    // funcs

    void start()
    {
        chunkManager = std::make_shared<ChunkManager>();
        // this
    }
};
