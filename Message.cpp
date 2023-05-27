#include <sstream>

#include "Message.h"


Message::Message(msg_type_t _type):msg_type(_type) {

}


Message::Message(network_address_t  master,msg_type_t _type):msg_type(_type) {
    c = master; //交易发送方
    t = time(nullptr); //时间戳
    o = "PBFT_Consensus"; //具体操作
    n = 0; //n主要用于对所有客户端的请求进行排序
    i = 0; //消息发送方
    v = 0; //v指视图编号
    r = ""; //epochRandomness
    d = this->diggest(); //d指消息摘要
    m = this->str(); //m指消息内容
}

std::string Message::diggest() {
    std::stringstream ss;
    ss << o << t << c << r;
    return sha256(ss.str());
} //摘要hash

std::string Message::str() const{
    std::stringstream ss;
    ss
        <<"o="<<o
        <<", t="<<t
        <<", v="<<v
        <<", n="<<n
        <<", c="<<c
        <<", d="<<d
        <<", r="<<r
        <<")";
    return ss.str();
}//消息内容
Message::Message(const Message &msg) {
  msg_type = msg.msg_type;
  t = msg.t;
  c = msg.c;
  o = msg.o;
  d = msg.d;
  i = msg.i;
  v = msg.v;
  n = msg.n;
  r = msg.r;
}
Message &Message::operator=(const Message &msg) {
  if (this == & msg)
    return *this;
  msg_type = msg.msg_type;
  t = msg.t;
  c = msg.c;
  o = msg.o;
  d = msg.d;
  i = msg.i;
  v = msg.v;
  n = msg.n;
  r = msg.r;
  return  *this;

} //对比消息

