#include <map>

//区块大小
const int chunkSize = 64 * 64 * 64;

//单个块
typedef struct
{
    int id1;
    int id2;
} BlockKey;

//ChunkKey 区块在世界map中的键
typedef struct
{
    int x;
    int y;
    int z;
} ChunkKey;

//ChunkModel 区块的数据模型
typedef struct
{
    BlockKey blockDataArr[chunkSize];
} ChunkModel;
//WorldModel 地图的数据模型
typedef struct
{
    std::map<ChunkKey, ChunkModel> map;
} WorldModel;