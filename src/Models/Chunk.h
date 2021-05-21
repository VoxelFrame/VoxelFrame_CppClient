#pragma once

struct ChunkIDStruct
{
    int x;
    int y;
    int z;
    /* data */
};

class Chunk
{
private:
    /* data */
public:
    Chunk(int x, int y, int z);
    ~Chunk();
};
