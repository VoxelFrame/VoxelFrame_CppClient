#pragma once

#define ChunkSize 64
#include "graph/base/Mesh.h"

struct ChunkIDStruct
{
    int x;
    int y;
    int z;
    /* data */
    ChunkIDStruct();
    ChunkIDStruct(int x, int y, int z);
};

class Chunk
{
private:
    int blockData[ChunkSize * ChunkSize * ChunkSize]; //protobuf需要直接解析到的目标位置
    ChunkIDStruct chunkId;                            //构造函数中进行初始化
    Mesh mesh;
    /* data */
public:
    void fillTest();
    Chunk(int x, int y, int z);
    ~Chunk();
};
