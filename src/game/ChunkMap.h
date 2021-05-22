#pragma once
#include "parallel_hashmap/phmap.h"
#include "Chunk.h"

class ChunkMap
{
private:
    phmap::flat_hash_map<ChunkIDStruct, Chunk *> chunkPhMap;
    /* data */
public:
    ChunkMap(/* args */);
    ~ChunkMap();
};
