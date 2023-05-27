

#include "Blockchain.h"

Blockchain::Blockchain()
{
	_bChain.emplace_back(BigBlock(_bIndex,"Genesis Block", ""));
}//添加创世区块

BigBlock Blockchain::AddBlock(BigBlock bNew)
{
	bNew.bPrevHash = GetLastBlock().GetHash(); //获取前一区块hash
    bNew._bHash = bNew.CalculateBlockHash(); //计算当前hash
    BlockIndexAdd(); //区块编号改变
    bNew._bBIndex = GetBlockIndex(); //获取区块编号
    _ePochRandomness = bNew._bHash; //时代随机源取自当前区块，作用在下一个时代

//    cout<<"_ePochRandomness = " << _ePochRandomness <<endl;
	_bChain.push_back(bNew); //添加新区块上链
    return bNew;
}

BigBlock Blockchain::GetLastBlock() const
{
	return _bChain.back();//返回向量中的最后一个元素
}

size_t Blockchain::GetBlockIndex() const{
    return _bIndex;
}

void Blockchain::BlockIndexAdd() {
    _bIndex++;

}

string Blockchain::GetRandomness() {
    return _ePochRandomness;
}
