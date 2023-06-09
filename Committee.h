

#ifndef K_CA_COMMITTEE_H
#define K_CA_COMMITTEE_H


#include "Block.h"
#include "Message.h"
#include "Node.h"
#include "Network.h"
#include "ViewState.h"
#include <algorithm>
#include <random>


class Node;



class Committee{
private:
    int number_members;
    std::vector<int> _members; //成员
    int whoismaster;
    vector<Message>_translations; //交易池

public:
    int sequence;
    Committee();
    vector<Message> & GetTranslations(); //获取交易消息
    std::vector<int> GetMembers(); //获取数量
    Committee(int num_members, int seq, int wism);
    std::vector<int>& GetCommitteeMembers(); //获取委员会成员
    int GetLeaderAddress(); //获取leader地址
    int GetWhoisMaster(); 
    void ShuffleNode(std::unique_ptr<Node> & node);

};

//通过PBFT共识打包bigblock
class ConsensusCommittee:public Committee{
private:
    BigBlock bBlk;
    Message PBFT_msg = Message(GetWhoisMaster(),Message::PRE_PREPARE);
public:
    vector<Block>vec_blocks;
    static ConsensusCommittee & instance();
    ConsensusCommittee();
    ConsensusCommittee(int num_members, int seq, int wism);
    BigBlock & GetBigBlock();
    Message & PBFT();
    //打包大区块
    BigBlock SealerBlock();
    void SendBigBlock(network_address_t ip, BigBlock & bBlk);
};

#endif //K_CA_COMMITTEE_H
