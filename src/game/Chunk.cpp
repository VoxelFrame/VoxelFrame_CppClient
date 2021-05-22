#include "Chunk.h"

// chunk在map中的key //////////////////////////////////
ChunkIDStruct::ChunkIDStruct(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Chunk（区块） /////////////////////
void Chunk::fillTest()
{
    for (int x = 0; x < ChunkSize; x++)
    {
        for (int y = 0; y < ChunkSize; y++)
        {
            for (int z = 0; z < ChunkSize; z++)
            {
                if (y < 32) //小于32的y填充方块
                {
                    //左移12相当于乘64*64
                    this->blockData[x << 12 + y << 6 + z] = 1;
                }
            }
        }
    }
}

Chunk::Chunk(int x, int y, int z)
{
    this->chunkId.x = x;
    this->chunkId.y = y;
    this->chunkId.z = z;
    this->fillTest();
}

Chunk::~Chunk()
{
}
