#pragma once
#include "parallel_hashmap/phmap.h"
#include "graph/Mesh.h"
#include "graph/_Graph.h"
#include "game.h"
#include "app.h"
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
    //需要确保参数一一对应
    //构建一个维度的面
    void constructMeshInOneDim(
        uint8_t &block,
        uint8_t &block_p,
        CommonBlockInfo &blockInfo,
        CommonBlockInfo &blockInfo_p,
        CommonBlockInfo::FaceDirection posDir,
        CommonBlockInfo::FaceDirection negDir)
    {
        //+1为空 当前为实心
        if (!block_p &&
            block &&
            blockInfo.hasFace(posDir))
        {
            uint8_t indicesOfIndices[6]; //qaq 取不来名字了
            blockInfo.getFaceIndices(posDir, indicesOfIndices);
            for (int i = 0; i < 6; i++)
            {
                indices.push_back(_8points[indicesOfIndices[i]]);
            }
            //逆时针面为正面
        }
        //x为空 x+1为实,添加朝x负向的面
        else if (!x &&
                 _x_p &&
                 blockInfo_p.hasFace(negDir))
        {
            uint8_t indicesOfIndices[6]; //qaq 取不来名字了
            blockInfo_p.getFaceIndices(negDir, indicesOfIndices);
            for (int i = 0; i < 6; i++)
            {
                indices.push_back(_8points[indicesOfIndices[i]]);
            }
            //逆时针面为正面
        }
    }

public:
    uint8_t data[ChunkSize];
    ChunkKey chunkKey;
    Game &game;

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
        auto blockManager = _g_app.gamePtr->blockManager;
        //遍历区块
        for (int x = 0; x < ChunkWidth; x++)
        {
            for (int y = 0; y < ChunkWidth / 2; y++)
            {
                for (int z = 0; z < ChunkWidth; z++)
                {
                    uint32_t _8points = {
                        getIndexByPos(x + 0, y + 0, z + 0),
                        getIndexByPos(x + 1, y + 0, z + 0),
                        getIndexByPos(x + 0, y + 1, z + 0),
                        getIndexByPos(x + 0, y + 0, z + 1),
                        getIndexByPos(x + 1, y + 1, z + 0),
                        getIndexByPos(x + 0, y + 1, z + 1),
                        getIndexByPos(x + 1, y + 0, z + 1),
                        getIndexByPos(x + 1, y + 1, z + 1),
                    };
                    //             x y z
                    //x+1 空 x 不空 x 的正向面存在
                    auto _block = readData(x, y, z);
                    auto &blockInfo = blockManager->getBlockInfo(_block);

                    //构建一个维度的面
                    auto _block_p = readData(x + 1, y, z);
                    auto &blockInfo_p = blockManager->getBlockInfo(_block_p);
                    constructMeshInOneDim(_block, _block_p, blockInfo, blockInfo_p,
                                          CommonBlockInfo::FaceX_Positive, CommonBlockInfo::FaceX_Negative);

                    _block_p = readData(x, y + 1, z);
                    &blockInfo_p = blockManager->getBlockInfo(_block_p);
                    constructMeshInOneDim(_block, _block_p, blockInfo, blockInfo_p,
                                          CommonBlockInfo::FaceY_Positive, CommonBlockInfo::FaceY_Negative);

                    _block_p = readData(x, y, z + 1);
                    &blockInfo_p = blockManager->getBlockInfo(_block_p);
                    constructMeshInOneDim(_block, _block_p, blockInfo, blockInfo_p,
                                          CommonBlockInfo::FaceZ_Positive, CommonBlockInfo::FaceZ_Negative);
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
    // Game &game;
    /* data */
    phmap::flat_hash_map<ChunkKey, std::shared_ptr<Chunk>> chunkKey2chunkPtr;

public:
    ChunkManager()
    {
        addNewChunk(0, 0, 0);
    }
    void addNewChunk(int32_t x, int32_t y, int32_t z);
};