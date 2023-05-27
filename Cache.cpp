
#include "Cache.h"




void Cache::AddTranslation(Message & tr) {
    _trans_que.push(tr);
}  //添加


std::queue<Message> & Cache::GetTransQueue() {
    return _trans_que;
} //获取队列

void Cache::PopTransQueue() {
    _trans_que.pop();
} //删除
