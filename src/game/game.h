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
        //因为game是父元素，所以传给子元素引用就行，game管理子元素的生命周期
        chunkManager = std::make_shared<ChunkManager>();
        blockManager = std::make_shared<BlockManager>();
        // this
    }
};
