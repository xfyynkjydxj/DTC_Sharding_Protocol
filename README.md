# K--CA
## SHA-256
sha256.h sha256.cpp ,详见LICENSE.txt

显示tps,延迟，区块容量。


##KCA
1. 利用pbft共识区块链修改，实现kca共识算法

2. 联盟链系统是通过文献中分片协议流程描述实现的，在系统架构和网络模型等方面与本系统保持一致，尽量控制差异仅在分片协议范围内

3. 系统采用与以太坊类似的银行账户模型存储节点信息，节点信息包括账户余额，积分余额，Nonce计数器，状态树根值以及合约哈希值。

4. 在系统仿真阶段，利用多线程的方式实现多个节点的生成。多个节点同时监听网络，查询网络中是否存在发送给自己的消息和区块。

5. 网络模型设计采用基于联盟链的弱中心化网络架构，节点进出网络需要系统批准，并将自身节点地址广播至联盟链网络，在下一个epoch开始时加入。

6. 系统由c++语言编写。系统包括区块类，区块链类，交易类，消息类，交易池类，打包功能类，节点类，网络类，共识机制类，分片协议类，视图类。本系统由三部分组成，第一部分是基础框架，其中包含区块类、区块链类、交易类、交易池类、消息类和网络类，组成区块链系统的基本框架、节点网络以及交易缓存池。第二部分是功能层，分别是打包功能类、节点类、共识机制类和视图类，实现交易的验证打包、消息传输和视图转换功能。第三部分是实现层，只有分片协议类。在基础框架部分，区块类包含Merkle root、版本信息、区块编号、时间戳等信息。节点类拥有信息表和微区块表，其中信息表用来存储网络中接收到的视图转换信息和交易验证审查信息，微区块表用来存储所属小组委员会的Leader节点发送的微区块，比对最终区块链上的大区块信息。而网络类则负责生成节点地址。

