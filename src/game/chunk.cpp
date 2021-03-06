#include "chunk.h"

void ChunkManager::addNewChunk(int32_t x, int32_t y, int32_t z)
{
    ChunkKey ck(x, y, z);
    auto newChunk = std::make_shared<Chunk>(ck);

    // newChunk->constructMesh();
    chunkKey2chunkPtr[ck] = newChunk;
    _g_Graph.addChunk2DrawList(newChunk);
}

void Chunk::constructMesh()
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
    auto blockManager = App::getInstance().gamePtr->blockManager;
    //遍历区块
    for (int x = 0; x < ChunkWidth; x++)
    {
        for (int y = 0; y < ChunkWidth / 2; y++)
        {
            for (int z = 0; z < ChunkWidth; z++)
            {
                //标准方块8个点序列对应的在区块中的索引
                uint32_t _8points[8] = {
                    getIndexByPos(x + 0, y + 0, z + 0),
                    getIndexByPos(x + 1, y + 0, z + 0),
                    getIndexByPos(x + 0, y + 1, z + 0),
                    getIndexByPos(x + 0, y + 0, z + 1),
                    getIndexByPos(x + 1, y + 1, z + 0),
                    getIndexByPos(x + 0, y + 1, z + 1),
                    getIndexByPos(x + 1, y + 0, z + 1),
                    getIndexByPos(x + 1, y + 1, z + 1),
                };

                auto _block = readData(x, y, z);
                auto &blockInfo = blockManager->getBlockInfo(_block);

                auto _block_p = readData(x + 1, y, z);
                auto &blockInfo_p_x = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(_block, _block_p, blockInfo, blockInfo_p_x,
                                      CommonBlockInfo::FaceX_Positive, CommonBlockInfo::FaceX_Negative, _8points);

                _block_p = readData(x, y + 1, z);
                auto &blockInfo_p_y = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(_block, _block_p, blockInfo, blockInfo_p_y,
                                      CommonBlockInfo::FaceY_Positive, CommonBlockInfo::FaceY_Negative, _8points);

                _block_p = readData(x, y, z + 1);
                auto &blockInfo_p_z = blockManager->getBlockInfo(_block_p);
                constructMeshInOneDim(_block, _block_p, blockInfo, blockInfo_p_z,
                                      CommonBlockInfo::FaceZ_Positive, CommonBlockInfo::FaceZ_Negative, _8points);
            }
        }
    }
}
