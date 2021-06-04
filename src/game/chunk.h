#pragma once
#include "parallel_hashmap/phmap.h"
#include "graph/Mesh.h"
#include "graph/_Graph.h"
#include "game.h"
#define ChunkWidth 64
#define ChunkSize (ChunkWidth * ChunkWidth * ChunkWidth)

class Game;
x class Mesh;
//////////////////////////
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
class Chunk : public Mesh
{
private:
    /* data */
    inline uint8_t readData(int x, int y, int z)
    {
        return data[x + y * ChunkWidth + z * ChunkWidth * ChunkWidth];
    }
    inline uint32_t getIndexByPos(int x, int y, int z)
    {
        return x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1);
    }

public:
    uint8_t data[ChunkSize];
    ChunkKey chunkKey;

    //首次加载、数据变更（修改地形，都要构造（前提是在视野内
    void constructMesh()
    {
        indices.clear();
        if (vertices.size() != (ChunkWidth + 1) * (ChunkWidth + 1) * (ChunkWidth + 1))
        {
            vertices.resize((ChunkWidth + 1) * (ChunkWidth + 1) * (ChunkWidth + 1));
            for (int x = 0; x < ChunkWidth + 1; x++)
            {
                for (int y = 0; y < ChunkWidth + 1; y++)
                {
                    for (int z = 0; z < ChunkWidth + 1; z++)
                    {
                        vertices[x + y * (ChunkWidth + 1) + z * (ChunkWidth + 1) * (ChunkWidth + 1)].setPostion(x, y, z);
                    }
                }
            }
        }

        //遍历区块
        for (int x = 0; x < ChunkWidth; x++)
        {
            for (int y = 0; y < ChunkWidth / 2; y++)
            {
                for (int z = 0; z < ChunkWidth; z++)
                {
                    //             x y z
                    uint32_t _0_0_0 = getIndexByPos(x + 0, y + 0, z + 0);
                    uint32_t _1_0_0 = getIndexByPos(x + 1, y + 0, z + 0);
                    uint32_t _0_1_0 = getIndexByPos(x + 0, y + 1, z + 0);
                    uint32_t _0_0_1 = getIndexByPos(x + 0, y + 0, z + 1);
                    uint32_t _1_1_0 = getIndexByPos(x + 1, y + 1, z + 0);
                    uint32_t _0_1_1 = getIndexByPos(x + 0, y + 1, z + 1);
                    uint32_t _1_0_1 = getIndexByPos(x + 1, y + 0, z + 1);
                    uint32_t _1_1_1 = getIndexByPos(x + 1, y + 1, z + 1);
                    //x+1为空 x为实,添加朝x正向的面
                    if (!readData(x + 1, y, z) && readData(x, y, z))
                    {
                        // index_1_0_0
                        // index_1_1_0
                        // index_1_0_1
                        // index_1_1_1

                        //逆时针面为正面
                        indices.push_back(_1_0_0, _1_1_0, _1_0_1);
                        indices.push_back(_1_0_1, _1_1_1, _1_1_0);
                    }
                    //x为空 x+1为实,添加朝x负向的面
                    else if (readData(x + 1, y, z) && !readData(x, y, z))
                    {
                    }
                    //y+1为空 y为实,添加朝y正向的面
                    if (!readData(x, y + 1, z) && readData(x, y, z))
                    {
                    }
                    //y为空 y+1为实,添加朝y负向的面
                    else if (readData(x, y + 1, z) && !readData(x, y, z))
                    {
                    }
                    //z+1为空 z为实,添加朝z正向的面
                    if (!readData(x, y, z + 1) && readData(x, y, z))
                    {
                    }
                    //z为空 z+1为实,添加朝z负向的面
                    else if (readData(x, y, z + 1) && !readData(x, y, z))
                    {
                    }
                }
            }
        }
    }
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
    Game &game;
    /* data */
    phmap::flat_hash_map<ChunkKey, std::shared_ptr<Chunk>> chunkKey2chunkPtr;

public:
    ChunkManager(Game &game) : game(game)
    {
        addNewChunk(0, 0, 0);
    }
    void addNewChunk(int32_t x, int32_t y, int32_t z);
};