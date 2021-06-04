#pragma once
#include "parallel_hashmap/phmap.h"
#define ChunkWidth 64
#define ChunkSize (ChunkWidth * ChunkWidth * ChunkWidth)

struct ChunkKey
{
    int32_t x;
    int32_t y;
    int32_t z;

    bool operator==(const ChunkKey &o) const
    {
        return x == o.x && y == o.y && z == o.z;
    }
    friend size_t hash_value(const ChunkKey &p)
    {
        return phmap::HashState().combine(0, p.x, p.y, p.z);
    }

    ChunkKey(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z)
    {
    }
    ChunkKey() {}
};
class Chunk
{
private:
    /* data */
public:
    uint8_t data[ChunkSize];
    ChunkKey chunkKey;
    Chunk(ChunkKey ck)
    {
        chunkKey = ck;
        for (int x = 0; x < ChunkWidth; x++)
        {
            for (int y = 0; y < ChunkWidth / 2; y++)
            {
                for (int z = 0; z < ChunkWidth; z++)
                {
                    data[x + y * ChunkWidth + z * ChunkWidth * ChunkWidth];
                }
            }
        }
    }
    Chunk() {}
};

class ChunkManager
{
private:
    /* data */
    phmap::flat_hash_map<ChunkKey, std::shared_ptr<Chunk>> chunkKey2chunkPtr;

public:
    ChunkManager()
    {
        addNewChunk(0, 0, 0);
    }
    void addNewChunk(int32_t x, int32_t y, int32_t z)
    {
        ChunkKey ck(x, y, z);
        chunkKey2chunkPtr[ck] = std::make_shared<Chunk>(ck);
    }
};