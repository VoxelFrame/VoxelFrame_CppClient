#include "chunk.h"

void ChunkManager::addNewChunk(int32_t x, int32_t y, int32_t z)
{
    ChunkKey ck(x, y, z);
    auto newChunk = std::make_shared<Chunk>(ck);

    // newChunk->constructMesh();
    chunkKey2chunkPtr[ck] = newChunk;
    _g_Graph.addChunk2DrawList(newChunk);
}
