

#include "Network.h"

Network & Network::instance() {
    static Network inst;
    return inst;
} //单例p2p网络
bool Network::Empty(){
    std::lock_guard<std::mutex> guard(_mutex);//互斥锁，保证多线程情况下只有一个在运行。
    return _messages.empty();
} //判断消息list是否为空

void Network::SendMsg(network_address_t src, network_address_t dst, Message msg) {
    std::lock_guard<std::mutex> guard(_mutex);
    _messages.push_back({src,dst,msg});
}

void Network::SendBigBlock(network_address_t src, network_address_t dst, BigBlock bk){
  std::lock_guard<std::mutex> guard(_mutex);
  _bigblocks.push_back({src,dst,bk});
}
MessageAddressed Network::RecvMsg(network_address_t dst) {
    std::lock_guard<std::mutex> guard(_mutex);
    for (auto it = _messages.begin(); it !=_messages.end(); ++it) //遍历消息list
    {
        if(it->dst == dst)
        {
            auto msg = * it;
            _messages.erase(it); //删除
            return msg;
        }
    }
    throw std::runtime_error("no message for you");
}
//接收消息、区块
BigBlockAddressed Network::RecvBigBlock(network_address_t dst) {
  std::lock_guard<std::mutex> guard(_mutex);
  for (auto it = _bigblocks.begin(); it !=_bigblocks.end(); ++it)
  {
    if(it->dst == dst)
    {
      auto bk = *it;
      _bigblocks.erase(it);
      return bk;
    }
  }
  throw std::runtime_error("no block for you");
}
network_address_t Network::AssignAddress() {
    std::lock_guard<std::mutex> guard(_mutex);
    return ++nextAddress; // 分配address
}
bool Network::List_BigBlocks_Empty() {
  return _bigblocks.empty();
} //判空

void Network::SendBlock( Block bk) {
    std::lock_guard<std::mutex> guard(_mutex);
    _blocks.push_back(bk);
}//发送区块

network_address_t NetworkNode::GetNodeAddress() const{
    return _nAddress; // 获取节点地址
}


 NetworkNode::NetworkNode() :_nAddress(Network::instance().AssignAddress()) {
     std::thread([this]() {
         while (true) {
             try {
                 auto msg = Network::instance().RecvMsg(GetNodeAddress());
                 OnRecvMsg(msg.src, msg.msg);
             } catch (...) {
                 std::this_thread::sleep_for(1s);
             }
         }
     }).detach();
 }

 void NetworkNode::SendMsg(network_address_t dst, Message msg) {
    Network::instance().SendMsg(GetNodeAddress(),dst,msg);
}
void NetworkNode::SendBlock(Block &bk) {
    Network::instance().SendBlock(bk);
}
void NetworkNode::SendBigBlock(network_address_t dst, BigBlock bk) {
  Network::instance().SendBigBlock(GetNodeAddress(),dst,bk);
}
