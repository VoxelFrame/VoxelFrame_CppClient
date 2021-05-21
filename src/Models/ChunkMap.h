#pragma once
#include "sparsepp/spp.h"
#include "Chunk.h"

class ChunkMap
{
private:
    spp::sparse_hash_map<ChunkIDStruct, Chunk> chunkSparseMap;
    /* data */
public:
    ChunkMap(/* args */);
    ~ChunkMap();
};
