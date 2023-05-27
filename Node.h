
#ifndef K_CA_NODE_H
#define K_CA_NODE_H

#include <vector>
#include <map>
#include <iostream>

#include "Network.h"
#include "Sealer.h"
#include "ViewState.h"
#include "Committee.h"

//客户端


class Client : public NetworkNode {
    std::map<std::string ,int> accepted_reply; 
public:
    Client();
    void OnRecvMsg(network_address_t src,Message msg) override; //接收网络中发送给自己的交易
    void SendRequest(network_address_t dst,Message &msg); //发送请求消息
};


//共识节点
class Node : public NetworkNode {

    Cache ca = Cache(); //初始化交易池
    Sealer sl = Sealer(); //交易打包
    Blockchain bChain = Blockchain();
    std::vector<network_address_t> _otherNodes;



    struct key_t {
        network_address_t c;//客户端标识
        std::string o;//具体操作
        time_t t;
        std::string d;

        key_t();
        explicit key_t(Message &msg);
        key_t(network_address_t c,std::string o, time_t t, std::string d);
        key_t(const key_t &kt);
        bool operator<(const key_t &k1) const; //比较
        key_t &operator=(const key_t &k2) ;
    };
    std::map<key_t ,ViewState> _log;

    size_t _view = 0;


public:
    std::vector<network_address_t> _otherCommitteeNodes; //存放委员会其他成员
    int committe_seq ;
    size_t committee_trans = 0;
    bool isLeader;
    bool isBoss;
    string iDentity;
    Blockchain GetBlockChain();
    void TransToCache(Message &msg);
    Block SealTrans();
    BigBlock SealBlocks();
    network_address_t  GetNodeAdd();
    void SetAllNodes(const std::vector<std::unique_ptr<Node>> & allNodes);
    void OnRecvMsg(network_address_t src, Message msg) override;
    void GetOutBk();
    void SendAll(Message &msg);
//    void SendMsg();
    void SendConsensus(Message  msg);
    void SendBlock(Block &bk);
    void SendBigBlock(BigBlock &bk);
    void SendUnpack(Message &msg);

    string CalculateEpochRandomness(Block &bk);



};
#endif //K_CA_NODE_H
