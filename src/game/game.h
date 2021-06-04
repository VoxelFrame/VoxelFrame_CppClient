#pragma once
#include "base.h"
#include "chunk.h"
#include "block.h"

class Game
{
    // private:

    /* data */
public:
    // datas
    std::shared_ptr<ChunkManager> chunkManager;
    std::shared_ptr<BlockManager> blockManager;
    // funcs

    void start()
    {
        chunkManager = std::make_shared<ChunkManager>();
        blockManager = std::make_shared<BlockManager>();
        // this
    }
};
