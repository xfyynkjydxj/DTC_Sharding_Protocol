
#include "Node.h"
#include <sstream>
#include <string>



void Client::SendRequest(network_address_t dst, Message & msg) {
    SendMsg(dst, msg);
} //发送请求
void Client::OnRecvMsg(network_address_t src, Message msg) {

} //接收msg

Client::Client() {
}

Blockchain Node::GetBlockChain() {
  return bChain;
}

//构造P2P网络
void Node::SetAllNodes(const std::vector<std::unique_ptr<Node>> &allNodes) {

//GetBlockChain()
    for (auto & node : allNodes) {
        if (node->GetNodeAddress() == GetNodeAddress()) {
            continue;
        }
        _otherNodes.push_back(node->GetNodeAddress()); //添加其他节点
    }
}

void Node::OnRecvMsg(network_address_t src, Message msg)
{
    std::lock_guard<std::mutex> console_guard(console_mutex);
    key_t kt = key_t(msg.c,msg.o,msg.t,msg.d);

    if (msg.msg_type == Message::REQUEST)
    {
        ViewState vs = ViewState(msg);
        _log[kt] = vs;
    }
    if (msg.msg_type == Message::PRE_PREPARE||msg.msg_type == Message::UNPACK)
    {
        auto iter = _log.find(kt);
        if (iter ==_log.end())
        {
            ViewState vs = ViewState(msg);
            _log[kt] = vs;
            }
        }

    auto iter = _log.find(kt);
    if (iter ==_log.end())
    {
        std::cout <<"节点：" <<GetNodeAdd() << "找不到交易信息视图！"<< std::endl;
    }
    else
    {
        iter->second.handle_message(msg, *this);

    }
}







void Node::SendAll(Message &msg) {

    for(auto dst : _otherCommitteeNodes)
    {
        SendMsg(dst,msg);
    }
} //发送消息给委员会其他成员


void Node::SendConsensus(Message msg) {

    for(auto dst :ConsensusCommittee::instance().GetCommitteeMembers())
    {
        if (dst == GetNodeAdd())
            continue;
        else
        {
            // cout << " 向节点 " << dst ;
            SendMsg(dst,msg);
        }

    }
}

network_address_t Node::GetNodeAdd() {
    return NetworkNode::GetNodeAddress();
}


Node::key_t::key_t(Message &msg) {
    c = msg.c;
    o = msg.o;
    t = msg.t;
    d = msg.d;
}
 bool Node::key_t::operator<(const Node::key_t &k1) const
{
    if(c <k1.c)
        return true;
    else if(c == k1.c)
    {
        if (o < k1.o)
            return true;
        else if(o == k1.o)
        {
            if (t < k1.t)
                return true;
            else if (t == k1.t)
            {
                if (d < k1.d)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
Node::key_t &Node::key_t::operator=(const Node::key_t &k2) {
    if(this == &k2)
        return *this;
    c = k2.c;
    o = k2.o;
    t = k2.t;
    d = k2.d;
    return *this;
}
Node::key_t::key_t(const Node::key_t &kt) {
    c = kt.c;
    t = kt.t;
    o = kt.o;
    d = kt.d;
}

Node::key_t::key_t(network_address_t client, std::string object, time_t time, std::string diggest):c(client),o(std::move(object)),t(time),d(std::move(diggest)) {

}
Node::key_t::key_t():c(0),o("0"),t(0),d("0"){}


void Node::TransToCache(Message &msg) {
    ca.AddTranslation(msg);
} //添加交易进池


Block Node::SealTrans() {
    sl.CalculateMerkRoot(ca);
    Block bNew = Block(sl.merkle_root);
    bNew._bHash = bNew.CalculateBlockHash();
    return bNew;
} //封装交易

BigBlock Node::SealBlocks() {
    BigBlock bNew;
    //TODO:打包大区块由Node，Committee还是BigBlock完成
    bNew = sl.Upchain(bChain);//区块上链
    return bNew;
}
void Node::SendBigBlock(BigBlock &bk) {
  for(auto dst : _otherCommitteeNodes)
  {
    NetworkNode::SendBigBlock(dst,bk);
  }
}//发送大区块

//主节点分发区块给其他节点
void Node::GetOutBk() {

    bChain.AddBlock(ConsensusCommittee::instance().GetBigBlock());
    uint32_t block_index = ConsensusCommittee::instance().GetBigBlock()._bBIndex;
    std::cout << "节点：" << GetNodeAdd() << " 添加第 " << block_index << " 个区块. " << std::endl;
//    std::cout << "第" << block_index << "个区块的哈希值： " << ConsensusCommittee::instance().GetBigBlock()._bHash << endl;
}



void Node::SendUnpack(Message &msg) {
  Message unpack(Message::UNPACK);
  unpack.t = msg.t;
  unpack.o = msg.o;
  unpack.i = GetNodeAddress();
  unpack.d = msg.d;
  unpack.v = msg.v;
  unpack.c = msg.c;
  unpack.m = msg.m;
  unpack.r = msg.r;
    for (auto iter:_otherCommitteeNodes) {
//        cout << "节点：" << GetNodeAdd() << "节点：" << iter << "发送打包消息." << endl;
        SendMsg(iter,unpack);
    }

}

string Node::CalculateEpochRandomness(Block &bk) {
    stringstream ss;
 //   cout<<"节点 "<<GetNodeAdd()<<" ePochRandomness:" <<bk._bHash<<endl;
    ss << GetNodeAdd() << bk._bHash;
    return sha256(ss.str());
}

void Node::SendBlock(Block & bk) {
    NetworkNode::SendBlock(bk);

}
