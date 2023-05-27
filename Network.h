

#ifndef K_CA_NETWORK_H
#define K_CA_NETWORK_H

#include <list>
#include <thread>
#include "Message.h"
#include "Block.h"

using namespace std::chrono_literals; //引入了名字空间std::chrono_literals，其中预定义了一些字面量后缀运算符

struct MessageAddressed{
    network_address_t src; //源
    network_address_t dst; //目的
    Message msg;
};

struct BigBlockAddressed{
  network_address_t src;
  network_address_t dst;
  BigBlock bk;
};

//P2P网络
class Network
{
    std::list<MessageAddressed> _messages;
    std::list<Block>_blocks;
    std::list<BigBlockAddressed> _bigblocks;
    network_address_t  nextAddress = 0;
    std::mutex _mutex;

public:

    static Network & instance();
    bool Empty();
    bool List_BigBlocks_Empty();
    void SendMsg(network_address_t src, network_address_t dst, Message msg); //发送
    void SendBlock(Block bk);
    void SendBigBlock(network_address_t src, network_address_t dst, BigBlock bk);
    MessageAddressed RecvMsg(network_address_t dst); //接收
    BigBlockAddressed RecvBigBlock(network_address_t dst);
    network_address_t  AssignAddress(); //分配地址
};

class NetworkNode
{
private:
    const network_address_t _nAddress;
    std::mutex _mutex;

public:
    NetworkNode();
    network_address_t GetNodeAddress() const;
    virtual void OnRecvMsg(network_address_t src, Message msg) = 0;
    void SendMsg(network_address_t dst, Message msg);
    void SendBlock(Block &bk);
    void SendBigBlock(network_address_t dst, BigBlock bk);
};
#endif
