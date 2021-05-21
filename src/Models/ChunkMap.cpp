#include "ChunkMap.h"
//chunkmap下是一个chunk的键值对
//用于存储chunks,并在操作时可以快速地获取
#include "sparsepp/spp.h"
#include "Chunk.h"

using spp::sparse_hash_map;

ChunkMap::ChunkMap()
{
}

ChunkMap::~ChunkMap()
{
}
