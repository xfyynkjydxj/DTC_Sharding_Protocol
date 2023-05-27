

#ifndef K_CA_CACHE_H
#define K_CA_CACHE_H
//#include <vector>
#include <queue>
#include "Message.h"


class Cache{
public:
    void AddTranslation (Message & tr); //添加交易
    std::queue<Message> & GetTransQueue();  //获取交易队列
    void PopTransQueue(); //将队列中最靠前位置的元素删除

private:
    std::queue<Message> _trans_que;

};
#endif //K_CA_CACHE_H
