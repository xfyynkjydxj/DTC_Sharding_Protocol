

#ifndef K_CA_BLOCKCHAIN_H
#define K_CA_BLOCKCHAIN_H

#include <vector>
#include "Block.h"
using namespace std;

class Blockchain{
    size_t _bIndex = 0;
public:
    Blockchain();
    BigBlock AddBlock(BigBlock bNew);
    size_t GetBlockIndex() const;
    void BlockIndexAdd();
    string GetRandomness();
private:
    //uint32_t _mDifficulty;
    vector<BigBlock> _bChain;
    string _ePochRandomness;//时代随机源
    BigBlock GetLastBlock() const;

};

#endif //K_CA_BLOCKCHAIN_H
