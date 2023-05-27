#include "sha256.h"
#include "Block.h"
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

Block::Block(uint32_t bIndexIn,const string & bDataIn, string merkleroot):_bIndex(bIndexIn),_bData(bDataIn){
    merkle_root = merkleroot;
	_bNonce = -1;
	_cTime = time(nullptr);
}

//TODO:
Block::Block(string &merkleroot) {
    _cTime = time(nullptr); //获取当前时间
    _bIndex = 0;
    _bNonce = 0;
    _bData = "";
    merkle_root = merkleroot;
}

Block::Block() =default;



string Block::GetHash()
{
	return _bHash;
}//获取区块hash

uint32_t Block::GetBIndex() {
    return _bIndex++;
}//获取区块编号

 string Block::CalculateBlockHash()
{
	stringstream ss;
	ss<< _bIndex << _cTime << _bData << _bNonce << bPrevHash << merkle_root;
	return sha256(ss.str());

}//计算区块hash
string Block::GetMerkleRoot() const {
    return merkle_root;
}
//获取默克尔根植

BigBlock::BigBlock() {
    merkle_root = "";
    _bNonce = 0;
    _cTime = time(nullptr);
    _bIndex ++;

}//构造函数

void BigBlock::AddMicroBlock(Block &blk) {
   vec_blocks.emplace_back(blk);
}//添加微区块

//BigBlock::BigBlock(string & merkleroot) {
//    merkle_root = merkleroot;
//    _bNonce = 0;
//    _cTime = time(nullptr);
//    _bIndex ++;
//
//}

BigBlock::BigBlock(uint32_t bIndexIn, const string &bDataIn, string merkleroot) {
    _bIndex = bIndexIn;
    _bData = bDataIn;
    merkle_root = merkleroot;
    _cTime = time(nullptr);
    _bNonce = -1;

}//构造函数

